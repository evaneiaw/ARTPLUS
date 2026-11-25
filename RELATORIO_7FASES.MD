# RELATÓRIO MESTRE: CONSOLIDAÇÃO ARTPLUS EM 7 FASES

## VISÃO GERAL
Este documento estabelece o plano integral para a unificação dos projetos **ARTPLUS** (Núcleo Lógico) e **ARTPLUS-UI** (Interface e Componentes Visuais) em uma única árvore canônica residente em `H:\Desktop\ArtPlus`. O objetivo é estabilizar o ambiente de desenvolvimento, eliminar a duplicidade do motor lógico e integrar a interface rica do ArtPro+ v24.03.10017 com o motor funcional já auditado.

### Cronograma Lógico de Execução
1.  **Fase 1: Inventário e Diagnóstico** (Concluída em 24/11/2026)
2.  **Fase 2: Unificação Física e Estrutural** (Pendente)
3.  **Fase 3: Integração Lógica e Funcional** (Pendente)
4.  **Fase 4: Limpeza e Organização** (Pendente)
5.  **Fase 5: Auditoria da Engenharia Reversa** (Pendente)
6.  **Fase 6: Unificação dos Agentes e Modos** (Pendente)
7.  **Fase 7: Validação Final e Publicação** (Pendente)

---

## FASE 1 — INVENTÁRIO E DIAGNÓSTICO (CONCLUÍDA)

### 1.1 Objetivo
Realizar o levantamento completo das duas árvores de trabalho, identificar redundâncias, divergências de código e lacunas de evidência para fundamentar a estratégia de unificação.

### 1.2 Situação Inicial
O projeto operava em dois repositórios divergentes: um focado no motor lógico (`ArtPlus`) e outro no desenvolvimento da interface (`ArtPlus-UI`). O motor do núcleo era mais recente e auditado, enquanto a UI possuía componentes visuais avançados, mas baseados em uma versão anterior do motor.

### 1.3 Inventário Resumido
*   **ARTPLUS (Núcleo):** 7 commits (`70c3d00`), 84 arquivos em `src/`, 11 testes CTest, 5 features auditadas/testadas.
*   **ARTPLUS-UI (Interface):** 5 commits (`049ec52`), 77 arquivos em `src/` (54 duplicatas do motor), 14 testes CTest, 118 arquivos de workshop visual.
*   **Divergência Real:** 17 arquivos em `src/` apresentaram diferenças lógicas após normalização de CRLF.

### 1.4 Estado das Funcionalidades (Núcleo)
*   **F-001/002/003/005/008:** Testados/Implementados com laudos de auditoria.
*   **F-004:** Fora do escopo (CAP negativo na v24).
*   **F-006:** Implementado (Save Document com rollback).
*   **F-007:** Bloqueado (BLO-008).

### 1.5 Riscos Identificados
*   **R1:** Perda de melhorias do motor auditado durante o merge com a UI.
*   **R3:** Monolito `main_window.cpp` (146 KB) dificulta a manutenção.
*   **R9:** Invalidação de auditorias prévias devido a alterações no código-fonte.

### 1.6 Veredito do Gate F1
**ATENDIDO.** O inventário forneceu a base necessária para a unificação, com doadores declarados por arquivo divergente.

---

## FASE 2 — UNIFICAÇÃO FÍSICA E ESTRUTURAL

### 2.1 Objetivo
Estabelecer a estrutura física unificada no diretório `H:\Desktop\ArtPlus`, integrando os recursos visuais e componentes da UI sem sobrescrever o progresso lógico do núcleo.

