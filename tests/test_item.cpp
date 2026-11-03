#include "doctest.h"
#include "Item.hpp"
#include "Jogador.hpp"
#include "Questao.hpp"
#include "Excecoes.hpp"

TEST_CASE("Item - Criacao com atributos") {
    Item item("Pocao de Energia", "Restaura 20 pontos de energia", 2, "CURA_ENERGIA");

    CHECK(item.getNome() == "Pocao de Energia");
    CHECK(item.getDescricao() == "Restaura 20 pontos de energia");
    CHECK(item.getQuantidade() == 2);
    CHECK(item.getTipoEfeito() == "CURA_ENERGIA");
}

TEST_CASE("Item - Modificacao de quantidade") {
    Item item("Cafe", "Reduz o cansaco em 10 pontos", 3, "CURA_ENERGIA");

    SUBCASE("Adicionar quantidade") {
        item.adicionarQuantidade(3);
        CHECK(item.getQuantidade() == 6);
    }

    SUBCASE("Decrementar quantidade") {
        item.decrementarQuantidade();
        CHECK(item.getQuantidade() == 2);
    }

    SUBCASE("Quantidade nao fica negativa") {
        item.decrementarQuantidade();
        item.decrementarQuantidade();
        item.decrementarQuantidade();
        item.decrementarQuantidade();
        CHECK(item.getQuantidade() == 0);
    }
}

TEST_CASE("Item - Uso em jogador com excecoes") {
    Jogador jogador("Cassia");
    Item item("Pocao de Energia", "Restaura 20 pontos de energia", 2, "CURA_ENERGIA");

    SUBCASE("Uso com quantidade disponivel") {
        CHECK_NOTHROW(item.usarEmJogador(&jogador));
        CHECK(item.getQuantidade() == 1);
    }

    SUBCASE("Uso com ponteiro nulo lanca ParametroInvalidoException") {
        CHECK_THROWS_AS(item.usarEmJogador(nullptr), ParametroInvalidoException);
    }
}

TEST_CASE("Item - Uso em questao com excecoes") {
    Questao questao("Integral", 3, 30, "Tente integracao por partes");
    Item item("Dica de Integral", "Revela a dica da questao", 1, "DICA");

    SUBCASE("Uso com questao valida") {
        CHECK_NOTHROW(item.usarEmQuestao(&questao));
    }

    SUBCASE("Uso com questao nula lanca ParametroInvalidoException") {
        CHECK_THROWS_AS(item.usarEmQuestao(nullptr), ParametroInvalidoException);
    }
}

TEST_CASE("Item - Uso com quantidade zero lanca ItemEsgotadoException") {
    Jogador jogador("Cassia");
    Questao questao("Limite", 1, 10, "Analise o limite pela esquerda");
    Item item("Pocao de Energia", "Restaura 20 pontos de energia", 0, "CURA_ENERGIA");

    CHECK_THROWS_AS(item.usarEmJogador(&jogador), ItemEsgotadoException);
    CHECK_THROWS_AS(item.usarEmQuestao(&questao), ItemEsgotadoException);
    CHECK(item.getQuantidade() == 0);
}