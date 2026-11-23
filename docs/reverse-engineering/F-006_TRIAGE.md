# F-006 — Save Document — TRIAGE

**Identidade:**
- **Módulo Principal:** `Document.dll` (Responsável por `DocumentIO`, `WriteOptions`, `PieceInfoWriter`).
- **Módulos Relacionados:** `NDLModel.dll` (Contém lógica de fluxo de trabalho `SaveDocumentTask` e exceções `SaveDocumentException`).
- **Binário Alvo:** `C:\Esko\bg_prog_artpro+_v240\ArtPro+.app\Contents\Windows\Document.dll`
- **Versão Referenciada:** v240
- **SHA-256:** `DA91E28574C877D392D3E6BEF9CCBB7C4DCF3117EBD03655DE89834FC8FA9E21`
- **Compilador:** Microsoft Visual C/C++ (19.38.33134)
- **Arquitetura:** x64 (PE64)
- **Assinatura:** Windows Authenticode (2.0)

**Superfície Funcional:**
- O binário implementa um mecanismo robusto de I/O de documento, suportando **salvamento incremental/otimizado** (`NoOptimizedSave`, `IsIncrementalSave`).
- A serialização envolve gerenciamento de **Metadata/Pieces** (`PieceInfoWriter`), **Configurações de Saída** (`WriteOptions`: `Flavour`, `ImageCompression`), e **Contexto de Dados** (`Document.VariableContextMapping`).
- Funções de serialização expostas (via métodos de instância, não exports globais) incluem `?Save@Document@ArtDoc@@QEAAX...` e `?ExportDocument@NDLModel@@YA?AV?$Future...`.
- Indícios de formato proprietário: URLs `http://ns.esko-graphics.com/extfileslist/1.0/` e referências a `Document.ProcessingSteps.Plates`.

**Dependências:**
- Alta interdependência com módulos Esko/ArtPro+ (`ArtSys.dll`, `LayoutEngine.dll`, etc.).
- Dependências de terceiros comuns: `Qt6Core.dll`, `boost`, `icudtl.dat`, `libxml.dll`.

**Alvos Prioritários para Ghidra:**
- **Document.dll:** Foco na classe `ArtDoc` e no dispatcher `DocumentIO` (para mapear o fluxo de I/O).
- **NDLModel.dll:** Foco na implementação de `SaveDocumentTask` (para entender a orquestração do fluxo de trabalho de salvamento).
- **Endereços Chave (Sugestão):** Funções relacionadas a `?Save@Document@ArtDoc@@QEAAX...` (em `Document.dll`).

**Confiança:** **Média** (A existência do mecanismo de salvamento é provada por strings e estrutura de classes, mas a confirmação do formato `.artplus` requer análise de conteúdo, não apenas I/O).

**Status F-006:** Implementado (em termos de mecanismo), mas **PENDENTE** de evidência comportamental CAP-YYYYMMDD-nn (salvando o arquivo no ArtPro+ real).

**Próxima Ação:** Aguardar captura comportamental (`artpro-behavior-capture`). Não prosseguir com Ghidra/Manifest.