### 2.2 Subfases e Tarefas
1.  **Segurança e Backup:**
    *   Criação de tags Git anotadas `pre-consolidation` em ambos os repositórios.
    *   Geração de Git bundles em `H:\Desktop\_backup_artplus\`.
2.  **Importação de Componentes:**
    *   Mover os 19 arquivos exclusivos de UI (`src/ui/artpro/*`, `dialogs/*`, `panels/*`, `styles/*`) para a árvore do núcleo.
    *   Importar `resources/ui.qrc` e o diretório `docs/ui-workshop/`.
3.  **Ajuste de Infraestrutura:**
    *   Atualizar `CMakeLists.txt` para incluir `Qt6::PrintSupport`.
    *   Registrar os 5 novos alvos de teste vindos da UI.
    *   Criar `IMPORT_MANIFEST.md` registrando a origem de cada arquivo importado.

### 2.3 Proibições
*   Não importar `selection_mark.*` (F-004).
*   Não importar `color_manipulation/*` (concorrente do F-008).
*   Não sobrescrever `src/pdf/` ou `src/prepress/` sem merge manual (Fase 3).

### 2.4 Critérios de Aceite (Gate F2)
*   [ ] Build bem-sucedido do alvo `ArtPlus`.
*   [ ] 16 testes CTest registrados e passando.
*   [ ] `IMPORT_MANIFEST.md` completo.

---

## FASE 3 — INTEGRAÇÃO LÓGICA E FUNCIONAL

### 3.1 Objetivo
Fundir os fluxos de execução do motor lógico com o chrome da interface, garantindo que as ferramentas (F-001..F-003) e os sistemas de arquivo (F-005, F-006) funcionem através da nova UI.

### 3.2 Tarefas Detalhadas
1.  **Merge do MainWindow:** Utilizar o chrome da UI como base e transplantar as chamadas de API do núcleo (`openDocumentPath`, `DocumentSaveManager`, `MarkSetProcessor`).
2.  **Expansão da API:** Adicionar `Document::setPageOrder()` e integrar os comandos de Undo (`CreateObjectsCommand`, `PageOrderCommand`).
3.  **Correção de Regressão:** Aplicar a precisão de 4 casas decimais no `MediaBox` do `PdfExporter` (vinda da UI).
4.  **Auditoria de UI:** Mapear todos os 60 botões desabilitados; adicionar `TODO(F-###)` ou tooltip informativa.

### 3.3 Testes Necessários
*   Teste de round-trip de PDF verificando a preservação do MediaBox fracionário.
*   Teste de integração: abrir PDF → modificar via painel Marks → salvar → verificar integridade.

### 3.4 Critérios de Aceite (Gate F3)
*   [ ] Interface funcional com todos os menus e painéis populados.
*   [ ] Undo/Redo operantes para novas operações de página/objeto.

---

## FASE 4 — LIMPEZA E ORGANIZAÇÃO

### 4.1 Objetivo
Eliminar resíduos do processo de merge e padronizar a estrutura do projeto para manutenção a longo prazo.

### 4.2 Escopo
*   Remover arquivos `.bak`, `.new`, e scripts de log ad-hoc da raiz.
*   Normalizar a codificação de arquivos (UTF-8 sem BOM) e o estilo de indentação.
*   Reorganizar a pasta `scripts/` para evitar duplicidade com a raiz.

### 4.3 Critérios de Aceite (Gate F4)
*   [ ] `git status` limpo de arquivos não rastreados desnecessários.
*   [ ] Zero referências a caminhos absolutos da antiga árvore `ArtPlus-UI`.

---

## FASE 5 — AUDITORIA DA ENGENHARIA REVERSA

### 5.1 Objetivo
Vincular os novos componentes de interface às evidências reais do ArtPro+ v24 e revalidar o projeto contra a Regra de Ouro (v24.03.10017).

### 5.2 Tarefas
1.  **Rastreabilidade:** Criar `docs/reverse-engineering/UI_TRACEABILITY.md` vinculando os CAPs da interface (01..14) aos arquivos em `src/ui/`.
2.  **Correção de Evidência:** Recuperar os 2 CAPs quebrados e o GHIDRA orfão identificado na Fase 1.
3.  **Reauditoria:** Executar o ciclo de auditoria para F-001, 002, 003, 005, 006 e 008, emitindo novos laudos devido às alterações no `src/`.

### 5.3 Critérios de Aceite (Gate F5)
*   [ ] Toda funcionalidade visível possui um CAP correspondente registrado no `manifest.json` da feature.

---

## FASE 6 — UNIFICAÇÃO DOS AGENTES E MODOS

### 6.1 Objetivo
Migrar o projeto para o modelo de operação **BUILD** centralizado, com automação total de gates e delegação para subagentes especialistas.

### 6.2 Tarefas
1.  **Consolidação de Agentes:** Definir o agente `build` como `primary` no `opencode.jsonc`.
2.  **Atualização de Skills:** Fundir as 7 skills do UI com as 26 do núcleo; eliminar redundâncias e padronizar o namespace.
3.  **Correção de Schema:** Atualizar todas as definições de agentes para o formato V2 (uso de `steps` e permissões por allowlist).

### 6.3 Critérios de Aceite (Gate F6)
*   [ ] `validate_skills.py` retorna zero erros.
*   [ ] Pipeline de subagentes operacional (rea -> doc -> impl -> testes -> auditor).

---

## FASE 7 — VALIDAÇÃO FINAL E PUBLICAÇÃO

### 7.1 Objetivo
Realizar o teste de aceitação final do sistema unificado e publicar a versão canônica no repositório remoto.

### 7.2 Tarefas
1.  **Build de Release:** Executar um build limpo (`build_phase7`) em configuração Release.
2.  **Validação Visual:** Gravar sessão de uso demonstrando os 10 fluxos principais (Abertura -> Edição -> Marks -> Save).
3.  **Sincronização:** Fazer o push final para `github.com/evaneiaw/artplus`.
4.  **Arquivamento:** Marcar o repositório `ArtPlus-UI` como arquivado (read-only).

### 7.3 Critérios de Aceite (Gate F7)
*   [ ] Build 0 falhas; CTest 0 falhas.
*   [ ] HEAD local em sincronia com `origin/master`.

---

## MATRIZ DE RISCOS E DECISÕES

| Risco | Impacto | Mitigação |
|---|---|---|
| Perda de Lógica | Crítico | Doador declarado: motor lógico sempre vence em conflitos, exceto MediaBox/Undo. |
| Build Quebrado | Alto | Checkpoint após cada `git mv`/merge; build incremental obrigatório. |
| Falta de Evidência | Médio | Marcar comportamentos não provados como `Hipótese` na matriz de rastreabilidade. |

### Decisões Aprovadas
1.  Motor Canônico: **ARTPLUS**.
2.  Base de UI: **ARTPLUS-UI**.
3.  Branch Única: `master`.
4.  Modo Operacional: **BUILD**.

---
*Documento gerado pelo Agente BUILD em 24/11/2026.*
*Caminho: H:\Desktop\ArtPlus\RELATORIO_7FASES.MD*
