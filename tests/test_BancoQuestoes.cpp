#include "doctest.h"
#include "BancoQuestoes.hpp"
#include "Semestre.hpp"
#include "Jogador.hpp"
#include "Excecoes.hpp"

TEST_CASE("BancoQuestoes - Criacao do jogador inicial de Calculo I") {
    Jogador jogador = BancoQuestoes::criarJogadorInicial("Carlos");

    CHECK(jogador.getCansaco() == 0);
    CHECK(jogador.getDano() == 10);
    CHECK(jogador.getHabilidades().size() >= 5);
    CHECK(jogador.getItens().size() >= 2);

    SUBCASE("Habilidades iniciais contemplam conteudos de Limites, Derivadas e Integrais") {
        bool temFatoracao = false;
        bool temCadeia = false;
        bool temPartes = false;
        bool temSuporte = false;

        for (const auto& hab : jogador.getHabilidades()) {
            if (hab.getNome() == "Fatoracao Algebrica") temFatoracao = true;
            if (hab.getNome() == "Regra da Cadeia") temCadeia = true;
            if (hab.getNome() == "Integracao por Partes") temPartes = true;
            if (!hab.afetaInimigo()) temSuporte = true;
        }

        CHECK(temFatoracao);
        CHECK(temCadeia);
        CHECK(temPartes);
        CHECK(temSuporte);
    }

    SUBCASE("Itens iniciais incluem cafe e livro de dicas") {
        bool temCafe = false;
        bool temLivro = false;

        for (const auto& item : jogador.getItens()) {
            if (item.getNome() == "Cafe Quente") temCafe = true;
            if (item.getNome() == "Anotacoes") temLivro = true;
        }

        CHECK(temCafe);
        CHECK(temLivro);
    }
}

TEST_CASE("BancoQuestoes - Carregamento das 4 Provas no Semestre") {
    Jogador jogador = BancoQuestoes::criarJogadorInicial("Carlos");
    Semestre semestre(jogador);

    BancoQuestoes::carregarProvasNoSemestre(semestre);

    CHECK(semestre.getTotalProvas() == 4);
    CHECK(semestre.getIndiceProvaAtual() == 0);

    SUBCASE("Prova 1 (Limites) contem 2 questoes de calculo") {
        const Prova& p1 = semestre.getProvaAtual();
        CHECK(p1.getAssunto() == 1);
        CHECK(p1.getDificuldade() == 1);
        CHECK(p1.getQuestoes().size() == 2);
        CHECK(p1.getQuestoes()[0].getVidaResolucao() == 50);
        CHECK(p1.getQuestoes()[0].getdanoContraAtaque() > 0);
    }

    SUBCASE("Avanco de provas pelo semestre") {
        CHECK(semestre.temProximaProva());
        semestre.gerenciarFilaDeTurnos(); // P1 -> P2
        CHECK(semestre.getIndiceProvaAtual() == 1);
        CHECK(semestre.getProvaAtual().getAssunto() == 2);

        semestre.gerenciarFilaDeTurnos(); // P2 -> P3
        CHECK(semestre.getIndiceProvaAtual() == 2);
        CHECK(semestre.getProvaAtual().getAssunto() == 3);

        semestre.gerenciarFilaDeTurnos(); // P3 -> P4
        CHECK(semestre.getIndiceProvaAtual() == 3);
        CHECK(semestre.getProvaAtual().getAssunto() == 4);
        CHECK_FALSE(semestre.temProximaProva());

        // Testando tratamento de excecao defensiva ao tentar avancar alem da ultima prova
        CHECK_THROWS_AS(semestre.gerenciarFilaDeTurnos(), IndiceInvalidoException);
    }
}

