# ADR-005 — Open Document (PDF)

> **Registro histórico.** Esta página registra a **proposta original** de abertura, baseada
> em reutilizar `PDFAccessLayer.dll`/`PDFObjectLayer.dll`. Ela **não** descreve o código do
> ArtPlus e **não** foi implementada. A decisão vigente é `ADR-013`, que corresponde ao que
> existe em `src/pdf/`, `src/ui/main_window.cpp` e `src/document/document_serializer.*`.
> O conteúdo decisório abaixo é preservado para rastreabilidade.

## Contexto

Spec F-005; funcionalidade File > Open Document, que utiliza `PDFAccessLayer.dll` e
`PDFObjectLayer.dll` para instanciar o modelo `ArtDoc` (Document.dll).

A evidência da versão de referência v24.03.10017 (`GHIDRA-Document-0x1802160B0`,
`GHIDRA-Document-0x1800A2E40`, `GHIDRA-Document-0x18008F590`, `GHIDRA-Document-0x180093D60`)
descreve a entrada de abertura em `Document.dll`; o parse do PDF é delegado a
`PDFOBJECTLAYER.DLL::GODocument` (import externo, fora do módulo analisado). Esta proposta
não produziu evidência estática própria de `PDFAccessLayer.dll` nem de `PDFObjectLayer.dll`.

## Decisão

A responsabilidade de abrir e parsear documentos PDF reside no módulo `DocumentCore`,
centralizado na classe `ArtDoc`. As camadas de acesso externo (`PDFAccessLayer`,
`PDFObjectLayer`) são tratadas como dependências de infraestrutura de I/O, e não como parte
do modelo de domínio.

## Mapeamento binário → ArtPlus

Endereços **não coletados**: esta proposta não gerou evidência estática própria, e os
marcadores abaixo são apenas descritivos — não são IDs `GHIDRA-*` de nenhum módulo.

| Função (Ghidra/Inferido) | Classe/método ArtPlus | Observação |
|---|---|---|
| (não coletado — leitura de caixas) | `ArtDoc::load(const std::string& path)` | Utiliza `PDFAccessLayer` para extrair caixas de página (mm). |
| (não coletado — iteração de objetos) | `ArtDoc::parsePage(Page& p)` | Itera objetos via `PDFObjectLayer` para construir `ContentObject`s. |
| (não coletado — parse de conteúdo) | `ContentObject::parse(PDFStreamData)` | Mapeia comandos PDF (`/Path`, `/Text`) para `Path`, `Text`, `Group`. |
| (não coletado — atualização de estado) | `ArtDoc::applyChanges(const ChangeCollector&)` | Registra `WhatChangedFlags` usando lógica de `Document.dll`. |

## Contrato de interface

```cpp
// DocumentCore/ArtDoc.h
class ArtDoc {
public:
    // Estrutura de Parâmetros de Abertura
    struct OpenParams { std::string filePath; };

    // Ponto de entrada principal
    bool load(const OpenParams& params);

    // Acesso aos componentes de domínio
    const LayerProperties& getLayerProperties() const;
    const std::vector<ContentObject>& getContentObjects() const;
    // ... métodos para acessar Group, Text, Path, etc.

private:
    // Métodos de parsing (internos, dependentes de PDFAccessLayer/PDFObjectLayer)
    void parsePage(Page& p) const;
};

// DocumentCore/ContentObject.h
class ContentObject {
public:
    enum ObjectType { TEXT, PATH, GROUP, IMAGE };
    ObjectType getType() const;
    // Métodos específicos de transformação/propriedades
    void setTransform(const QTransform& t);
};
```

## Dependências

- **Requer:** `PDFAccessLayer` (para caixas de página, metadados PDF).
- **Requer:** `PDFObjectLayer` (para iteração de objetos no stream de conteúdo).
- **Não Requer:** `DocumentMarks` (esta funcionalidade é posterior à abertura).

## Estrutura de módulos C++/Qt 6.8.3

- **Módulo:** `DocumentCore` (Responsável pelo modelo `ArtDoc`, `ContentObject`, `LayerProperties`, etc.).
- **Dependências:** `PDFAccessLayer` (Infra I/O), `PDFObjectLayer` (Infra I/O).
- **Fluxo de Dados:** UI (via `File > Open`) $\rightarrow$ `ArtDoc::load` $\rightarrow$ `PDFAccessLayer` $\rightarrow$ Stream PDF $\rightarrow$ `PDFObjectLayer` $\rightarrow$ Objeto/Estrutura Interna (`Path`, `Text`, `Group`) $\rightarrow$ `ArtDoc` (Estado).
- **Pontos de Extensão:** Implementação de *parsers* de comandos PDF (`/Path`, `/Text`) deve ser extensível para novos formatos PDF, respeitando a unidade `mm` conforme exigido por `PDFAccessLayer`.
- **O que NÃO entra:** Lógica de *rendering* visual (pertence ao módulo de Visualização, não DocumentCore).

## Correção documental

Em 2026-11-21, em resposta ao laudo `docs/audit/F-005-audit-20261121b.md` (ressalva e):

1. removido o campo `version = 25.0` do contrato de `OpenParams` — resíduo da versão
   histórica, fora do fluxo ativo, apresentado indevidamente junto à referência
   v24.03.10017;
2. substituídos os marcadores de endereço `[ADDR_…]` por "não coletado", porque não
   existem endereços desta proposta e nenhum deles corresponde a um ID `GHIDRA-*` da
   versão de referência;
3. registrada a superação por `ADR-013`.

Nenhuma decisão de projeto foi alterada por esta correção.

## Estado

proposto — **não implementado**. A abertura efetiva do ArtPlus está registrada em
`ADR-013`; esta página permanece apenas como histórico da proposta inicial.
