# Auditoria F-006 — Save Document
Data: 2026-11-21 · Auditor: auditor-subagent
Veredito: REPROVADO

## Evidência verificada
| Item | Esperado | Encontrado | OK |
|---|---|---|---|
| Spec completa | `docs/features/F-006.md` com entrada, UI, regras, exceções, saída | Presente ✓ | ✓ |
| ADR-006 com mapa função→classe | `docs/architecture/F-006-ADR.md` | Presente ✓ | ✓ |
| Código compilado e passando build | Build release-mingw limpo + ctest passa | **Não** — build falhou (ver abaixo) | ✗ |
| Teste citando F-006 existente | Teste unitário/integração que cobre F-006 | **Inexistente** (`tests: []` em F-006.md); ctest reportou "No tests were found!!!" | ✗ |
| Hash SHA-256 da evidência | `manifest.json` com hash correspondente ao binário | Manifest existe com hash referente ao `Document.dll` v24.03 | ✓ (reference) |

## Build (executado)
- Comando (powershell):
  ```powershell
  $cmake = 'C:\Users\Evanei\AppData\Local\Microsoft\WinGet\Packages\Kitware.CMake_Microsoft.Winget.Source_8wekyb3d8bbwe\cmake-4.4.4-windows-x86_64\bin\cmake.exe'
  Remove-Item -Recurse -Force build -ErrorAction SilentlyContinue
  & $cmake --preset mingw-msvcrt
  & $cmake --build --preset release-mingw
  ctest --preset unit-tests
  ```
- **Saída observada:**
  - Build compilou alvos `form_parser_probe`, `smask_probe`, `mirror_probe`, `page_placeholders`, `form_xobject_test`, `pdf_smoke` (7 alvos de probe).
  - Falhou ao compilar o alvo principal `ArtPlus`: erro em `mocs_compilation.cpp` — `fatal error: opening dependency file CMakeFiles\ArtPlus.dir\ArtPlus_autogen\mocs_compilation.cpp.obj.d: No such file or directory`.
  - `ctest --preset unit-tests` reportou: **`No tests were found!!!`** (0 testes registrados).
- **Conclusão:** Build do alvo principal `ArtPlus` **não concluiu**; não há testes unitários configurados/registrados.

## Testes
- `ctest --preset unit-tests`: **Não executável** — 0 testes encontrados. O CMakePreset `unit-tests` não inclui testes para F-006; o `tests: []` em F-006.md confirma a ausência.
- Cobertura do F-006: **0/0** (nenhum teste cita F-006).
- Justificativa: Feature em fase de implementação reversa; testes comportamentais bloqueados por `CAP-BLOCKED-006` e falta de configuração de teste no CMake.

## Divergências (reiteradas + novas)
1. `src/document/document_save_manager.cpp:24-35` — `switchToWorkingFile()` é **simulado**, não verifica `this+0x78 == 2` como spec/R1 exigem.
2. `src/document/document_save_manager.cpp:72-83` — Criptografia retorna erro "não suportada" (TODO F-006), não implementada conforme fluxo `0x180099710`.
3. `src/document/document_save_manager.cpp:87-92` — Flavour != NormalPDF força `SaveException(8)`, mas spec diz ramos dedicados para Flavour 1/2.
4. `src/document/document_save_manager.cpp:96-98` — `noOptimizedSave` apenas registra `qDebug() << "TODO"`; não altera comportamento.
5. `src/document/document_save_manager.cpp:117` — `DocumentSerializer::save()` reutiliza **Serializer JSON existente**, não gravação proprietária `GODocument::Save` (`0x1802ad561`).
6. `src/document/document_save_manager.cpp:144-178` — `applyEncryption` retorna `true` apenas se `encryptionLevel == 0`; não executa `Security::GetEncryption/GetPassword` + `SetNew*`.
7. `src/document/document_save_manager.cpp:145-195` — `deriveBackupPath` usa `.bak` provisório; não implementa `FUN_180095230`.
8. `src/document/document_save_manager.cpp:180-195` — `finalizeState` não chama `SwitchToWorkingFile`, não implementa `ChangeCollector::NotifyChangesCollected`.

## O que falta para aprovar
- [ ] **Resolver erro de build** em `mocs_compilation.cpp` (verificar geração de arquivos `.d` de dependência, limpar `build/` e reexecutar CMake).
- [ ] **Configurar/registrar testes unitários** que cubram `Save`/`Save As`, incremental save e backup logic, citando F-006.
- [ ] **Implementar lógicas críticas** (switchToWorkingFile, criptografia, deriveBackupPath, gravação proprietária em vez de JSON serializer).
- [ ] **Reexecutar ctest** e colar saída completa para validade.

## Próximos passos recomendados
1. Limpar `build/` completamente e verificar CMakePreset `mingw-msvcrt`/compilação do alvo `ArtPlus`.
2. Adicionar testes `tests/document_save_test.cpp` usando `QTEST` ou similar, invocando `DocumentSaveManager::save()`.
3. Fechar TODOS os `TODO(F-006)` com implementação real extraída de Ghidra/REA.
4. Reauditar gerando `F-006-audit-2.md` após correções.

---

**Nota:** O build produziu 7 alvos `probe` (utilitários de teste) mas **não** produziu o executável principal `ArtPlus` nem registrou testes unitários. Sem o build limpo do alvo principal e testes que citam F-006, a auditoria **não pode ser aprovada**. Esse laudo substitui o anterior `docs/audit/F-006-audit.md`.