# F-004 — Selection Mark — TRIAGE

**Identidade:**
- **Binário:** `PDFObjectActions.dll`
- **Versão Referenciada:** v250
- **SHA-256:** `73ab2d7b7df5ea73272eb5bdafb3408a90f6d471680300d3debf0b2294273bf4`
- **Compilador:** Microsoft Visual C/C++ (19.41.34435)
- **Arquitetura:** x64 (PE64)
- **Assinatura:** Windows Authenticode (2.0)
- **Dependências Chave:** Qt6Core.dll, Document.dll, ArtSys.dll, LayoutEngine.dll, CurveApprox.dll, etc. (Muitas dependências Esko/ArtPro+)

**Superfície Funcional:**
- O binário lida com operações essenciais de manipulação de PDF, como manipulação de **Bounding Boxes (CropBox, TrimBox, ArtBox, BleedBox)**, **Trapping**, **Color Management (CMYK, Spot)**, **Separation** e **Marks** (incluindo `BARCODE` e `RegistrationMarks`).
- Strings de UI/Mensagens indicam: `Heidelberg Trapping for some pages`, `Errors & Warnings`, `Critical PDF failure on page %1`, `Selection Mark` (`F-004`).
- Funções relacionadas a seleção e manipulação de objetos são expostas, confirmando o suporte a **Selection Mark** (operação no contexto de seleção, sem diálogo modal - `F-004`).
- Métodos para manipular `PageBoxes`, `PageLabels`, `OutputIntents` e `ColorSpaces` estão presentes.

**Dependências:**
- Alta interdependência com módulos Esko/ArtPro+ (`Document.dll`, `ArtSys.dll`, `LayoutEngine.dll`).
- Dependências de terceiros comuns em apps Qt/Windows: `Qt6Core.dll`, `KERNEL32.dll`, `MSVCP140.dll`, `zlib.dll`.

**Alvos Prioritários para Ghidra:**
- A análise completa de funções/Xrefs (`GHIDRA-PDFObjectActions-PENDING`) é necessária para mapear a lógica exata da **Selection Mark** (e.g., `GOVChangeSelectOverlappingObjects`, `GOVSelectOverlappingObjects`, `GOVChangeSelectionToForm`).
- **Endereços Chave (Sugestão):** Funções relacionadas a `GOVChangeSelectOverlappingObjects` e `GOVSelectOverlappingObjects` (visíveis em strings/contexto).

**Confiança:** **Média-Alta** (Funcionalidade F-004 confirmada por strings e contexto de engenharia reversa existente, mas **ausência de evidência comportamental CAP-*** impede confiança total, conforme auditoria).

**Status F-004:** Implementado e Testado (13/13), mas **BLOQUEADO** pela indisponibilidade do ArtPro+ real para **captura comportamental (CAP-YYYYMMDD-nn)**.

**Próxima Ação:**
1. Prosseguir com a análise estática detalhada via Ghidra (usando `ghidra-analysis` skill).
2. Aguardar ambiente para captura comportamental (`artpro-behavior-capture`).