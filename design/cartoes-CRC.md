
## CLASSE: Jogador
RESPONSABILIDADES:
  1. Manter e informar o nível atual de cansaço/energia (Saber)
  2. Armazenar a lista de habilidades conhecidas e seus custos (Saber)
  3. Gerenciar o inventário de itens e quantidades disponíveis (Saber)
  4. Executar uma habilidade consumindo energia no seu turno (Fazer)
  5. Usar um item consumível do inventário (Fazer)
  6. Aplicar dano na prova após resolver uma questão (Fazer)

COLABORAÇÕES:
  - Habilidade
  - Item
  - Questao

--------------------------------------------------------------------------------
## CLASSE: Prova

RESPONSABILIDADES:
  1. Armazenar a lista de questões predeterminadas da avaliação (Saber)
  2. Identificar o assunto da prova (Limite, Derivada, Integral ou Geral) (Saber)
  3. Controlar os pontos de vida/dano acumulado da prova (Saber)
  4. Verificar se todas as questões da prova foram resolvidas (Fazer)
  5. Calcular a pontuação final obtida na prova (Fazer)

COLABORAÇÕES:
  - Questao
  - Jogador

--------------------------------------------------------------------------------
## CLASSE: Questão

RESPONSABILIDADES:
  1. Guardar o assunto e o nível de dificuldade da questão (Saber)
  2. Armazenar as habilidades específicas do inimigo/questão (Saber)
  3. Manter o estado da questão (Pendente ou Resolvida) (Saber)
  4. Gerenciar a barra de bônus de energia concedida ao jogador (Saber)
  5. Executar ações/ataques automáticos contra o jogador no seu turno (Fazer)
  6. Fornecer dicas de resolução quando acionada (Fazer)

COLABORAÇÕES:
  - Habilidade
  - Jogador

--------------------------------------------------------------------------------
## CLASSE: Item

RESPONSABILIDADES:
  1. Armazenar o nome, descrição e quantidade do item (Saber)
  2. Guardar o tipo de efeito do item (recuperar energia, dar dica, etc.) (Saber)
  3. Aplicar o efeito no jogador ao ser consumido (Fazer)
  4. Aplicar efeitos negativos ou enfraquecer a questão alvo (Fazer)
  5. Atualizar/Decrementar a quantidade do item no inventário (Fazer)

COLABORAÇÕES:
  - Jogador
  - Questao

--------------------------------------------------------------------------------
## CLASSE: Habilidade

RESPONSABILIDADES:
  1. Armazenar o nome e o custo de energia da habilidade (Saber)
  2. Guardar o assunto/tipo ao qual a habilidade pertence (Saber)
  3. Definir o valor de dano ou efeito de resolução gerado (Saber)
  4. Aplicar o efeito no jogador (ex: recuperar energia/bônus) (Fazer)
  5. Aplicar o efeito na questão alvo para tentar resolvê-la (Fazer)

COLABORAÇÕES:
  - Jogador
  - Questao

--------------------------------------------------------------------------------
## CLASSE: Semestre

RESPONSABILIDADES:
  1. Armazenar a lista de provas do semestre e a ordem de execução (Saber)
  2. Somar a pontuação total alcançada ao longo de todas as provas (Saber)
  3. Gerenciar a fila e o fluxo do turno entre o jogador e as questões (Fazer)
  4. Permitir que o jogador explore a sala entre as provas para achar itens (Fazer)
  5. Validar as condições de vitória ou derrota do jogador no combate/semestre (Fazer)

COLABORAÇÕES:
  - Prova
  - Jogador
