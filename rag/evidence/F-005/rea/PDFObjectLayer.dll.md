# PDFObjectLayer.dll - Triagem Estática (REA)

## Identidade
- **Compilador**: Microsoft Visual C/C++ 19.41.34435 (Visual Studio 2022)
- **Linker**: Microsoft Linker 14.41.34435
- **Arquitetura**: PE64
- **Assinatura**: Windows Authenticode (PKCS #7)
- **Dados de Depuração**: POGO (Profile Guided Optimization)
- **Dependências**: Microsoft C/C++ Runtime [dynamic]

## Metadados PE
- **Hash SHA-256**: ba6f1eeecdf5b9bb5aa587b35821ed6b3118d133075fe425ac5a7a5988aa4a7d
- **Tamanho**: 2,335,784 bytes (menor que Document.dll e PDFAccessLayer.dll, possivelmente camada mais específica)

## Superfície Funcional
Strings Unicode notáveis (extraídas via `strings64 -n 8`):
- Múltiplas strings com prefixo `PDFObject` (classe/prop)
- Terminologia de **PDF Object Actions** e **View Layer**
- Referências a camadas de visualização e ações de objeto PDF (seleção, edição, transformação)
- Termos como `Preflight`, `Trapping`, `BarCode`, `Screen`, `Separation`, `Marks`
- Ações do sistema: `ACTION/*`, `WARNING/*`, `MESSAGECENTER/*`

Este módulo parece ser a camada de manipulação de objetos dentro de PDFs, complementando `PDFAccessLayer.dll`. Enquanto `PDFAccessLayer` gerencia estruturas como caixas de página, `PDFObjectLayer` lida com as ações sobre os objetos visuais dentro do PDF. O nome `PDFObjectViewLayer` também aparece como DLL auxiliar.

## Importações / Exportações
- **Imports**: Parte do ecossistema Esko (Document.dll, DocumentMarks.dll, PDFAccessLayer.dll, etc.) e Qt6, APIs do Windows.
- **Exports**: Necessa análise com Ghidra/REA para mapear nomes de funções.

## Alvos Prioritários para Ghidra
- Funções relacionadas a `PDFObject` e `PDFObjectViewLayer`
- Manipulação de objetos visuais (caminhos, formas, imagens) dentro de PDFs
- Integração com `Selection`, `Transform`, `Marks` modules
- Endereços após importação completa.

## Confiança
Média-Alta — strings confirmam foco em objetos PDF, mas a API externa interna precisa de Ghidra.

## Evidência Bruta
- JSON DIE: `rag/sources/PDFObjectLayer.dll.json`
- Strings (amostra): `rag/sources/PDFObjectLayer.dll.strings.txt`

## Próxima Ação
Importar no Ghidra 12.2 (headless) para analisar a API de manipulação de objetos PDF e correlacionar com `Document.dll` e `PDFAccessLayer.dll`. Marcar como `analisado` no INVENTORY.