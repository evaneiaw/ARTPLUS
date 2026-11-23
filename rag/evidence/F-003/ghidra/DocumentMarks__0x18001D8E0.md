---
modulo: DocumentMarks.dll
funcao: DocumentMarks::BearerBar::parsePdfPropertiesDict
endereco: 0x18001D8E0
versao: 24.03.10017
confianca: alta
id_historico: GHIDRA-DocumentMarks-0x18001F870
---
# Evidencia Ghidra v240 - GHIDRA-DocumentMarks-0x18001D8E0

Arquivo de evidencia do **equivalente v240** do ID historico `GHIDRA-DocumentMarks-0x18001F870`.
O ID historico pertence ao layout do binario antigo (fora do fluxo ativo) e NAO identifica funcao
na versao de referencia; o endereco abaixo e o da v24.03.10017.

## Identificacao lida no programa v240

- endereco: `0x18001D8E0`
- simbolo: `DocumentMarks::BearerBar::parsePdfPropertiesDict`
- assinatura: `bool parsePdfPropertiesDict(BearerBar * this, map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_> * param_1)`
- corpo: `0x18001D8E0`..`0x18001DD91` (1195 bytes), convencao `__thiscall`, thunk=false
- ID historico correspondente: `GHIDRA-DocumentMarks-0x18001F870`

## O que faz

Parser virtual do dicionario de propriedades do PDF+: converte as chaves DM-BearerBarParams* de volta para os campos do objeto. Usa o nome de tipo BearerBar na mensagem de versao nao suportada, le Version (rejeita >= 3), Width/Extend/Offset (mm -> mp) e Location; IsVertical e tratado apenas na versao 1, conforme a analise registrada no ID historico. As 7 chaves DM-BearerBarParams* estao listadas abaixo.

String-chave de Bearer Bar: DM-BearerBarParams, DM-BearerBarParams-Width/Extend/Offset/IsVertical/Location/Version e literal BearerBar

## Chamadores (xrefs de chamada)

- nenhum chamador direto no programa (a funcao e virtual, exportada por vtable, ou so tem xref de dados)

Chamadas diretas (11):

- `180074c70 DocumentMarks::DynamicMark::parsePdfPropertiesDict`
- `EXTERNAL:000005ad API-MS-WIN-CRT-RUNTIME-L1-1-0.DLL::_invalid_parameter_noinfo_noreturn`
- `180100280 FUN_180100280`
- `EXTERNAL:000001e2 DOCUMENT.DLL::ArtDoc::Dictionary::GetFloatValue`
- `1802cbea4 API-MS-WIN-CRT-HEAP-L1-1-0.DLL::free`
- `EXTERNAL:000001ac DOCUMENT.DLL::ArtDoc::Dictionary::GetIntegerValue`
- `1802cbfd0 __security_check_cookie`
- `EXTERNAL:000001ad DOCUMENT.DLL::ArtDoc::Dictionary::GetDictionaryValue`
- `18000d740 FUN_18000d740`
- `EXTERNAL:000001a6 DOCUMENT.DLL::ArtDoc::ContentObject::GetContent`
- ... mais 1 no bruto

## Strings referenciadas no corpo

- `1802fa1f8 "BearerBar"`
- `18032fda8 "DM-BearerBarParams"`
- `180330128 "DM-BearerBarParams-Width"`
- `180330148 "DM-BearerBarParams-Extend"`
- `180330168 "DM-BearerBarParams-Offset"`
- `180330188 "DM-BearerBarParams-IsVertical"`
- `1803301a8 "DM-BearerBarParams-Location"`
- `1803301c8 "DM-BearerBarParams-Version"`

## Pseudocodigo (inicio; integral no bruto)

```c
/* WARNING: Function: __security_check_cookie replaced with injection: security_check_cookie */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* public: virtual bool __cdecl DocumentMarks::BearerBar::parsePdfPropertiesDict(class
   std::map<class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char>
   >,class ArtDoc::ContentObject * __ptr64,struct std::less<class std::basic_string<char,struct
   std::char_traits<char>,class std::allocator<char> > >,class std::allocator<struct std::pair<class
   std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > const ,class
   ArtDoc::ContentObject * __ptr64> > > const & __ptr64) __ptr64 */

bool __thiscall
DocumentMarks::BearerBar::parsePdfPropertiesDict
          (BearerBar *this,
          map<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>,ArtDoc::ContentObject*___ptr64,std::less<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_>,std::allocator<std::pair<std::basic_string<char,std::char_traits<char>,std::allocator<char>_>_const_,ArtDoc::ContentObject*___ptr64>_>_>
          *param_1)
/* ... 213 linhas omitidas; ver bruto */
```

## Lacunas

- Nenhuma lacuna de leitura: assinatura, xrefs e pseudocodigo presentes no bruto para este endereco.

## Confianca

`alta` - endereco, simbolo, assinatura e xrefs lidos diretamente no programa v240 (Ghidra 12.2 headless); a equivalencia ja havia sido provada na sonda dos 19 IDs historicos.

## Fonte

- modulo: `DocumentMarks.dll`
- versao de referencia: `24.03.10017`
- binario: `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\DocumentMarks.dll`
- bruto do equivalente: `rag/evidence/F-003/ghidra/raw_v240/addr_18001D8E0.txt`
- origem: Ghidra 12.2 headless; programa DocumentMarks.dll v24.03.10017; bruto em rag/evidence/F-003/ghidra/raw_v240
