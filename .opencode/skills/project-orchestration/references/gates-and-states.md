# Gates e máquina de estados

O estado **não é negociado**: é o que `python scripts/gate.py` deriva. O `INVENTORY.md` transcreve.
Estados abaixo são os valores aceitos por `gate.py` (`STAGES` + terminais).

## Estados da feature (INVENTORY)

| Estado | Critério comprovado pelo gate | Quem produz o artefato |
|---|---|---|
| `triado` | identidade + superfície + dependências + SHA-256 | `rea` |
| `analisado` | funções principais com endereço, xrefs e confiança | `ghidra` |
| `comportamento` | ferramenta operada e capturada com `CAP-*` | `comportamento` |
| `spec` | `--stage spec` = 0 (8 seções + evidência) | `documentacao` |
| `arquitetado` | `--stage adr` = 0 (ADR aprovada + mapa função→classe) | `arquitetura` |
| `implementado` | `--stage code` = 0 (arquivos + build real) | `implementacao` |
| `testado` | `--stage test` = 0 (teste cita F-### e passa) | `testes` |
| `auditado` | `--stage audit` = 0 (laudo + token + build/test) | `auditor` |
| `bloqueado` | linha na tabela de `HALT.md`/`BLOQUEIOS.md`; não é estado de progresso | `orquestrador` |
| `fora-do-escopo-v24` | evidência negativa na v24 + spec + ADR; sem código/teste | `orquestrador` + `documentacao` |

- O estado de uma **feature** é independente das demais. Não existe estado por módulo que exija
  "todas as features auditadas" — isso não é verificável e já gerou divergência de inventário.
- Divergência `declarado > comprovado` é erro de contrato: rebaixe no INVENTORY antes de seguir.
- Feature presente em artefato e ausente do INVENTORY é lacuna de rastreabilidade: registre.

## Gate de liberação

| Para liberar | Exija | Rejeite se |
|---|---|---|
| `ghidra` | triagem ou projeto existente | pedido duplicado de import |
| `comportamento` | prova em `tools/test_documents` | original será aberto direto |
| `documentacao` | 1 evidência estática + 1 comportamental | só string ou só screenshot |
| `arquitetura` | spec `status: spec` completa | seção “Em aberto” com regra central |
| `implementacao` | ADR aprovada + arquivos declarados | “ajusta aí” sem contrato |
| `testes` | código compilando | build quebrada por toolchain |
| `auditor` | teste passando + evidência | “funciona na minha máquina” |

## Exemplo de despacho

```
ALVO: DocumentMarks.dll / Trim Marks
SPEC: F-025
SAÍDA: rag/evidence/F-025/ghidra/, docs/reverse-engineering/DocumentMarks_FUNCTIONS.md
ACEITE: funções de criação de marca com endereço, xrefs e strings de UI; confiança declarada
LIMITE: 40 passos, 90 min, 8 funções
CONTEXTO: projeto ArtProPlus já importado; não reimportar; triagem em DocumentMarks_TRIAGE.md
```

## Quando o gate não fecha

- Evidência impossível: registre em `manifest.json` → `bloqueios` com motivo e screenshot/log.
- Conflito entre agentes: `docs/agents/CONFLITOS.md` antes de qualquer código.
- Módulo gigante: divida por funcionalidade (`F-025a`, `F-025b`), nunca por “terminar o módulo”.

## Registro de ciclo

Atualize `INVENTORY.md`, `ROADMAP.md`, `FEATURE_MATRIX.csv`, `docs/phases/STATUS.md` e
`docs/agents/CHECKPOINT.md` no mesmo ciclo, **depois** de rodar o gate. Estado desejado não
substitui estado real. Use um único escritor (o orquestrador).
