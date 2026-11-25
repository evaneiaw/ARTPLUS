# ADR-006 — Save Document (F-006) — CONSOLIDADO

> **Este arquivo não é mais uma ADR.** Foi consolidado em
> `docs/decisions/ADR-006-save-document.md`, que é a **única ADR canônica de F-006**
> (`Estado: aprovado`, aprovada em 2026-11-24).
>
> Motivo da consolidação: existiam dois documentos de decisão para F-006 com estados
> divergentes, e o mapa função→classe daqui continha um mapeamento **falso** (ver abaixo).
> Dois ADRs para a mesma funcionalidade produzem duas verdades; a convenção do projeto é
> `docs/decisions/ADR-###-<slug>.md` (AGENTS.md §4).

## O que este arquivo continha de errado

| Item | Conteúdo anterior | Correção (evidência) |
|---|---|---|
| `0x1802ad5eb` | mapeado para `DocumentSaveManager::applyEncryption()` | É `GODocument::SignOnSave(GODocument*, GODocSignParams*)` — **assinatura digital**, não criptografia (`rag/evidence/F-006/ghidra/Document__1802ad5eb.md`) |
| `0x180099710` (NDL) → `saveDocument()` | linha do mapa com endereço errado | `NDLModel::SaveDocument` é `0x180021990` (`Document__180099710.md` é `ArtDoc::Document::Save`) |
| `0x1802ad561` → "gravação proprietária" | sugeria que o corpo da gravação foi recuperado | é **trampolim por jumptable**; o corpo e o layout do container **não** foram recuperados (`Document__1802ad561.md`) |
| Seções §2–§8 | duplicavam regras, exceções e contrato da spec/ADR | duplicidade removida; a fonte é a spec F-006 + ADR canônica |
| `## Estado` | `proposto` | substituído por `aprovado` **no ADR canônico** |

## Onde está o quê agora

- **Decisão de arquitetura (normativa):** `docs/decisions/ADR-006-save-document.md`.
- **Visão do módulo (diagramas, fluxo de dados, dependências, testes planejados):**
  `docs/architecture/F-006-SaveDocument.md`.
- **Especificação funcional:** `docs/features/F-006.md`.
- **Evidência estática:** `rag/evidence/F-006/ghidra/`. **Comportamental:**
  `CAP-20261124-01` (v24.03.10017, 2026-11-24) — `docs/behavior/F-006.md`. O registro
  anterior `CAP-BLOCKED-006` está **SUPERADO**.

## Regra de manutenção

Não recrie conteúdo de decisão neste arquivo. Alteração de decisão de F-006 acontece
somente em `docs/decisions/ADR-006-save-document.md`; este arquivo pode ser removido pelo
`orquestrador` quando as referências em `docs/audit/F-006-audit.md` e
`docs/phases/REPOSITORY_RECONCILIATION.md` forem atualizadas.
