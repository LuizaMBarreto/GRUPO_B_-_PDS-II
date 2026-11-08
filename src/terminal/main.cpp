#include "BancoQuestoes.hpp"
#include "BatalhaTerminal.hpp"
#include <iostream>

int main() {
    std::cout << "========================================\n";
    std::cout << "   MODO TERMINAL: BATALHA DE CALCULO I   \n";
    std::cout << "========================================\n";

    Jogador jogador = BancoQuestoes::criarJogadorInicial("Carlos");
    Semestre semestre(jogador);
    BancoQuestoes::carregarProvasNoSemestre(semestre);

    const Prova& p1 = semestre.getProvaAtual();
    BatalhaTerminal batalha(jogador, p1, 1);

    batalha.executarLoop(std::cin, std::cout);

    std::cout << "\nSaindo do modo de demonstracao no terminal.\n";
    return 0;
}
