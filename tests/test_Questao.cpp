#include "doctest.h"
#include "Jogador.h"
#include "Questao.h"

TEST_CASE("Teste - Criação de questão com atributos personalizados"){
 Questao quest("derivada", 1, 50, "use a regra da cadeia");
  CHECK(quest.getassunto() == "derivada");
  CHECK(quest.getDificuldade() == 1);
  CHECK(quest.getVidaResolucao()== 100);
  CHECK(quest.fornecerDica() == "use a regra da cadeia");
  CHECK(quest.getBarraBonus()== 0);
  CHECK(quest.isResolvida() == false);
  CHECK(quest.isProntaParaFinalizar() == false);
  
}

//testes de receber dano
TEST_CASE("Questao - Receber dano da resolucao"){
  SUBCASE("Dano menor que a vida restante"){
  Questao quest("Derivadas", 1, 50, "Use a regra da potencia");
  
  quest.receberDanoResolucao(30);
  
  CHECK(quest.getVidaResolucao() == 50);
  CHECK(quest.isResolvida() == false);
}

SUBCASE("Dano igual a vida restante"){
    Questao quest("Integrais", 2, 75, "Procure uma primitiva");
    quest.receberDanoResolucao(50);
    
    CHECK(quest.getVidaResolucao() == 50);
    CHECK(quest.isResolvida() == true);
}

SUBCASE("Dano maior que a vida restante"){
      Questao quest("Limites", 3, 100, "Use a regra do Confronto");
    
    quest.receberDanoResolucao(50);
    
    CHECK(quest.getVidaResolucao() == 30);
    CHECK(quest.isResolvida() == true);

}
 SUBCASE("Receber dano em varias etapas") {
        Questao quest("Limites", 1, 50, "Simplifique a expressao");

        quest.receberDanoResolucao(20);
        CHECK(quest.getVidaResolucao() == 50);

        quest.receberDanoResolucao(10);
        CHECK(quest.getVidaResolucao() == 20);

        quest.receberDanoResolucao(30);
        CHECK(quest.getVidaResolucao() == 0);
        CHECK(quest.isResolvida() == true);
    }
}

//teste da barra de bonus

TEST_CASE("Teste - incrementar barra de bonus"){
    Questao quest("Derivada", 2, 75, "Use a regra do produto");
  
  SUBCASE("Zerar a barra de bonus"){
    CHECK(quest.getBarradeBonus() == 0);
  }

  SUBCASE("incrementar bonus uma unica vez"){
      quest.incrementarBonus(10);
      CHECK(quest.getBarraBonus() == 10);
}
  
  SUBCASE("incrementar bonus varias vezes"){
      quest.incrementarBonus(10);
      quest.incrementarBonus(3);
      quest.incrementarBonus(25);
    CHECK(quest.getBarraBonus() == 38);
  } 
}

  TESTE_CASE("Teste - Fornecimentos de dicas"){
     Questao quest("Limite", 3, 100, "Tem uma assíntota aí");
    CHECK(quest.forncercerDica() == "Tem uma assíntota aí");
  //faça um subcase caso seja decidido que teremos dicas vazia
}

TESTE_CASE("Teste - Finalizar questao"){
  SUBCASE("Não pode finalizar sem concluir a etapa anterior"){
      Questao quest("Integral", 3, 100, "Tente a substituição trigonométrica");
      CHECK(quest.isProntaParaFinalizar() == false);
      CHECK(quest.isResolvida() == false);
      CHECK(quest.tentarFinalizar() == false);
      CHECK(quest.getVidaResolucao() == 100);
  }
  SUBCASE("Finalizar sem pendências"){
    Questao quest("Limite", 1, 50, "Tem uma assíntota aí");
    CHECK(quest.isProntaParaFinalizar() == false);
    CHECK(quest.tentarFinalizar() == false);
   //Precisa de um mecanismo que a altere para true
  //Provavelmente vamos ter alterar a classe
  }
}
TESTE_CASE("Teste - executa a ação inimiga"){
  Questao quest("Derivada", 2, 75, "Use a regra da cadeia");
  Jogador j("Carlos");
  //ainda e uma stub e, portanto, não altera o jogador
    quest.executarAcaoInimiga(&j);
    CHECK(j.getCansaco() == cansacoInicial);
    CHECK(quest.getVidaResolucao() == 100);
    CHECK(quest.isResolvida() == false);
}
  
}






