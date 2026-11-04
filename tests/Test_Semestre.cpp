#include "doctest.h"
#include "Semestre.hpp"
#include "Excecoes.hpp"

TEST_CASE("Testando inicializacao do Semestre com o Jogador") {
    Jogador jogador("Carlos");
    Semestre semestre(jogador);

    CHECK(semestre.getPontuacaoAcumulada() == 0);
    CHECK(semestre.getIndiceProvaAtual() == 0u);
}

TEST_CASE("Testando que o Semestre guarda o Jogador recebido") {
    Jogador jogador("Ana", 15, 25);
    Semestre semestre(jogador);

    CHECK(semestre.getJogador().getCansaco() == 15);
    CHECK(semestre.getJogador().getDano() == 25);
    CHECK(semestre.getJogador().getHabilidades().empty());
    CHECK(semestre.getJogador().getItens().empty());
}

TEST_CASE("Testando adicao de provas ao Semestre") {
    Jogador jogador("Carlos");
    Semestre semestre(jogador);

    SUBCASE("Adicionar uma prova nao altera o indice da prova atual") {
        Prova prova;
        semestre.adicionarProva(prova);
        CHECK(semestre.getIndiceProvaAtual() == 0u);
    }

    SUBCASE("Adicionar as quatro provas (Limite, Derivada, Integral e Geral)") {
        Prova p1, p2, p3, p4;
        semestre.adicionarProva(p1);
        semestre.adicionarProva(p2);
        semestre.adicionarProva(p3);
        semestre.adicionarProva(p4);
        CHECK(semestre.getIndiceProvaAtual() == 0u);
    }

    SUBCASE("Prova atual corresponde a primeira prova adicionada") {
        Prova prova;
        semestre.adicionarProva(prova);
        CHECK(semestre.getProvaAtual().getAssunto() == prova.getAssunto());
        CHECK(semestre.getProvaAtual().getDificuldade() == prova.getDificuldade());
        CHECK(semestre.getProvaAtual().getQuestoes().size() == prova.getQuestoes().size());
    }
}

TEST_CASE("Testando acumulo de pontuacao do Semestre") {
    Jogador jogador("Carlos");
    Semestre semestre(jogador);

    SUBCASE("Somar uma pontuacao") {
        semestre.somarPontuacao(10);
        CHECK(semestre.getPontuacaoAcumulada() == 10);
    }

    SUBCASE("Somar varias pontuacoes acumula o total") {
        semestre.somarPontuacao(10);
        semestre.somarPontuacao(25);
        semestre.somarPontuacao(5);
        CHECK(semestre.getPontuacaoAcumulada() == 40);
    }

    SUBCASE("Somar zero nao altera a pontuacao") {
        semestre.somarPontuacao(0);
        CHECK(semestre.getPontuacaoAcumulada() == 0);
    }
}

TEST_CASE("Testando verificacao de fim de combate por cansaco") {
    // Limite maximo de cansaco definido pelo grupo: 100
    const int LIMITE_CANSACO = 100;

    SUBCASE("Combate termina quando o cansaco atinge exatamente o limite") {
        Jogador jogador("Exausto", LIMITE_CANSACO, 10);
        Semestre semestre(jogador);

        Prova prova;
        semestre.adicionarProva(prova);

        CHECK(semestre.verificarFimDeCombate() == true);
    }

    SUBCASE("Combate termina quando o cansaco ultrapassa o limite") {
        Jogador jogador("MuitoExausto", LIMITE_CANSACO + 50, 10);
        Semestre semestre(jogador);

        Prova prova;
        semestre.adicionarProva(prova);

        CHECK(semestre.verificarFimDeCombate() == true);
    }

    SUBCASE("Combate termina quando o cansaco chega ao limite apos alteracao") {
        Jogador jogador("Cansando", LIMITE_CANSACO - 1, 10);
        jogador.alterarCansaco(1);
        Semestre semestre(jogador);

        Prova prova;
        semestre.adicionarProva(prova);

        CHECK(semestre.verificarFimDeCombate() == true);
    }
}

TEST_CASE("Testando tratamento de excecoes em Semestre") {
    SUBCASE("Lanca excecao ao buscar prova atual sem provas cadastradas") {
        Jogador jogador("Carlos");
        Semestre semestre(jogador);

        CHECK_THROWS_AS(semestre.getProvaAtual(), IndiceInvalidoException);
    }

    SUBCASE("Tratamento de excecao com try/catch e verificacao da mensagem") {
        Jogador jogador("Carlos");
        Semestre semestre(jogador);

        try {
            semestre.getProvaAtual();
            FAIL("Deveria ter lancado IndiceInvalidoException");
        } catch (const IndiceInvalidoException& e) {
            CHECK(std::string(e.what()).find("Erro de Indice") != std::string::npos);
        }
    }

    SUBCASE("Lanca excecao ao somar pontuacao negativa") {
        Jogador jogador("Carlos");
        Semestre semestre(jogador);

        CHECK_THROWS_AS(semestre.somarPontuacao(-10), ParametroInvalidoException);
    }

    SUBCASE("Pontuacao nao e alterada apos tentativa negativa") {
        Jogador jogador("Carlos");
        Semestre semestre(jogador);
        semestre.somarPontuacao(20);

        try {
            semestre.somarPontuacao(-5);
        } catch (const ParametroInvalidoException&) {}

        CHECK(semestre.getPontuacaoAcumulada() == 20);
    }
}
