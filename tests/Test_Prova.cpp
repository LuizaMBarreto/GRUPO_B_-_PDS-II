#include "doctest.h"
#include "Prova.hpp"

TEST_CASE("Testando construtor padrao de Prova") {
    Prova prova;

    CHECK(prova.getQuestoes().empty());
    CHECK(prova.getQuestoes().size() == 0u);
}

TEST_CASE("Testando valores iniciais de assunto e dificuldade da Prova") {
    Prova prova;

    CHECK(prova.getAssunto() == 0);
    CHECK(prova.getDificuldade() == 0);
}

TEST_CASE("Testando consistencia dos getters de Prova") {
    Prova prova;

    SUBCASE("Chamadas repetidas retornam o mesmo assunto") {
        CHECK(prova.getAssunto() == prova.getAssunto());
    }

    SUBCASE("Chamadas repetidas retornam a mesma dificuldade") {
        CHECK(prova.getDificuldade() == prova.getDificuldade());
    }

    SUBCASE("Duas provas padrao possuem os mesmos atributos") {
        Prova outra;
        CHECK(prova.getAssunto() == outra.getAssunto());
        CHECK(prova.getDificuldade() == outra.getDificuldade());
        CHECK(prova.getQuestoes().size() == outra.getQuestoes().size());
    }
}

TEST_CASE("Testando que getQuestoes devolve uma copia da lista") {
    Prova prova;

    std::vector<Questao> copia = prova.getQuestoes();
    copia.push_back(Questao("Limite", 1, 10, "Analise o limite pela esquerda"));

    CHECK(copia.size() == 1u);
    CHECK(prova.getQuestoes().empty());
}

TEST_CASE("Testando limites dos valores de Prova") {
    Prova prova;

    CHECK(prova.getAssunto() >= 0);
    CHECK(prova.getDificuldade() >= 0);
}
