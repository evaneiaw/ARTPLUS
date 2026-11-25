# ARТPLUS — ROADMAP MESTRE DE DESENVOLVIMENTO

**Projeto:** ArtPlus  
**Referência funcional:** Esko ArtPro+ v24.03.10017  
**Repositório:** <https://github.com/evaneiaw/artplus><br>
**Branch:** master  
**Objetivo:** Desenvolver um aplicativo profissional de pré-impressão e edição gráfica, reconstruindo comportamentos comprovados do ArtPro+ por engenharia reversa, observação funcional e implementação independente.

---

# 1. MISSÃO DO PROJETO

Transformar o ArtPlus em um aplicativo gráfico profissional, funcional e estável, contemplando edição vetorial, manipulação de PDF, pré-impressão, gerenciamento de cores, produção gráfica, embalagens e automação.

O objetivo não é produzir uma interface que apenas se pareça com o ArtPro+. Os comandos, menus, ferramentas, painéis e operações precisam executar suas funções reais.

Toda implementação deve ser baseada em:
- Evidências obtidas pela análise Ghidra.
- Documentação e conhecimento armazenados no RAG.
- Comportamentos observados diretamente no ArtPro+.
- Testes reproduzíveis.
- Arquitetura e código existentes no ArtPlus.

Não inventar comportamentos nem declarar equivalência sem comprovação.

# 2. REGRAS OBRIGATÓRIAS

1. Preservar a arquitetura existente e funcionalidades já validadas.
2. Investigar antes de implementar.
3. Não substituir componentes funcionais sem justificativa técnica.
4. Não criar botões decorativos, placeholders ou funcionalidades simuladas.
5. Todo comando visível deve executar uma operação real ou estar claramente indisponível por limitação técnica documentada.
6. Compilar Release após cada alteração de código.
7. Executar testes específicos e todos os CTests após cada ciclo de implementação.
8. Validar inicialização real do executável.
9. Validar visualmente as funcionalidades alteradas.
10. Comparar resultados com o ArtPro+ quando houver referência disponível.
11. Atualizar testes, documentação e RAG.
12. Registrar todos os arquivos criados, modificados e removidos.
13. Fazer commits e push para origin/master após cada conjunto coerente de alterações validadas.
14. Nunca declarar conclusão sem evidências.
15. Não apagar, sobrescrever ou descartar trabalho existente sem necessidade comprovada.

# 3. ROADMAP DE IMPLEMENTAÇÃO

## MÓDULO 01 — NÚCLEO E ARQUITETURA
- 01.01 Auditar arquitetura atual.
- 01.02 Auditar modelo de documentos e objetos.
- 01.03 Verificar gerenciamento de memória e propriedade dos objetos.
- 01.04 Consolidar sistema de coordenadas e transformações.
- 01.05 Verificar comunicação entre editor, ferramentas e painéis.
- 01.06 Verificar gerenciamento de eventos.
- 01.07 Verificar sistema de comandos e histórico.
- 01.08 Eliminar duplicações e inconsistências arquiteturais.
- 01.09 Criar testes de integração do núcleo.

## MÓDULO 02 — INTERFACE E WORKSPACE
- 02.01 Auditar todos os menus.
- 02.02 Auditar todos os itens de menu e submenus.
- 02.03 Auditar todas as barras de ferramentas.
- 02.04 Auditar todos os painéis.
- 02.05 Corrigir abertura, fechamento, encaixe e redimensionamento de painéis.
- 02.06 Implementar gerenciamento de documentos e abas.
- 02.07 Implementar preferências e configurações persistentes.
- 02.08 Implementar atalhos e personalização.
- 02.09 Corrigir estados visuais e atualização dos comandos.
- 02.10 Validar cada ação da interface.

## MÓDULO 03 — SELEÇÃO E EDIÇÃO VETORIAL
- 03.01 Seleção individual.
- 03.02 Seleção múltipla.
- 03.03 Seleção por área.
- 03.04 Adição e remoção de objetos da seleção.
- 03.05 Seleção por camadas e hierarquia.
- 03.06 Ferramenta de nós.
- 03.07 Criação e remoção de nós.
- 03.08 Edição de curvas Bézier.
- 03.09 Pen Tool.
- 03.10 Ferramentas de desenho vetorial.
- 03.11 Fechamento e união de caminhos.
- 03.12 Operações booleanas.
- 03.13 Offset e contornos.
- 03.14 Precisão geométrica e snapping.
- 03.15 Testar seleção e edição em documentos complexos.

