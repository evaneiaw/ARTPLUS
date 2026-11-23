# PDFAccessLayer.dll - Triagem Estática (REA)

## Identidade
- **Compilador**: Microsoft Visual C/C++ 19.41.34435 (Visual Studio 2022)
- **Linker**: Microsoft Linker 14.41.34435
- **Arquitetura**: PE64
- **Assinatura**: Windows Authenticode (PKCS #7)
- **Dados de Depuração**: POGO (Profile Guided Optimization)
- **Dependências**: Microsoft C/C++ Runtime [dynamic]

## Metadados PE
- **Hash SHA-256**: a98eb2c9eac50307485de46c88be64dda514710d4b46141009e7235253fc5149
- **Tamanho**: 3,660,840 bytes

## Superfície Funcional
Strings Unicode notáveis (extraídas via `strings64 -n 8`):
- Múltiplas strings relacionadas a **PDF** (Box types: `MediaBox`, `CropBox`, `BleedBox`, `TrimBox`, `ArtBox`)
- Termos como `Preflight`, `Trapping`, `BarCode`, `Screen`, `Separation`, `Marks`
- Ações do sistema: `ACTION/C`, `ACTION/WARNING`, `MESSAGECENTER`
- Referências a Esko PDF workflows e características de prepress

Este módulo parece ser a camada de acesso à estrutura PDF, gerenciando caixas de página (Page boxes) e integrando com recursos de preflight e trapping do ArtPro+.

## Importações / Exportações
- **Imports**: Parte do ecossistema Esko (Document.dll, DocumentMarks.dll, PDFObjectLayer.dll, etc.) e Qt6, APIs do Windows.
- **Exports**: Necessa análise com Ghidra/REA para mapear nomes de funções.

## Alvos Prioritários para Ghidra
- Funções que lidam com leitura/escrita de PDF Page boxes (`PageMediaBox`, `PageCropBox`, etc.)
- Integração com `Preflight`, `Trapping`, `Screen` modules
- Funções de acesso às estruturas `Content` do documento PDF
- Endereços após importação completa.

## Confiança
Média-Alta — strings de UI documentam funcionalidades PDF específicas, mas precisarão de Ghidra para mapear a API externa e interna.

## Evidência Bruta
- JSON DIE: `rag/sources/PDFAccessLayer.dll.json`
- Strings (amostra): `rag/sources/PDFAccessLayer.dll.strings.txt`

## Próxima Ação
Importar no Ghidra 12.2 (headless) para analisar a API de acesso ao PDF e correlacionar com `Document.dll`. Marcar como `analisado` no INVENTORY.