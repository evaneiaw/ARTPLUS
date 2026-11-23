# Document.dll - Triagem Estática (REA)

## Identidade
- **Compilador**: Microsoft Visual C/C++ 19.41.34435 (Visual Studio 2022)
- **Linker**: Microsoft Linker 14.41.34435
- **Arquitetura**: PE64
- **Assinatura**: Windows Authenticode (PKCS #7)
- **Dados de Depuração**: POGO (PGO - Profile Guided Optimization)
- **Dependências**: libpng (detectado), Microsoft C/C++ Runtime [dynamic]

## Metadados PE
- **Hash SHA-256**: 0aa0311cfcdaedf8028a626ac751ee0b5cce5e000f3ac551d9d291b250038160
- **Tamanho**: 4,447,272 bytes
- **Seções**: .text (0x12D238B), .rdata, .data, .pdata, .rsrc, .reloc, .fnp_dir, .fnp_mar

## Superfície Funcional
Strings Unicode notáveis (extraídas via `strings64 -n 8`):
- `ArtDoc`, `LayerProperties`, `ContentObject`, `Group`, `Text`, `Path`, `Strokable`, `Fillable`, `Transformable`, `Blendable`
- `ChangeCollector`, `SeparationInUseChange`, `ObjectChanged`, `WhatChangedFlags`
- `AEBVContent`, `AEBVContent@ArtDoc@@`, `AEBVPath`, `AEBVFillable`, etc.
- Múltiplas funções com `sp_counted_impl_pd` indicando uso extensivo de `boost::signals2` e referências compartilhadas (`shared_ptr`)

Indica que este módulo central implementa o modelo de documento (`ArtDoc`), gerenciamento de camadas/objetos (`LayerProperties`, `ContentObject`) e manipulação de separações/estados de mudança. O uso de `signals2` do Boost sugere um padrão de observador/assíncrono amplamente usado no ArtPro+.

## Importações / Exportações
- **Imports**: Exporta/importa com diversas DLLs internas Esko (DocumentMarks.dll, PDFAccessLayer.dll, PDFObjectLayer.dll, NDLModelLocal.dll, etc.) e Qt6, além de APIs do Windows (KERNEL32, USER32, OLEAUT32, etc.).
- **Exports**: Necessita análise via Ghidra/REA para mapear nomes de funções exportadas e RTTI.

## Alvos Prioritários para Ghidra
- Funções relacionadas ao tipo `ArtDoc` e `ContentObject` (RTTI vtable)
- Funções que manipulam `Group`, `Text`, `Path`, `Strokable`, `Fillable` objects
- Funções de separação e mudança de estado (`ChangeCollector`, `WhatChangedFlags`)
- Endereços após importação completa.

## Confiança
Alta — metadados PE consistentes, strings complexas e estrutura de Boost signals2 confirmam o papel central neste módulo.

## Evidência Bruta
- JSON DIE: `rag/sources/Document.dll.json`
- Strings (amostra): `rag/sources/Document.dll.strings.txt`

## Próxima Ação
Importar no Ghidra 12.2 (headless) para extrair call graph, vtables/RTTI e endereços precisos. Marcar módulo como `analisado` no INVENTORY após análise de funções principais.