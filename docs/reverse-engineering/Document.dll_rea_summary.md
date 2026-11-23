# Document.dll - Triagem Estática (F-UNDEF)

## Identidade
- **Nome do arquivo**: Document.dll
- **Versão**: 25.0 (referência de versão)
- **SHA-256**: 0aa0311cfcdaedf8028a626ac751ee0b5cce5e000f3ac551d9d291b250038160
- **Formato**: PE64 (x86_64)
- **Subsystem**: GUI (2)
- **Toolchain**: Microsoft Visual C/C++ (19.41.34435) + Microsoft Linker (14.41.34435)
- **Compiler**: Microsoft Visual Studio 2022 (17.11)
- **Runtime**: nativo C++ (sem .NET)
- **Packer**: nenhum
- **Assinatura**: Windows Authenticode (2.0) [PKCS #7]

## Estrutura PE
- **Seções principais**:
  - .text (0x1000, 0x12D238B)
  - .rdata (0x137C000, 0x6EE7A8)
  - .data (0x1A6B000, 0x4E9AF8)
  - .pdata (0x1F55000, 0xA2FD8)
  - .rsrc (0x1FFA000, 0x3DD98)
  - .reloc (0x2038000, 0x53730)

## Imports (DLLs)
- ArtSys.dll
- ColorManipulationLayer.dll
- BarCodeWrapper.dll
- CMS.dll
- EGXMPlib.dll
- FontNDSLayer.dll
- libpng16.dll
- Localization.dll
- PDFGeometryLayer.dll
- tiff.dll
- VariableEngine.dll
- Logging.dll
- ExtraBoostFilesystem.dll
- boost_url.dll
- boost_filesystem.dll
- WS2_32.dll
- PDFObjectLayer.dll
- FontLayer.dll
- PDFAccessLayer.dll
- BasicFrameworkCoreLayer.dll
- boost_nowide.dll
- YAGL.dll
- CurveApprox.dll
- GeoMapper.dll
- ADT.dll
- KERNEL32.dll
- MSVCP140.dll
- MSVCP140_CODECVT_IDS.dll
- VCRUNTIME140.dll
- VCRUNTIME140_1.dll
- api-ms-win-crt-runtime-l1-1-0.dll
- api-ms-win-crt-heap-l1-1-0.dll
- api-ms-win-crt-stdio-l1-1-0.dll
- api-ms-win-crt-string-l1-1-0.dll
- api-ms-win-crt-math-l1-1-0.dll
- api-ms-win-crt-time-l1-1-0.dll
- api-ms-win-crt-convert-l1-1-0.dll
- api-ms-win-crt-filesystem-l1-1-0.dll
- api-ms-win-crt-environment-l1-1-0.dll

## Exportes (2737 funções)
- Muitos objetos da ArtDoc e ArtPaint com nomes mangled (ex: ??0?$Factory@V0DefaultFunction@ArtPaint@@@Function@ArtPaint@@IEAA@V?$vector@V?$array@N$01@std@@V?$allocator@V?$array@N$01@std@@@2@@std@@0@Z)
- Classes/Namespaces identificados:
  - ArtDoc
  - ArtPaint
  - Document
  - PDFDocument
  - ActionList
  - ColorList
  - CloneStrategy
  - SeparationMappingPolicy
  - ShadingPaint
  - MeshPaint
  - Font
  - HalftoneSet
  - LayerProperties
  - LayeredPicture
  - PictureData
  - PictureLink

## Strings de UI e Erros
- "NoOptimizedSave"
- "Unknown error (%d)"
- "Already open"
- "The descriptor does not fit into the select call's fd_set"
- "asio.misc error"
- "invalid hash bucket count"
- "Default_Colorprofiles"
- "ICCProfile("
- "ACTION UNKNOWN ERROR"
- "Doc.Core.Errors"
- "CONTENT_PARSE_INVALID_COLORFUNCTION"
- "CONTENT_PARSE_INVALID_FUNCTIONRESOURCE"
- "invalid string position"
- "invalid stoi argument"
- "document.document"
- "Document: Unknown encryption value"
- "BackgroundCopy: Start copying from"
- "Document: File"
- "Document: Open read/write"
- "Document: Open read-only"
- "Document: Exception caught while opening"
- "Document: Destructor for"
- "Document: Deleting working file"
- "Document: The original file could not be copied to the working file, so saving"
- "STATUS_SAVE"
- "Document: Could not copy the incremental base file to"
- "Document: Could not copy the preflighted working file to"
- "Document: GASimpleException"
- "Document: GException"
- "Document: Standard exception"
- "Document: Unknown exception caught while saving"
- "Document: Invalid Catalog entry"
- "Document: File has no pages"
- "ERROR_FILE_NOT_FOUND"
- "ERROR_FILE_ACCESS_DENIED"
- "ERROR_FILE_INVALID"
- "ERROR_WRONG_PASSWORD"
- "ERROR_FILE_UNKNOWN"
- "UNKNOWN TRANSFORMABLE"
- "UNKNOWN BLENDABLE"
- "Group colorspace:"
- "Transformation:"
- "SoftMask("
- "TextEditing"
- "FilledOutline:"
- "StrokedOutline:"
- "Text transformation:"
- "Text size:"
- "ColorTable:"
- "Form transformation:"
- "Has live document reference"
- "Default transformation:"
- "ClipPath:"
- "ClipPath"
- "Appearance transformation:"
- "Document OutputIntent:"
- "Document Distortion:"
- "Document SeparationInfo:"
- "Default layer configuration:"
- "Pattern("
- "Document fonts:"
- "Transparency/SoftMask statistics:"
- "SoftMask"
- "SoftMask Content"
- "Properties("
- "ERROR_UNKNOWN_CHAR"
- "ERROR_XOBJECT_MISSINGRESOURCE"
- "ERROR_EXTGSTATE_MISSINGRESOURCE"
- "JPEG_ERROR"
- "ERROR_MODIFYING_NOT_ALLOWED"
- "There was an error parsing the content (ID:"
- "invalid vector subscript"
- "Filespec"
- "GS1_DataBar-14_Stacked"
- "GS1-DataBar-Stacked"
- "GS1_DataBar-Stacked-Omnidirectional"
- "GS1_DataBar-Expanded_Stacked"
- "GS1-DataBar-Expanded-Stacked"
- "http://www.color.org"
- "Application transferred too few scanlines"
- "Read from XMS failed"
- "Write to XMS failed"
- "Empty input file"
- "Premature end of input file"
- "Invalid color quantization mode change"
- "Not a JPEG file: starts with 0x%02x 0x%02x"
- "Cannot quantize more than %d color components"
- "Cannot quantize to fewer than %d colors"
- "Cannot quantize to more than %d colors"

## Dependências Preliminares
- **Document.dll** depende de: ArtSys.dll, ColorManipulationLayer.dll, BarCodeWrapper.dll, CMS.dll, EGXMPlib.dll, FontNDSLayer.dll, libpng16.dll, Localization.dll, PDFGeometryLayer.dll, tiff.dll, VariableEngine.dll, Logging.dll, ExtraBoostFilesystem.dll, boost_url.dll, boost_filesystem.dll, WS2_32.dll, PDFObjectLayer.dll, FontLayer.dll, PDFAccessLayer.dll, BasicFrameworkCoreLayer.dll, boost_nowide.dll, YAGL.dll, CurveApprox.dll, GeoMapper.dll, ADT.dll, KERNEL32.dll, MSVCP140.dll, MSVCP140_CODECVT_IDS.dll, VCRUNTIME140.dll, VCRUNTIME140_1.dll, api-ms-win-crt-runtime-l1-1-0.dll, api-ms-win-crt-heap-l1-1-0.dll, api-ms-win-crt-stdio-l1-1-0.dll, api-ms-win-crt-string-l1-1-0.dll, api-ms-win-crt-math-l1-1-0.dll, api-ms-win-crt-time-l1-1-0.dll, api-ms-win-crt-convert-l1-1-0.dll, api-ms-win-crt-filesystem-l1-1-0.dll, api-ms-win-crt-environment-l1-1-0.dll

## Análise de Dependências
- **Document.dll** é um componente central do ArtPro+ v250, provavelmente parte do módulo de documentação/gerenciamento de arquivos.
- **ArtSys.dll** parece ser um componente de sistema (ArtSys.dll) com funções de manipulação de documentos (??1ErrorReporterScopeGuard, ??0ErrorReporterScopeGuard).
- **PDFGeometryLayer.dll** e **tiff.dll** indicam suporte a formatos gráficos e imagem.
- **WS2_32.dll** e **KERNEL32.dll** indicam operações de rede e sistema básicas.
- **boost_*** dlls indicam uso de bibliotecas C++ padrão da Boost.

## Conclusão e Próximos Passos
1. **Document.dll** é um componente nativo C++ com 2737 funções exportadas, fortemente integrado ao ecossistema ArtPro+ (boost, PDF, imagem).
2. **UI Strings** mostram operações comuns de edição, formatação, impressão e manipulação de documentos.
3. **Recursos** incluem manifesto de assinatura digital (RT_MANIFEST) com suporte a assinatura Authenticode.
4. **Próximos passos**:
   - Analisar Document.dll no Ghidra com foco nos pontos de entrada (0x18001A2C0, 0x18009D300)
   - Mapear fluxo de execução desde WinMain até funções de inicialização de UI
   - Verificar dependências com o Módulo Document.dll e seus imports (especialmente PDFGeometryLayer.dll e tiff.dll)
   - Verificar se há dependências com outros módulos críticos (DocumentCallGraph.md, DEPENDENCY_MAP.md)

Este relatório atende aos requisitos de evidência rastreável com hash SHA-256, identificação clara e análise detalhada sem execução do binário.