#include "BancoQuestoes.hpp"
#include "Habilidade.hpp"
#include "Item.hpp"
#include "Questao.hpp"
#include "Prova.hpp"

Jogador BancoQuestoes::criarJogadorInicial(const std::string& nome) {
    Jogador jogador(nome, 0, 10);

    // Habilidades matemáticas
    jogador.adicionarHabilidade(Habilidade(
        "Fatoracao Algebrica",
        "Simplifica indeterminacoes polinomiais 0/0 por diferenca de quadrados",
        25,
        true
    ));

    jogador.adicionarHabilidade(Habilidade(
        "Multiplicar Conjugado",
        "Racionaliza expressoes com raiz no limite",
        35,
        true
    ));

    jogador.adicionarHabilidade(Habilidade(
        "Regra da Cadeia",
        "Deriva composicoes de funcoes f(g(x))",
        35,
        true
    ));

    jogador.adicionarHabilidade(Habilidade(
        "Integracao por Partes",
        "Aplica a formula integral(u dv) = uv - integral(v du)",
        35,
        true
    ));

    jogador.adicionarHabilidade(Habilidade(
        "Regra de L'Hopital",
        "Deriva numerador e denominador para resolver indeterminacoes persistentes",
        30,
        true
    ));

    jogador.adicionarHabilidade(Habilidade(
        "Tomar um ar",
        "Faz uma pausa rapida para respirar e recuperar a energia",
        20,
        false
    ));

    // Itens iniciais no inventário
    jogador.adicionarItem(Item(
        "Cafe Quente",
        "Reduz o cansaco em 20 pontos",
        0,
        "CURA_ENERGIA"
    ));

    jogador.adicionarItem(Item(
        "Anotacoes",
        "Consulta anotacoes teoricas com dicas essenciais",
        0,
        "DICA"
    ));

    return jogador;
}

void BancoQuestoes::carregarProvasNoSemestre(Semestre& semestre) {
    // ----------------------------------------------------
    // PROVA 1: LIMITES E CONTINUIDADE (P1)
    // ----------------------------------------------------
    Prova p1(1, 1);

    Questao q1(
        "Limite Polinomial por Diferenca de Quadrados",
        1,
        50,
        "O numerador e uma diferenca de quadrados: x^2 - 9 = (x - 3)(x + 3). Fatore para cancelar o termo (x - 3).",
        15,
        "lim (x -> 3) [ (x^2 - 9) / (x - 3) ]"
    );

    Questao q2(
        "Limite com Racionalizacao de Raiz",
        2,
        75,
        "Multiplique numerador e denominador pela expressao conjugada (sqrt(t^2 + 9) + 3).",
        12,
        "lim (t -> 0) [ (sqrt(t^2 + 9) - 3) / t^2 ]"
    );

    p1.adicionarQuestao(q1);
    p1.adicionarQuestao(q2);
    semestre.adicionarProva(p1);

    // ----------------------------------------------------
    // PROVA 2: DERIVADAS E TAXAS RELACIONADAS (P2)
    // ----------------------------------------------------
    Prova p2(2, 2);

    Questao q3(
        "Derivacao com Regra da Cadeia",
        2,
        75,
        "Identifique a funcao externa u^4 e a interna u = 3x^2 - 5x + 2. Aplique d/dx[f(u)] = f'(u) * u'.",
        18,
        "f(x) = (3x^2 - 5x + 2)^4  -->  Encontre f'(x)"
    );

    Questao q4(
        "Derivacao com Regra do Quociente",
        1,
        50,
        "Quociente de duas funcoes lineares. Use a Regra do Quociente: (f/g)' = (g*f' - f*g') / g^2.",
        10,
        "g(x) = (3x - 1) / (2x + 1)  -->  Encontre g'(x)"
    );

    p2.adicionarQuestao(q3);
    p2.adicionarQuestao(q4);
    semestre.adicionarProva(p2);

    // ----------------------------------------------------
    // PROVA 3: INTEGRAIS E TECNICAS DE INTEGRACAO (P3)
    // ----------------------------------------------------
    Prova p3(3, 3);

    Questao q5(
        "Integracao por Partes Classica",
        3,
        100,
        "Use a regra de partes integral(u dv) = uv - integral(v du), escolhendo u = x e dv = sen(x)dx.",
        20,
        "integral [ x * sin(x) dx ]"
    );

    Questao q6(
        "Integral por Substituicao Simples",
        2,
        75,
        "Use a regra da substituicao escolhendo u = 1 + e^x, cuja diferencial e du = e^x dx.",
        15,
        "integral [ e^x * sqrt(1 + e^x) dx ]"
    );

    p3.adicionarQuestao(q5);
    p3.adicionarQuestao(q6);
    semestre.adicionarProva(p3);

    // ----------------------------------------------------
    // PROVA 4: EXAME FINAL GERAL (P4)
    // ----------------------------------------------------
    Prova p4(4, 3);

    Questao q7(
        "Limite Trigonometrico por L'Hopital",
        2,
        75,
        "Se apos derivar uma vez a indeterminacao continuar, aplique a Regra de L'Hopital novamente.",
        20,
        "lim (x -> 0) [ x^2 / (1 - cos(x)) ]"
    );

    Questao q8(
        "Decomposicao em Fracoes Parciais",
        3,
        100,
        "Fatore o denominador como (x - 1)(x + 1) e decomponha em A/(x - 1) + B/(x + 1).",
        20,
        "integral [ (5x - 1) / (x^2 - 1) dx ]"
    );

    p4.adicionarQuestao(q7);
    p4.adicionarQuestao(q8);
    semestre.adicionarProva(p4);
}

