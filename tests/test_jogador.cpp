#include "doctest.h"
#include "Jogador.hpp"
#include "Habilidade.hpp"
#include "Item.hpp"
#include "Excecoes.hpp"

TEST_CASE("Jogador - Criacao com atributos e excecoes") {
    SUBCASE("Atributos padrao e personalizados") {
        Jogador j1("Carlos");
        CHECK(j1.getCansaco() == 0);
        CHECK(j1.getDano() == 10);

        Jogador j2("Ana", 15, 25);
        CHECK(j2.getCansaco() == 15);
        CHECK(j2.getDano() == 25);
    }

    SUBCASE("Cansaco inicial negativo ajustado para zero") {
        Jogador j("Pedro", -10, 15);
        CHECK(j.getCansaco() == 0);
    }

    SUBCASE("Dano base invalido (<= 0) lanca ParametroInvalidoException") {
        CHECK_THROWS_AS(Jogador("Invalido", 0, 0), ParametroInvalidoException);
        CHECK_THROWS_AS(Jogador("Invalido", 0, -5), ParametroInvalidoException);
    }
}

TEST_CASE("Jogador - Alteracao e limites de cansaco") {
    Jogador j("Heroi", 10, 10);

    SUBCASE("Aumentar cansaco (delta positivo)") {
        j.alterarCansaco(15);
        CHECK(j.getCansaco() == 25);
    }

    SUBCASE("Reduzir cansaco (delta negativo)") {
        j.alterarCansaco(-5);
        CHECK(j.getCansaco() == 5);
    }

    SUBCASE("Cansaco nao deve ser menor que zero") {
        j.alterarCansaco(-20);
        CHECK(j.getCansaco() == 0);
    }
}

TEST_CASE("Jogador - Adicao e consulta de habilidades") {
    Jogador j("Mago");
    
    Habilidade h1("Bola de Fogo", "Causa dano de fogo no inimigo", 30, true);
    Habilidade h2("Meditacao", "Reduz o cansaco do jogador", 10, false);

    CHECK(j.getHabilidades().size() == 0);

    j.adicionarHabilidade(h1);
    CHECK(j.getHabilidades().size() == 1);
    CHECK(j.getHabilidades()[0].getNome() == "Bola de Fogo");

    j.adicionarHabilidade(h2);
    CHECK(j.getHabilidades().size() == 2);
    CHECK(j.getHabilidades()[1].getNome() == "Meditacao");
}

TEST_CASE("Jogador - Adicao e uso de itens com IndiceInvalidoException") {
    Jogador j("Guerreiro", 20, 10);

    Item itemCura("Cafe", "Recupera energia/cansaco", 2, "CURA_ENERGIA");
    Item itemDica("Livro de Estudo", "Revela dica para a questao", 1, "DICA");

    SUBCASE("Adicionar novos itens ao inventario") {
        j.adicionarItem(itemCura);
        CHECK(j.getItens().size() == 1);
        CHECK(j.getItens()[0].getQuantidade() == 2);

        j.adicionarItem(itemDica);
        CHECK(j.getItens().size() == 2);
    }

    SUBCASE("Adicionar item existente deve acumular quantidade") {
        j.adicionarItem(itemCura);
        j.adicionarItem(Item("Cafe", "Recupera energia/cansaco", 3, "CURA_ENERGIA"));

        CHECK(j.getItens().size() == 1);
        CHECK(j.getItens()[0].getQuantidade() == 5);
    }

    SUBCASE("Usar item do inventario") {
        j.adicionarItem(itemCura); // quantidade = 2
        
        CHECK_NOTHROW(j.usarItem(0)); // usa 1 unidade do item no indice 0
        
        CHECK(j.getItens().size() == 1);
        CHECK(j.getItens()[0].getQuantidade() == 1);

        CHECK_NOTHROW(j.usarItem(0)); // usa a última unidade
        // Item deve ser removido do inventário ao atingir quantidade 0
        CHECK(j.getItens().empty());
    }

    SUBCASE("Usar item com indice invalido lanca IndiceInvalidoException") {
        j.adicionarItem(itemCura);
        CHECK_THROWS_AS(j.usarItem(10), IndiceInvalidoException); // Índice fora dos limites
        CHECK(j.getItens().size() == 1);
    }
}