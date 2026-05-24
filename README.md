# specc-demo

Minimal example project for [SpecCompiler](https://github.com/SpecIR/SpecCompiler) — a typed,
compiled specification authored in CommonSpec (a small convention layer
over CommonMark).

> Click **Use this template** above to scaffold your own SpecCompiler
> project from this layout. The CI workflow is portable: it pulls the
> public upstream image and uses your fork's repo settings (Pages URL,
> tags, releases) automatically.

Three source files:

- [`srs.md`](srs.md) — Software Requirements Specification with two
  typed High-Level Requirements (`HLR-042`, `HLR-043`).
- [`sdd.md`](sdd.md) — Software Design Description with one Design
  Decision (`DD-001`), two Low-Level Requirements (`LLR-001`, `LLR-002`)
  tracing back to the HLRs, and a PlantUML sequence diagram rendered
  into the output.
- [`svc.md`](svc.md) — Software Verification Cases with one VC
  (`VC-020`) that covers both HLRs, plus a generated traceability
  matrix.

[`project.yaml`](project.yaml) wires them into the stock `sw_docs`
model. Compilation produces:

- `build/www/` — interactive HTML with cross-document anchors and
  rendered diagrams.
- `build/docx/` — formal-review DOCX deliverables.
- `build/specir.db` — the SQLite intermediate representation
  (compiled facts queryable directly).

## Local build

Requires `specc` installed locally:

```
specc build project.yaml
```

Or via Docker, no local install needed:

```
docker run --rm -v "$PWD:/workspace" -w /workspace \
  ghcr.io/specir/speccompiler:latest \
  /opt/speccompiler/bin/speccompiler-core project.yaml
```

## Continuous integration

[`.github/workflows/build.yml`](.github/workflows/build.yml) runs on
every push and PR. It pulls
[`ghcr.io/specir/speccompiler:latest`](https://github.com/SpecIR/SpecCompiler/pkgs/container/speccompiler),
builds HTML and DOCX, and exports ReqIF for all three specs with
`python3 -m reqif.specir export`.

Workflow artifacts on every successful run:

| Artifact | Contents |
|---|---|
| `html` | `srs.html`, `sdd.html`, `svc.html`, `index.html` (web app) |
| `docx` | `srs.docx`, `sdd.docx`, `svc.docx` |
| `reqif` | `srs.reqif`, `sdd.reqif`, `svc.reqif` |
| `specir-db` | `specir.db` (SQLite IR) |

If `speccompiler-core` exits non-zero (missing trace link, invalid
date cast, bad enum value), the workflow fails and no artifacts are
uploaded.

### GitHub Pages

On pushes to `main` *and* on every tag push, the HTML site is
deployed to GitHub Pages — for the upstream repo, that lands at
<https://specir.github.io/specc-demo/>; for a fork or a
template-copy, GitHub uses your own `<owner>.github.io/<repo>/` URL.
Last deploy wins; the `pages` concurrency group serializes them.

**One-time repo setup:** Settings → Pages → **Source: GitHub
Actions** (not "Deploy from a branch"). Without this, the
deploy-pages job fails with a 404.

### Releases

On any tag push (`git tag v0.1 && git push origin v0.1`), the
workflow creates a GitHub Release named after the tag, with all
three `.docx` files and all three `.reqif` files attached as release
assets and auto-generated release notes from the commit log.

## License

Apache 2.0.