## MÓDULO 04 — TEXTO E TIPOGRAFIA
- 04.01 Criar e editar textos.
- 04.02 Editar atributos tipográficos.
- 04.03 Gerenciar fontes.
- 04.04 Detectar fontes ausentes.
- 04.05 Preservar fontes incorporadas em PDF.
- 04.06 Implementar alinhamento e espaçamento.
- 04.07 Implementar conversão de texto em curvas quando suportada.
- 04.08 Validar caracteres especiais e Unicode.
- 04.09 Testar importação e exportação de textos.

## MÓDULO 05 — IMAGENS E RECURSOS
- 05.01 Importar imagens.
- 05.02 Substituir e atualizar imagens vinculadas.
- 05.03 Gerenciar recursos incorporados e externos.
- 05.04 Preservar resolução e perfil de cor.
- 05.05 Implementar recorte e posicionamento.
- 05.06 Detectar imagens ausentes.
- 05.07 Detectar baixa resolução.
- 05.08 Validar transparências e máscaras.
- 05.09 Testar exportação e reabertura.

## MÓDULO 06 — GRUPOS, MÁSCARAS E TRANSPARÊNCIAS
- 06.01 Agrupar e desagrupar.
- 06.02 Implementar hierarquia de grupos.
- 06.03 Clipping paths.
- 06.04 Máscaras de opacidade.
- 06.05 Transparências.
- 06.06 Modos de mesclagem.
- 06.07 Grupos de transparência.
- 06.08 Preservar estruturas durante importação e exportação PDF.
- 06.09 Validar renderização e equivalência visual.

## MÓDULO 07 — TRANSFORMAÇÕES E GEOMETRIA
- 07.01 Mover.
- 07.02 Escalar.
- 07.03 Rotacionar.
- 07.04 Espelhar.
- 07.05 Inclinar.
- 07.06 Transformação numérica.
- 07.07 Transformação em relação a pontos de referência.
- 07.08 Alinhar e distribuir.
- 07.09 Duplicar e repetir transformações.
- 07.10 Desfazer e refazer transformações.
- 07.11 Validar precisão e estabilidade numérica.

## MÓDULO 08 — CAMADAS E PROPRIEDADES
- 08.01 Criar, remover e renomear camadas.
- 08.02 Reordenar camadas.
- 08.03 Bloquear e desbloquear.
- 08.04 Ocultar e exibir.
- 08.05 Gerenciar subcamadas.
- 08.06 Gerenciar objetos.
- 08.07 Implementar painel de propriedades.
- 08.08 Atualização bidirecional entre seleção e propriedades.
- 08.09 Validar persistência do documento.

## MÓDULO 09 — PDF E COMPATIBILIDADE
- 09.01 Auditar importador e exportador.
- 09.02 Preservar estruturas PDF.
- 09.03 Form XObjects.
- 09.04 Image XObjects.
- 09.05 Text Objects e fontes.
- 09.06 Clipping e transparências.
- 09.07 Soft Masks.
- 09.08 Anotações.
- 09.09 Preservar metadados.
- 09.10 Implementar validação de PDF/X.
- 09.11 Testar arquivos reais e casos extremos.
- 09.12 Comparar renderização antes e depois da exportação.

## MÓDULO 10 — GERENCIAMENTO DE CORES
- 10.01 RGB, CMYK e Gray.
- 10.02 Cores especiais.
- 10.03 DeviceN.
- 10.04 ICC Profiles.
- 10.05 Conversões de cor.
- 10.06 Color Management.
- 10.07 Preservação de perfis.
- 10.08 Simulação de saída.
- 10.09 Comparação de cores e tolerâncias.

## MÓDULO 11 — SEPARAÇÕES E IMPRESSÃO
- 11.01 Painel de separações.
- 11.02 Visualização de chapas.
- 11.03 Ativar e desativar separações.
- 11.04 Overprint.
- 11.05 Overprint Preview.
- 11.06 Knockout.
- 11.07 Trapping.
- 11.08 Validar resultados de separação.
- 11.09 Exportar resultados preservando informações de impressão.

