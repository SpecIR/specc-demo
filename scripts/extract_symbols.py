#!/usr/bin/env python3
"""Extract SYMBOL objects (SpecDown Markdown) from C sources via libclang.

Walks the translation units listed in compile_commands.json, collects every
function *definition* located under the project directory, and emits one
SpecDown SYMBOL object per function:

    ## SYMBOL: name @SYM-name

    > kind: function

    > source: firmware/time_manager.c:45:1-67:2

    > complexity: 3

    > calls: [SYM-callee](@), ...

Calls to functions defined in the same project are emitted as SpecDown PID
links so the compiler materializes them as typed relations; calls to external
functions are omitted. Complexity is a decision-point count (1 + branches).

Usage: extract_symbols.py <compile_commands_dir> [output.md]
"""
import json
import sys
from pathlib import Path

from clang import cindex

BRANCH_KINDS = {
    cindex.CursorKind.IF_STMT,
    cindex.CursorKind.FOR_STMT,
    cindex.CursorKind.WHILE_STMT,
    cindex.CursorKind.DO_STMT,
    cindex.CursorKind.CASE_STMT,
    cindex.CursorKind.CONDITIONAL_OPERATOR,
}


def collect_functions(tu, project_dir):
    funcs = {}

    def visit(cursor):
        if cursor.kind == cindex.CursorKind.FUNCTION_DECL and cursor.is_definition():
            loc = cursor.location
            if loc.file and Path(loc.file.name).resolve().is_relative_to(project_dir):
                complexity = 1
                calls = []

                def walk(node):
                    nonlocal complexity
                    if node.kind in BRANCH_KINDS:
                        complexity += 1
                    if node.kind == cindex.CursorKind.CALL_EXPR and node.referenced is not None:
                        calls.append(node.referenced.spelling)
                    for child in node.get_children():
                        walk(child)

                walk(cursor)
                ext = cursor.extent
                funcs[cursor.spelling] = {
                    "name": cursor.spelling,
                    "file": str(Path(loc.file.name).resolve().relative_to(project_dir)),
                    "start": (ext.start.line, ext.start.column),
                    "end": (ext.end.line, ext.end.column),
                    "complexity": complexity,
                    "calls": calls,
                }
        for child in cursor.get_children():
            visit(child)

    visit(tu.cursor)
    return funcs


def main():
    ccdb_dir = Path(sys.argv[1]).resolve()
    out_path = Path(sys.argv[2]) if len(sys.argv) > 2 else None
    project_dir = ccdb_dir.parent if ccdb_dir.name == "firmware" else ccdb_dir

    ccdb = json.loads((ccdb_dir / "compile_commands.json").read_text())
    index = cindex.Index.create()

    # Cross-compilation flags are irrelevant for symbol extraction and break
    # host-side header lookup; drop them and parse in the ccdb directory so
    # relative -I paths resolve.
    import os

    os.chdir(ccdb_dir)
    skip = {"-c", "-o", "-mthumb"}
    skip_prefix = ("-target", "-mcpu", "arm-")

    functions = {}
    for entry in ccdb:
        src = (ccdb_dir / entry["file"]).resolve()
        raw = entry.get("arguments") or entry["command"].split()
        args = [
            a
            for a in raw[1:]
            if not a.endswith((".c", ".o"))
            and a not in skip
            and not a.startswith(skip_prefix)
            and a != entry["file"]
        ]
        tu = index.parse(str(src), args=args)
        for d in tu.diagnostics:
            if d.severity >= cindex.Diagnostic.Error:
                print(f"warn: {src.name}: {d.spelling}", file=sys.stderr)
        functions.update(collect_functions(tu, project_dir))

    defined = set(functions)
    lines = ["## Símbolos Extraídos do Código-Fonte", ""]
    lines.append(
        "Os objetos a seguir foram gerados automaticamente a partir da análise"
        " estática das unidades de compilação (libclang)."
    )
    lines.append("")
    for name in sorted(functions):
        f = functions[name]
        lines.append(f"### SYMBOL: {name} @{name}")
        lines.append("")
        lines.append("> kind: function")
        lines.append("")
        s, e = f["start"], f["end"]
        lines.append(f"> source: {f['file']}:{s[0]}:{s[1]}-{e[0]}:{e[1]}")
        lines.append("")
        lines.append(f"> complexity: {f['complexity']}")
        lines.append("")
        internal = sorted({c for c in f["calls"] if c in defined and c != name})
        if internal:
            links = ", ".join(f"[{c}](@)" for c in internal)
            lines.append(f"> calls: {links}")
            lines.append("")

    text = "\n".join(lines) + "\n"
    if out_path:
        out_path.write_text(text)
        print(f"{len(functions)} symbols -> {out_path}", file=sys.stderr)
    else:
        sys.stdout.write(text)


if __name__ == "__main__":
    main()
