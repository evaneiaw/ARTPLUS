---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::DumpInfo
endereco: 0x18001D0E0
versao: 24.03.10017
confianca: alta
id_historico: nenhum (funcao auxiliar v240, fora de estatico)
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001D0E0 (DumpInfo)

`DocumentMarks::BearerBar::DumpInfo` nao tem ID historico v25 atribuido nesta passada; o arquivo
registra a funcao lida no programa v240 por ser a rotina que formata o estado do objeto para debug.

## Identificacao lida no programa v240

- endereco: `0x18001D0E0`
- simbolo: `DocumentMarks::BearerBar::DumpInfo`
- assinatura: `pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,std::basic_string<char,struct_std::char_traits<char>,class_std::allocator<char>_>_> DumpInfo(BearerBar * this)`
- corpo: `0x18001D0E0`..`0x18001D44B` (876 bytes), convencao `__thiscall`

## O que faz

Monta o par (chave, valor) de depuracao do Bearer Bar: prefixo literal BearerBar( seguido de width=, , extend=, , offset= e , location= com os campos formatados. O mesmo corpo contem ainda o literal Dynamic Barcode Mark: Empty code, de uma rotina de dump vizinha no mesmo modulo. Nao gera geometria.

String-chave de Bearer Bar: `BearerBar(`, `width=`, `, extend=`, `, offset=`, `, location=`

## Chamadores (xrefs de chamada)

- nenhum chamador direto (membro virtual: acionado pela vtable)

## Strings referenciadas no corpo

- `1802f9df8 "Dynamic Barcode Mark: Empty code"`
- `1802fa240 "BearerBar("`
- `1802fa250 "width="`
- `1802fa258 ", extend="`
- `1802fa268 ", offset="`
- `1802fa288 ", location="`

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual struct std::pair<class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> >,class std::basic_string<char,struct std::char_traits<char>,class
   std::allocator<char> > > __cdecl DocumentMarks::BearerBar::DumpInfo(void)const __ptr64 */

void __thiscall DocumentMarks::BearerBar::DumpInfo(BearerBar *this)

{
  uint uVar1;
  double dVar2;
  double dVar3;
/* ... 119 linhas omitidas; ver bruto */
```

## Confianca

`alta` - simbolo, assinatura, strings e corpo lidos diretamente no programa v240; a funcao nao entra
na lista `estatico` do manifest porque nao corresponde a nenhum ID historico.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto: `rag/evidence/F-003/ghidra/raw_v240/addr_18001d0e0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