## MÓDULO 12 — PREFLIGHT E QUALIDADE
- 12.01 Estrutura de regras de preflight.
- 12.02 Fontes ausentes.
- 12.03 Imagens ausentes.
- 12.04 Baixa resolução.
- 12.05 Cores não permitidas.
- 12.06 Objetos fora da página.
- 12.07 Transparências problemáticas.
- 12.08 Problemas de sangria.
- 12.09 Relatórios de erros.
- 12.10 Correções automáticas seguras.
- 12.11 Perfis configuráveis de preflight.

## MÓDULO 13 — SANGRIA E PREPARAÇÃO DE IMPRESSÃO
- 13.01 Configuração de sangria.
- 13.02 Marcas de corte.
- 13.03 Marcas de registro.
- 13.04 Barras de controle.
- 13.05 Informações de produção.
- 13.06 Área de impressão.
- 13.07 Exportação de arquivos preparados.
- 13.08 Validação dimensional.

## MÓDULO 14 — STEP AND REPEAT
- 14.01 Repetição horizontal e vertical.
- 14.02 Quantidade de cópias.
- 14.03 Espaçamento.
- 14.04 Deslocamento.
- 14.05 Repetição por grade.
- 14.06 Repetição escalonada.
- 14.07 Atualização de instâncias.
- 14.08 Integração com histórico e exportação.

## MÓDULO 15 — IMPOSIÇÃO E MONTAGEM
- 15.01 Montagem de múltiplos trabalhos.
- 15.02 Distribuição em folhas.
- 15.03 Imposição.
- 15.04 Rotação automática.
- 15.05 Aproveitamento de material.
- 15.06 Marcas de produção.
- 15.07 Visualização de montagem.
- 15.08 Exportação e validação.

## MÓDULO 16 — EMBALAGENS E FACAS
- 16.01 Identificação de linhas de corte.
- 16.02 Identificação de linhas de vinco.
- 16.03 Separação entre arte e faca.
- 16.04 Gerenciamento de cores técnicas.
- 16.05 Visualização de faca.
- 16.06 Transformações de estruturas.
- 16.07 Preparação de embalagem.
- 16.08 Validação dimensional e geométrica.

## MÓDULO 17 — AUTOMAÇÃO E PROCESSAMENTO EM LOTE
- 17.01 Sistema de Action Lists.
- 17.02 Gravação de operações.
- 17.03 Reprodução de operações.
- 17.04 Processamento em lote.
- 17.05 Filas de processamento.
- 17.06 Relatórios de execução.
- 17.07 Tratamento de erros.
- 17.08 Preservação dos arquivos originais.

## MÓDULO 18 — SCRIPTS E EXTENSIBILIDADE
- 18.01 Auditar possibilidades de extensão.
- 18.02 Definir API pública interna.
- 18.03 Criar sistema de scripts.
- 18.04 Gerenciar extensões.
- 18.05 Presets de operações.
- 18.06 Documentar interfaces.
- 18.07 Testar segurança e estabilidade.

## MÓDULO 19 — DESEMPENHO
- 19.01 Medir desempenho do editor.
- 19.02 Otimizar renderização.
- 19.03 Otimizar seleção e geometria.
- 19.04 Gerenciar cache.
- 19.05 Otimizar consumo de memória.
- 19.06 Testar documentos grandes.
- 19.07 Testar operações em lote.
- 19.08 Eliminar travamentos e vazamentos.

## MÓDULO 20 — ESTABILIDADE E RECUPERAÇÃO
- 20.01 Salvamento automático.
- 20.02 Recuperação após falhas.
- 20.03 Proteção contra corrupção.
- 20.04 Tratamento de erros.
- 20.05 Undo/Redo completo.
- 20.06 Testes de estresse.
- 20.07 Testes de abertura e fechamento.
- 20.08 Testes de documentos danificados.

