#include "doctest.h"
#include "Habilidade.hpp"

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

