#include "doctest.h"
#include "BatalhaTerminal.hpp"
#include "BancoQuestoes.hpp"
#include "Excecoes.hpp"
#include <sstream>

TEST_CASE("BatalhaTerminal - Exibicao e processamento de opcoes no terminal") {
    Jogador jogador = BancoQuestoes::criarJogadorInicial("Carlos");
    Semestre semestre(jogador);
    BancoQuestoes::carregarProvasNoSemestre(semestre);

    const Prova& p1 = semestre.getProvaAtual();
    BatalhaTerminal batalha(jogador, p1, 1);

    SUBCASE("Exibicao inicial com Prova, Questao e Opcoes 1 a 4") {
        std::ostringstream out;
        batalha.exibirEstadoAtual(out);
        std::string texto = out.str();

        CHECK(texto.find("PROVA 1 - QUESTAO 1 DE 2") != std::string::npos);
        CHECK(texto.find("Enunciado: Limite Polinomial por Diferenca de Quadrados") != std::string::npos);
        CHECK(texto.find("1. Habilidades") != std::string::npos);
        CHECK(texto.find("2. Itens") != std::string::npos);
        CHECK(texto.find("3. Dicas") != std::string::npos);
        CHECK(texto.find("4. Finalizar") != std::string::npos);
    }

    SUBCASE("Opcao 1 imprime lista de habilidades") {
        std::ostringstream out;
        batalha.processarOpcao(1, out);
        std::string texto = out.str();

        CHECK(texto.find("LISTA DE HABILIDADES") != std::string::npos);
        CHECK(texto.find("Fatoracao Algebrica") != std::string::npos);
        CHECK(texto.find("Regra da Cadeia") != std::string::npos);
    }

    SUBCASE("Opcao 2 imprime lista de itens") {
        std::ostringstream out;
        batalha.processarOpcao(2, out);
        std::string texto = out.str();

        CHECK(texto.find("LISTA DE ITENS") != std::string::npos);
        CHECK(texto.find("Cafe Quente") != std::string::npos);
        CHECK(texto.find("Livro de Stewart") != std::string::npos);
    }

    SUBCASE("Opcao 3 imprime a dica da questao") {
        std::ostringstream out;
        batalha.processarOpcao(3, out);
        std::string texto = out.str();

        CHECK(texto.find("DICA DA QUESTAO") != std::string::npos);
        CHECK(texto.find("diferenca de quadrados") != std::string::npos);
    }

    SUBCASE("Opcao 4 verifica se e possivel finalizar a questao") {
        std::ostringstream out;
        batalha.processarOpcao(4, out);
        std::string texto = out.str();

        CHECK(texto.find("VERIFICACAO DE FINALIZACAO") != std::string::npos);
        CHECK(texto.find("Nao e possivel finalizar ainda") != std::string::npos);
    }
}
