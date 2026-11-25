---
description: Painel de status da extracao (dossies, funcoes, fila, relatorio)
agent: orquestrador
---

Status lido de `dossiers/*/manifest.json`, `docs/phases/OVERNIGHT-*.md` e `logs/auto/extract-detached.log`.

```
ALVO: painel do pipeline de extração (dossiês, funções, fila)
SPEC: não se aplica (somente leitura)
SAÍDA: painel de `python scripts/status.py --text`
ACEITE: painel executado com exit 0 e números lidos da saída real
LIMITE: não grava JSON/HTML nem inicia `--watch` sem pedido
FALHA: se o painel falhar, reporte o erro exato (não invente números)
```

```
!`python scripts/status.py --text`
```

O painel acima é o status atual. Não repita os números no texto; apenas responda com uma linha
de leitura (fase, fila, bloqueios). Se o bloco ``!`…` `` não executar, peça ao subagente `testes`
para rodar `python scripts/status.py --text` e use a saída.

Dashboard com auto-refresh: `docs/status/dashboard.html` (abrir no navegador).
JSON consumivel por script: `logs/auto/status.json`. Atualizacao continua: `python scripts/status.py --watch 2`.
