# specc-demo

Example project for [SpecCompiler](https://github.com/SpecIR/SpecCompiler) — a typed,
compiled specification authored in CommonSpec (a small convention layer
over CommonMark).

This is the running example of the SpecCompiler dissertation: the
specification of a digital-clock firmware, compiled with the `sw_docs`
model.

> Click **Use this template** above to scaffold your own SpecCompiler
> project from this layout.

Source files:

- [`srs.md`](srs.md) — requirements (`AL-001`, `TM-001`, `DP-001`) and
  the data dictionary, referenced inline via `[dic:...](#)`.
- [`sdd.md`](sdd.md) — design (`AL-004`, `TM-004`), software units
  (`AL-005`, `TM-005`) and the code symbols they implement.
- [`svc.md`](svc.md) — verification cases with input/procedure/expected
  and the auto-generated traceability matrix (`traceability_matrix:`).
- [`tr.md`](tr.md) — test results (`Pass`/`Fail`); in a real pipeline
  these objects are generated from JUnit XML reports.
- [`symbols.md`](symbols.md) — **generated, do not edit**: SYMBOL
  objects extracted from the firmware C sources by
  [`scripts/extract_symbols.py`](scripts/extract_symbols.py) (libclang),
  including the `calls:` graph used for impact analysis.
- [`firmware/`](firmware/) — the digital-clock C sources the
  specification describes (`alarm.c`, `time_manager.c`, ...), with the
  `compile_commands.json` used by the symbol extractor. The `CSU`
  objects in `sdd.md` point at these files via `file_path`.

Build:

```sh
specc build project.yaml
```

Regenerate symbols (requires `python3-clang`):

```sh
python3 scripts/extract_symbols.py firmware symbols.md
```

Identifiers use a module + sequence scheme (`AL-001`) instead of
embedding the object type: the type comes from the CommonSpec
annotation (`## HLR: ... @AL-001`), not from the identifier.
