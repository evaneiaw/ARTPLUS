# BLOQUEIOS — bloqueios ativos

Registro obrigatório. Feature com bloqueio aqui aparece como `bloqueado` no `INVENTORY.md`
e **não é redistribuída** até resolução comprovada.

| ID | Feature | Etapa | Motivo | Evidência existente | Próximo passo |
|---|---|---|---|---|---|
| BLO-003 | F-007 (Step & Repeat) | Comportamento | CAP não capturado; UI v24 não produziu fluxo | `rag/evidence/F-007/` (estático, `versao: 24.0`), `LayoutEngine_GHIDRA.md` | capturar CAP real ou manter bloqueado |
| BLO-005 | F-006 (Save Document) | Build/Testes | build quebrado; criptografia não implementada; laudo reprovado | `SaveDocumentTests` (91 asserções), `docs/audit/F-006-audit.md` | corrigir build (ver BLO-006) e fechar `TODO(F-006)` ou reduzir escopo |
| BLO-006 | GLOBAL (build) | Build | **RESOLVIDO em 2026-11-21** — o build compila e linka 17 alvos (Release/MSVCRT), inclusive em clone limpo do commit `4b174c3`; ctest 11/11. Evidência: `docs/testing/gates/CLEAN_CLONE_BUILD.md`, `docs/testing/gates/build.json`, `docs/testing/gates/ctest-full.xml` | `build_audit` + logs em `docs/testing/gates/logs/` | nenhum — mantido apenas como histórico |


## Premissas refutadas (2026-11-21)

| Premissa | Status | Evidência |
|---|---|---|
| "HASP v240 impede execução comportamental no ArtPro+ v24.03.10017" (constava no manifest de evidência de Selection Mark) | **REFUTADA** | `docs/behavior/V24_RUNNABILITY_20261121.md`; `ArtPro+.exe` 24.03.10017 (sha256 `9d331661…0b0f03`) abre UI utilizável. O diálogo `ArtPro+ License Info` ("suboptimal combination…", `License Server: localhost`, edições Essentials/Layout/Digital = 24 dias, botão **Continue**) é **informativo**, não bloqueio. Sem serviço HASP, sem erro de DLL. Capturas `rag/evidence/v24_probe/behavior/shot-0{1,2,3}-*.png`. |

Consequência: as features de Mark Set, Selection Mark e Open Document **não** estão bloqueadas por licença. O que falta nelas é captura comportamental **na v24** — as capturas de Cut Mark e Bearer Bar existentes são da versão histórica e não substituem a versão-alvo.

> Nota de manutenção: este arquivo é lido por `scripts/gate.py` (`blocked_features()`), que trata
> **qualquer** token de identificador de feature citado no texto como bloqueio. Não cite
> identificadores de feature aqui fora da tabela de bloqueios — use o nome da funcionalidade.

## Observações

- `BLO-003` estava referenciado no `INVENTORY.md` mas **não existia neste arquivo** —
  inconsistência corrigida em 2026-11-21.
- `BLO-005` citava "permissão shell negada no orquestrador"; a causa real medida agora é
  build quebrado. O bloqueio foi reescrito com a causa verificável.
- Bloqueio não é desculpa para parar o projeto: só impede a feature bloqueada; as demais
  seguem (respeitado o HALT de recuperação).

## Premissas refutadas / achados negativos (2026-11-21)

| Item | Status | Evidência |
|---|---|---|
| Mark Set: o caminho de menu "Marks > Create > Mark Sets" não existe — a funcionalidade **existe**, mas no painel | **CORRIGIDO** | `CAP-20261121-03`: `Document > Marks > engrenagem ▾` traz `Load Mark Set...` e `Save/Delete Mark Set...`; o botão `+ ▾` traz `Add Cut Mark`, `Add Bearer Bar Mark`, `Add Dimensions Mark`, `Add External File Mark`, `Add Position Mark`, `Add Input File Mark` e `Add Repeat for Grid Mark`. O caminho em menu era da versão histórica. |
| Selection Mark: a ação "Selection Mark" não existe na UI | **NEGATIVO nos caminhos medidos** | `CAP-20261121-02` — `File`, `Object`, `Select`, `Prepress` e ribbon sem a ação; `Ctrl+Shift+S` é `Save as...`. `View`/`Window`/`Edit`/`Help` não medidos. |

## Premissas refutadas / achados negativos (2026-11-22)

| Item | Status | Evidência |
|---|---|---|
| Color Management: menu "Color > Color Management" não existe na v24; a UI real é Colors panel (toolbar), Recolor (Object), Convert Separations With (Prepress) | **CORRIGIDO** | `CAP-20261122-02`: UIA tree do diálogo Recolor (Remove/Replace/Convert Separations, lista Cyan/Magenta/Yellow/Black/PANTONE 485 C, botões Remove/Close); ausência confirmada de campos ICC/Rendering Intent/Black Point; Colors panel exibe Document Profile + separações. |