---
modulo: DocumentMarks.dll
funcao: DocumentMarks::PDFPlusBearerBar::getMarkType
endereco: 0x18012EB70
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x180131FE0
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18012EB70

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x180131FE0`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18012EB70`
- simbolo: `DocumentMarks::PDFPlusBearerBar::getMarkType`
- assinatura: `basic_string_view<char,std::char_traits<char>_> getMarkType(PDFPlusBearerBar * this)`
- corpo: `0x18012EB70`..`0x18012EB7D` (14 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x180131FE0`

## O que faz

Identidade de tipo: devolve um std::basic_string_view<char> montado a partir do par (ponteiro, tamanho) em .rdata 0x180316458. O simbolo que o Ghidra gerou para esse par e PTR_s_DynamicObject_PDFPlusBearerBar_180316458, o que sugere o literal DynamicObject.PDFPlusBearerBar; os bytes do literal nao foram capturados no bruto (ver Lacunas).

String-chave de Bearer Bar: DynamicObject.PDFPlusBearerBar (por nome de simbolo)

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

## Strings referenciadas no corpo

- nenhuma (o corpo so referencia vftables, dados ou outras funcoes)

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual class std::basic_string_view<char,struct std::char_traits<char> > __cdecl
   DocumentMarks::PDFPlusBearerBar::getMarkType(void)const __ptr64 */

void __thiscall DocumentMarks::PDFPlusBearerBar::getMarkType(PDFPlusBearerBar *this)

{
  undefined8 uVar1;
  undefined8 *in_RDX;
  
                    /* 0x12eb70  1924
                       ?getMarkType@PDFPlusBearerBar@DocumentMarks@@UEBA?AV?$basic_string_view@DU?$char_traits@D@std@@@std@@XZ
                        */
  uVar1 = _UNK_180316460;
/* ... 4 linhas omitidas; ver bruto */
```

## Lacunas

- O literal devolvido por getMarkType nao aparece em [STRINGS_REFERENCED] nem em raw_v240/_strings_keywords.txt: apenas o simbolo PTR_s_DynamicObject_PDFPlusBearerBar_180316458. Nao foi possivel provar o texto exato nem o tamanho do string_view.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18012EB70.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
