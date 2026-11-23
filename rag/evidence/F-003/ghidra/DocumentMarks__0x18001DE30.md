---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::regenerateMarkImp
endereco: 0x18001DE30
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18001FDB0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001DE30

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18001FDB0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18001DE30`
- simbolo: `DocumentMarks::BearerBar::regenerateMarkImp`
- assinatura: `void regenerateMarkImp(BearerBar * this)`
- corpo: `0x18001DE30`..`0x18001E417` (1511 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18001FDB0`

## O que faz

Geracao da geometria do Bearer Bar legado: emite 1 Path por bit ligado de Location, insere os Paths depois da origem, remove os filhos excedentes e aplica a cor (applyColor); emite o log ' Bearer Bar update' quando o nivel de debug e maior que 2. Corpo de 1511 bytes; as strings de rotulo L/B/R/T e W/H pertencem a esse log.

String-chave de Bearer Bar:  Bearer Bar update (com quebra de linha) e os rotulos [ L: / W: / H: / B: / R: / T:

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (22):

- `1800f42c0 FUN_1800f42c0`
- `1802cbea4 API-MS-WIN-CRT-HEAP-L1-1-0.DLL::free`
- `18001cc60 FUN_18001cc60`
- `EXTERNAL:000001e4 DOCUMENT.DLL::ArtDoc::Fillable::IsFilled`
- `1801160f0 DocumentMarks::GetMarksDebugLevel`
- `1802cbe68 FUN_1802cbe68`
- `1800943e0 DocumentMarks::DynamicObject::applyColor`
- `180019300 FUN_180019300`
- `EXTERNAL:000001eb DOCUMENT.DLL::ArtPaint::FlatPaint::Factory::Get`
- `1800f46a0 FUN_1800f46a0`
- ... mais 12 no bruto

## Strings referenciadas no corpo

- `1802fa208 " Bearer Bar update\n"`
- `1802fa220 "   Reference object Bbox mm:"`
- `1802fa298 "[ <initial/default state> ]"`
- `1802fa2b8 ", H: "`
- `1802fa2c0 " (W: "`
- `1802fa2c8 ", B: "`
- `1802fa2d0 ", R: "`
- `1802fa2d8 ", T: "`
- `1802fa2e0 "[ L: "`

## Pseudocodigo (inicio; integral no bruto)

```c
/* protected: virtual void __cdecl DocumentMarks::BearerBar::regenerateMarkImp(void) __ptr64 */

void __thiscall DocumentMarks::BearerBar::regenerateMarkImp(BearerBar *this)

{
  int *piVar1;
  longlong *plVar2;
  int iVar3;
  ContentObject *pCVar4;
  double dVar5;
  double dVar6;
  double dVar7;
  double dVar8;
  bool bVar9;
/* ... 269 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001DE30.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
