# HALT — escopo de bloqueio de funcionalidades

**Estado: ATIVO com escopo reduzido** · Atualizado em: 2026-11-24
**Origem:** ordem do proprietário "Retomada — desenvolvimento autônomo do ArtPlus"
(encerra a fase de infraestrutura; SET-1, SET-2A e SET-2C concluídos).

Este arquivo **não** é mais uma parada global. Ele delimita o que continua bloqueado.

## Bloqueado (não avançar)

| Item | Motivo | Registro |
|---|---|---|
| F-007 — Step & Repeat | BLO-008: existência provada em CAP-20261124-01; campos do `Make Grid` não medidos (janela em branco) | `docs/agents/BLOQUEIOS.md` |
| Qualquer tarefa cuja pré-condição de evidência não exista | `AGENTS.md §6.1` (evidência primeiro) | — |

Também é proibido: inventar comportamento do ArtPro+, publicar placeholder como
funcionalidade concluída, ou aprovar etapa cujo gate reprovou.

## Liberado

- Desenvolvimento das features com evidência/spec viável: implementação, testes,
  build, integração e auditoria.
- Correção de build e de testes (BLO-006) — é pré-requisito de todo o resto.
- Correção do sistema de agentes, evidência e documentação de estado.
- `implementacao`, `testes`, `documentacao` e `arquitetura` podem ser despachados para
  trabalho de feature **desde que** a feature não esteja na tabela acima.

## Efeito no gate

`python scripts/gate.py --halt` e `--all` retornam **2** enquanto este arquivo existir — isso
agora significa "existe escopo bloqueado declarado", **não** "nenhuma funcionalidade pode
avançar". O controle operativo passa a ser por etapa:

```powershell
python scripts/gate.py --feature F-### --stage evidence|spec|adr|code|test|audit
```

`0` = etapa comprovada · `1` = não comprovada · `2` = bloqueada por este escopo · `3` = erro.

## Como sair

O proprietário remove este arquivo quando os bloqueios forem resolvidos. (BLO-003/005 resolvidos em 2026-11-24; resta BLO-008 de Step & Repeat — captura de campos do `Make Grid`. BLO-004/Color Management resolvido em 2026-11-22.)
