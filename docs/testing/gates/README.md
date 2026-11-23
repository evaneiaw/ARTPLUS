# Artefatos gerados pelo `scripts/gate.py`

Não editar à mão. Cada arquivo é produzido por uma execução real e verificado por hash.

| Arquivo | Origem | Conteúdo |
|---|---|---|
| `build.json` | `gate.py --build` | comando, exit code, log e `log_sha256`, `build_dir` |
| `logs/build-*.log` | `gate.py --build` | stdout+stderr do configure/build |
| `F-###.xml` | `gate.py --feature F-### --run-test` | JUnit do CTest (caminho absoluto) |
| `F-###.test.json` | idem | comando, exit code, `xml_path`, `xml_sha256`, `tests`, `failures` |
| `logs/test-F-###-*.log` | idem | saída do CTest |
| `logs/ctest-full-20261121.log` | execução manual de auditoria | matriz completa de 11 testes |

Contrato e fórmula do token: `docs/testing/GATE.md`.

## Última medição (2026-11-21)

- Build: `exit_code=0`.
- F-001 CutMarkTests: pass (0.047 s).
- F-002 MarkSetProcessor: pass (0.021 s).
- F-003 BearerBarTests: **fail** — `testGeometryTopology_R4_R6`
  ("Compared values are not the same"), 1 de 11.
- F-004 SelectionMarkTests: pass (0.036 s).
- F-005 PdfRoundTrip: **fail** — 4 de 10 (`testImportVector`, `testImportImages`,
  `testImportMultiPage`, `testExportModifiedPdf`).
- F-006 SaveDocumentTests: pass (0.063 s).
- Matriz completa: 6/11 passam; falham `UnitTests`, `PdfRoundTrip`, `EditingTests`,
  `IntegrationTestBasic`, `BearerBarTests`.

`UnitTests` termina com exit `1` após `testColors` sem `<failure>` no JUnit; o gate
registra o exit code e não inventa causa.

Token atual de F-002: ver `python scripts/gate.py --feature F-002 --emit-token`
(muda a cada nova execução de build/teste — nunca copiar valor antigo para laudo).
