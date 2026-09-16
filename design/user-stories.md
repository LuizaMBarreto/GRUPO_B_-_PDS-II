# User Stories

* User Story 01
Como jogador, quero poder atacar meu inimigo durante meu turno,
para diminuir seus pontos de vida.

** Critérios de Aceitação:
- O jogador deve poder escolher a ação de atacar durante seu turno.
- O ataque escolhido pelo jogador deve ser executado contra o inimigo selecionado.
- O ataque deve ter potencial de diminuir os pontos de vida
do inimigo, tendo um efeito de força equivalente a [ataquejogador - defesainimigo = dano]
- A força/dano do ataque deve depender dos pontos de experiência (exp) do jogador.
- Se a força do ataque for maior que a defesa do inimigo ele deve sofrer perdas diretas
em seus pontos de vida, do contrário, apenas sua defesa sofre danos.
--------------------------------------------------------------------------------------------------------------------------------------

* User Story 02
Como jogador quero que meus pontos de experiencia aumentem conforme eu avanço no jogo.

** Critérios de Aceitação:
- O jogador deve iniciar com uma quantidade mínima de pontos de experiência.
- O jogador deve receber uma certa quantidade de pontos de experiência ao derrotar um inimigo,
sendo estes pontos somados sempre a quantidade anterior detida pelo jogador.
- A quantidade de pontos de experiência recebida pelo jogador ao derrotar um inimigo
deve considerar a defesa do inimigo.
- A força de ataque do jogador deve ser determinada pela quantidade de pontos de experiência
detidos.
- O jogador deve conseguir consultar a quantidade de experiência acumulada durante o jogo.
--------------------------------------------------------------------------------------------------------------------------------------

* User Stories 03
Como sistema de combate, quero que inimigos tenham pontos de vida que diminuem quando sofrem ataques, para que possam ser derrotados 

Critérios de Aceitação:
- Cada inimigo deve iniciar o combate com uma quantidade máxima de vida baseada em seu nível/tipo.
- A vida do inimigo deve diminuir conforme recebe ataques, se chegar a 0,  deve ser derrotado e removido do combate.
- O jogador deve poder visualizar a vida atual e máxima de cada inimigo durante o combate.
--------------------------------------------------------------------------------------------------------------------------------------

* User Stories 04
Como desenvolvedor, quero que cada inimigo tenha características próprias 

Critérios de Aceitação:
- Cada inimigo deve ter um nível de força (baixo, médio ou alto) que determina sua força de ataque.
- Cada inimigo deve ter um tamanho (pequeno, médio ou grande) que pode influenciar sua vida máxima e defesa.
- Inimigos do mesmo tipo devem ter as mesmas características base
- O jogador deve poder visualizar as características de cada inimigo durante o combate (força, tamanho).
--------------------------------------------------------------------------------------------------------------------------------------

* User Stories 05
Como sistema de combate, quero alternar a vez de agir entre o jogador e os inimigos em turnos sequenciais, para garantir uma estrutura organizada de partida.

** Critérios de Aceitação:
- O sistema deve definir a fila de turnos no início do combate.
- O turno deve passar para o próximo participante assim que a ação atual for concluída.
- Os inimigos devem realizar seus ataques automaticamente durante a vez deles.
- O combate deve ser encerrado imediatamente quando a vida do jogador ou de todos os inimigos chegar a 0.
