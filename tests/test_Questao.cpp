#include "doctest.h"
#include "Jogador.hpp"
#include "Questao.hpp"

TEST_CASE("Teste - Criação de questão com atributos personalizados"){
 Questao quest("derivada", 1, 50, "use a regra da cadeia", 15);
  CHECK(quest.getAssunto() == "derivada");
  CHECK(quest.getDificuldade() == 1);
  CHECK(quest.getVidaResolucao()== 50);
  CHECK(quest.fornecerDica() == "use a regra da cadeia");
  CHECK(quest.getBarraBonus()== 0);
  CHECK(quest.isResolvida() == false);
  CHECK(quest.isProntaParaFinalizar() == false);
  
}

//testes de receber dano
TEST_CASE("Questao - Receber dano da resolucao"){
  SUBCASE("Dano menor que a vida restante"){
  Questao quest("Derivadas", 1, 50, "Use a regra da potencia", 16);
  
  quest.receberDanoResolucao(30);
  
  CHECK(quest.getVidaResolucao() == 20);
  CHECK(quest.isResolvida() == false);
}

SUBCASE("Dano igual a vida restante"){
    Questao quest("Integrais", 2, 75, "Procure uma primitiva", 15);
    quest.receberDanoResolucao(75);
    
    CHECK(quest.getVidaResolucao() == 0);
    CHECK(quest.isResolvida() == true);
}

SUBCASE("Dano maior que a vida restante"){
      Questao quest("Limites", 2, 75, "Use a regra do Confronto", 18);
    
    quest.receberDanoResolucao(100);
    
    CHECK(quest.getVidaResolucao() == 0);
    CHECK(quest.isResolvida() == true);

}
 SUBCASE("Receber dano em varias etapas") {
        Questao quest("Limites", 1, 50, "Simplifique a expressao", 10);

        quest.receberDanoResolucao(20);
        CHECK(quest.getVidaResolucao() == 30);

        quest.receberDanoResolucao(10);
        CHECK(quest.getVidaResolucao() == 20);

        quest.receberDanoResolucao(30);
        CHECK(quest.getVidaResolucao() == 0);
        CHECK(quest.isResolvida() == true);
    }
}

//teste da barra de bonus

TEST_CASE("Teste - incrementar barra de bonus"){
    Questao quest("Derivada", 2, 75, "Use a regra do produto", 13);
  
  SUBCASE("Zerar a barra de bonus"){
    CHECK(quest.getBarraBonus() == 0);
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

  TEST_CASE("Teste - Fornecimentos de dicas"){
     Questao quest("Limite", 3, 100, "Tem uma assíntota aí", 19);
    CHECK(quest.fornecerDica() == "Tem uma assíntota aí");
  //faça um subcase caso seja decidido que teremos dicas vazia
}

TEST_CASE("Teste - Finalizar questao"){
  SUBCASE("Não pode finalizar sem concluir a etapa anterior"){
      Questao quest("Integral", 3, 100, "Tente a substituição trigonométrica", 20);
      CHECK(quest.isProntaParaFinalizar() == false);
      CHECK(quest.isResolvida() == false);
      CHECK(quest.tentarFinalizar() == false);
      CHECK(quest.getVidaResolucao() == 100);
  }
 
}
TEST_CASE("Teste - executa a ação inimiga"){

 SUBCASE("Uma tentaiva errada aumenta o cansaco"){
  Questao quest("Derivada", 2, 75, "Use a regra da cadeia", 15);
  Jogador j("Carlos");
 

    int cansacoInicial = j.getCansaco();
  
    quest.executarAcaoInimiga(&j);
    CHECK(j.getCansaco() == 15);
}

SUBCASE("Tentivas erradas acumulam cansaco"){
 
   Questao quest("Limite", 1, 5, "Use a fatoracao", 15);
   Jogador j("Carlos");
 
   quest.executarAcaoInimiga(&j);
  CHECK(j.getCansaco() == 15);
 
 quest.executarAcaoInimiga(&j);
 CHECK (j.getCansaco() == 30);

 quest.executarAcaoInimiga(&j);
 CHECK(j.getCansaco() == 45);
}

SUBCASE("Questao resolvida nao contra ataca"){
  Questao quest("Derivada", 2, 75, "Use a regra da cadeia", 15);
  Jogador j("Carlos");
  
quest.receberDanoResolucao(75);
CHECK(quest.isResolvida() == true);
quest.executarAcaoInimiga(&j);
CHECK(j.getCansaco() == 0);
}

SUBCASE("Ponteiro nulo nao causa alteracoes"){
 Questao quest("Limite", 1, 50, "Use a fatoracao", 15);
 quest.executarAcaoInimiga(nullptr);
 CHECK(quest.getVidaResolucao() == 50);
 CHECK(quest.IsResolvida() == false);
}

}
TEST_CASE("Questao so pode finalizar apos concluir etapa previa") {
    Questao questao("Limite", 1, 10, "Olhe as assíntotas", 10);

    CHECK_FALSE(questao.isProntaParaFinalizar());
    CHECK_FALSE(questao.tentarFinalizar());
    CHECK_FALSE(questao.isResolvida());

    questao.concluirEtapaPrevia();

    CHECK(questao.isProntaParaFinalizar());
    CHECK(questao.tentarFinalizar());
    CHECK(questao.isResolvida());
    CHECK(questao.getVidaResolucao() == 0);
}

TEST_CASE("Dano negativo nao aumenta a vida da questao") {
    Questao questao("Limite", 1, 10, "olhe as assíntotas");

    questao.receberDanoResolucao(-5);

    CHECK(questao.getVidaResolucao() == 10);
    CHECK_FALSE(questao.isResolvida());
}

TEST_CASE("Questao resolvida nao recebe mais dano") {
    Questao questao("Limite", 1, 10, "Regra do confronto", 10);

    questao.receberDanoResolucao(10);

    CHECK(questao.isResolvida());
    CHECK(questao.getVidaResolucao() == 0);

    questao.receberDanoResolucao(5);

    CHECK(questao.getVidaResolucao() == 0);
    CHECK(questao.isResolvida());
}



