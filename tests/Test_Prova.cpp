#include "doctest.h"
#include "Prova.hpp"
#include "Excecoes.hpp"

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

TEST_CASE("Prova - adicionar questoes") {
    Prova prova(1, 1);

    SUBCASE("Adicionar questao valida preserva a ordem") {
        prova.adicionarQuestao(Questao("Limite", 1, 50, "dica A"));
        prova.adicionarQuestao(Questao("Derivada", 2, 75, "dica B"));
        CHECK(prova.getQuestoes().size() == 2u);
        CHECK(prova.getQuestoes()[0].getAssunto() == "Limite");
        CHECK(prova.getQuestoes()[1].getAssunto() == "Derivada");
    }

    SUBCASE("Questao ja resolvida lanca ParametroInvalidoException") {
        Questao resolvida("Limite", 1, 10, "dica");
        resolvida.receberDanoResolucao(10);
        CHECK_THROWS_AS(prova.adicionarQuestao(resolvida), ParametroInvalidoException);
        CHECK(prova.getQuestoes().empty());
    }
}

TEST_CASE("Prova - acesso seguro as questoes") {
    Prova prova(1, 1);
    prova.adicionarQuestao(Questao("Limite", 1, 50, "dica"));

    CHECK(prova.getQuestao(0).getAssunto() == "Limite");
    CHECK_THROWS_AS(prova.getQuestao(1), IndiceInvalidoException);
    CHECK_THROWS_AS(Prova().getQuestao(0), IndiceInvalidoException);
}
