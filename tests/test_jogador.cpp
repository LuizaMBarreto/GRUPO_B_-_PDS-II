#include "doctest.h"
#include "Jogador.hpp"
#include "Habilidade.hpp"
#include "Item.hpp"

TEST_CASE("Jogador - Criacao com atributos padrao e personalizados") {
    SUBCASE("Atributos padrao") {
        Jogador j("Carlos");
        CHECK(j.getCansaco() == 0);
        CHECK(j.getDano() == 10);
        CHECK(j.getHabilidades().empty());
        CHECK(j.getItens().empty());
    }

    SUBCASE("Atributos personalizados") {
        Jogador j("Ana", 15, 25);
        CHECK(j.getCansaco() == 15);
        CHECK(j.getDano() == 25);
    }

    SUBCASE("Cansaco inicial negativo deve ser ajustado para zero") {
        Jogador j("Pedro", -10, 15);
        CHECK(j.getCansaco() == 0);
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

TEST_CASE("Jogador - Adicao e uso de itens do inventario") {
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
        
        j.usarItem(0); // usa 1 unidade do item no indice 0
        
        // Se a implementacao de usarEmJogador decrementar a quantidade, restará 1
        CHECK(j.getItens().size() == 1);
        CHECK(j.getItens()[0].getQuantidade() == 1);

        j.usarItem(0); // usa a última unidade
        // Item deve ser removido do inventário ao atingir quantidade 0
        CHECK(j.getItens().empty());
    }

    SUBCASE("Usar item com indice invalido nao deve causar travamento") {
        j.adicionarItem(itemCura);
        j.usarItem(10); // Índice fora dos limites
        CHECK(j.getItens().size() == 1);
    }
}