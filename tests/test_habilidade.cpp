#include "doctest.h"
#include "Habilidade.hpp"
#include "Jogador.hpp"
#include "Questao.hpp"

TEST_CASE("Testando criacao de Habilidade ofensiva (afeta inimigo por padrao)") {
    Habilidade hab("Regra da Cadeia", "Causa dano adicional a questao", 15);

    CHECK(hab.getNome() == "Regra da Cadeia");
    CHECK(hab.getDescricao() == "Causa dano adicional a questao");
    CHECK(hab.getEfeitoValor() == 15);
    CHECK(hab.afetaInimigo() == true);
}

TEST_CASE("Testando criacao de Habilidade de suporte (afeta o jogador)") {
    Habilidade hab("L'Hopital", "Reduz o cansaco do jogador", 20, false);

    CHECK(hab.getNome() == "L'Hopital");
    CHECK(hab.getDescricao() == "Reduz o cansaco do jogador");
    CHECK(hab.getEfeitoValor() == 20);
    CHECK(hab.afetaInimigo() == false);
}

TEST_CASE("Testando casos limites e valores de Habilidade") {
    SUBCASE("Habilidade com efeito nulo") {
        Habilidade hab("Revisao Teorica", "Nenhum efeito imediato", 0, true);
        CHECK(hab.getEfeitoValor() == 0);
        CHECK(hab.afetaInimigo() == true);
    }

    SUBCASE("Habilidade com descricao e nome longos") {
        std::string nomeLongo = "Teorema Fundamental do Calculo Integral - Parte 1";
        std::string descLonga = "Aplica derivacao sob o sinal de integracao e simplifica o limite";
        Habilidade hab(nomeLongo, descLonga, 50, true);

        CHECK(hab.getNome() == nomeLongo);
        CHECK(hab.getDescricao() == descLonga);
        CHECK(hab.getEfeitoValor() == 50);
    }
}

TEST_CASE("Testando aplicacao de efeito de Habilidade de suporte no Jogador") {
    Habilidade suporte("Descanso Rapido", "Reduz cansaco", 20, false);
    Habilidade ofensiva("Regra da Cadeia", "Causa dano", 25, true);

    SUBCASE("Reduz o cansaco do jogador corretamente") {
        Jogador jogador("Carlos", 50);
        suporte.aplicarEfeito(jogador);
        CHECK(jogador.getCansaco() == 30);
    }

    SUBCASE("Cansaco do jogador nao fica negativo") {
        Jogador jogador("Carlos", 10);
        suporte.aplicarEfeito(jogador);
        CHECK(jogador.getCansaco() == 0);
    }

    SUBCASE("Habilidade ofensiva nao altera o cansaco do jogador") {
        Jogador jogador("Carlos", 40);
        ofensiva.aplicarEfeito(jogador);
        CHECK(jogador.getCansaco() == 40);
    }
}

TEST_CASE("Testando aplicacao de efeito de Habilidade ofensiva na Questao") {
    Habilidade ofensiva("Fatoracao Algebrica", "Dano na questao", 25, true);
    Habilidade suporte("Meditacao", "Reduz cansaco", 15, false);

    SUBCASE("Causa dano de resolucao na questao") {
        Questao questao("Limite", 1, 50, "Fatore a expressao");
        ofensiva.aplicarEfeito(questao);
        CHECK(questao.getVidaResolucao() == 25);
        CHECK(questao.isResolvida() == false);
    }

    SUBCASE("Dano suficiente zera a vida e resolve a questao") {
        Questao questao("Limite", 1, 20, "Fatore a expressao");
        ofensiva.aplicarEfeito(questao);
        CHECK(questao.getVidaResolucao() == 0);
        CHECK(questao.isResolvida() == true);
    }

    SUBCASE("Habilidade de suporte nao altera a vida da questao") {
        Questao questao("Limite", 1, 50, "Fatore a expressao");
        suporte.aplicarEfeito(questao);
        CHECK(questao.getVidaResolucao() == 50);
    }
}