## MÓDULO 21 — AUDITORIA FINAL DA INTERFACE
- 21.01 Inventariar todos os menus.
- 21.02 Inventariar todos os comandos.
- 21.03 Inventariar todas as ferramentas.
- 21.04 Inventariar todos os botões.
- 21.05 Inventariar todos os atalhos.
- 21.06 Mapear cada elemento à sua implementação.
- 21.07 Eliminar ações sem implementação.
- 21.08 Corrigir comandos que não atualizam o estado.
- 21.09 Validar todos os fluxos de interação.
- 21.10 Criar matriz de rastreabilidade entre interface, código e testes.

## MÓDULO 22 — COMPATIBILIDADE E VALIDAÇÃO FINAL
- 22.01 Criar conjunto de documentos de referência.
- 22.02 Comparar importação com ArtPro+.
- 22.03 Comparar operações de edição.
- 22.04 Comparar renderização.
- 22.05 Comparar exportação.
- 22.06 Testar documentos simples e complexos.
- 22.07 Testar regressões.
- 22.08 Validar instalação e inicialização.
- 22.09 Validar menus e ferramentas.
- 22.10 Produzir relatório de compatibilidade.
- 22.11 Registrar limitações comprovadas.
- 22.12 Consolidar versão Release.

# 4. CRITÉRIO DE CONCLUSÃO DE CADA TAREFA

Cada tarefa deve possuir:
- Evidência ou especificação de comportamento esperado.
- Implementação integrada ao aplicativo.
- Teste automatizado quando tecnicamente aplicável.
- Compilação Release bem-sucedida.
- Testes de regressão.
- Validação visual quando houver interface ou renderização.
- Documentação atualizada.
- Lista de arquivos alterados.

Uma tarefa não pode ser considerada concluída apenas porque compila ou porque possui uma interface.

# 5. PROTOCOLO DE EXECUÇÃO CONTÍNUA — 4 HORAS

O Goal deve trabalhar autonomamente em sessões de aproximadamente quatro horas de trabalho efetivo.

Durante a sessão:
1. Ler este ROADMAP e `docs/EXECUTION_LOG.md`.
2. Identificar tarefas pendentes e dependências.
3. Priorizar defeitos críticos e tarefas que desbloqueiam outros módulos.
4. Implementar continuamente.
5. Compilar Release após cada alteração de código.
6. Executar testes e corrigir regressões.
7. Validar visualmente as funcionalidades.
8. Atualizar documentação e RAG.
9. Fazer commit e push de conjuntos coerentes e validados.
10. Continuar automaticamente para a próxima tarefa.

Não interromper para pedir aprovação entre tarefas. Não parar após planejamento ou auditoria. Não encerrar após completar apenas uma tarefa ou módulo.

A ordem dos módulos pode ser ajustada por dependências técnicas, mas nenhuma área deve ser esquecida.

# 6. CONTROLE DE EXECUÇÃO

Criar e manter `docs/EXECUTION_LOG.md`.

Registrar:
- Sessões e duração efetiva.
- Identificadores das tarefas executadas.
- Concluídas, pendentes e bloqueadas.
- Arquivos criados, alterados e removidos.
- Compilações e resultados dos testes.
- Evidências de validação.
- Commits e SHAs publicados.
- Próxima tarefa exata para retomada.

Se houver interrupção por limite de contexto, tempo ou execução, salvar o progresso e retomar da próxima tarefa pendente na sessão seguinte.

# 7. CRITÉRIO DE CONCLUSÃO DO PROJETO

O ArtPlus só poderá ser considerado concluído quando:
- Os 22 módulos tiverem sido avaliados.
- Todas as tarefas aplicáveis estiverem implementadas e validadas.
- Não existirem menus ou botões anunciando operações inexistentes.
- As funções críticas possuírem testes e evidências.
- A compilação Release e os testes de regressão estiverem aprovados.
- A inicialização e os fluxos principais tiverem sido validados.
- As limitações restantes estiverem documentadas explicitamente.

**REGRA FINAL: O ROADMAP É UMA ORDEM DE EXECUÇÃO CONTÍNUA. O AGENTE DEVE IMPLEMENTAR, TESTAR, CORRIGIR E AVANÇAR AUTOMATICAMENTE ATÉ O LIMITE REAL DA SESSÃO. NÃO DEVE ESPERAR NOVAS INSTRUÇÕES DO USUÁRIO ENTRE AS TAREFAS.**