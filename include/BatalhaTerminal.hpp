#ifndef BATALHA_TERMINAL_HPP
#define BATALHA_TERMINAL_HPP

#include "Jogador.hpp"
#include "Prova.hpp"
#include "Questao.hpp"
#include <iostream>

class BatalhaTerminal {
private:
    Jogador& _jogador;
    std::vector<Questao> _questoes;
    int _numeroProva;
    size_t _indiceQuestaoAtual;

public:
    BatalhaTerminal(Jogador& jogador, const Prova& prova, int numeroProva = 1);

    void exibirEstadoAtual(std::ostream& out = std::cout) const;
    void processarOpcao(int opcao, std::ostream& out = std::cout);
    void executarLoop(std::istream& in = std::cin, std::ostream& out = std::cout);

    const Questao& getQuestaoAtual() const;
    Questao& getQuestaoAtual();
    size_t getIndiceQuestaoAtual() const;
    int getNumeroProva() const;

    bool usarHabilidade(size_t indiceHabilidade, std::ostream& out = std::cout);
    bool usarItem(size_t indiceItem, std::ostream& out = std::cout);
    void executarContraAtaque(std::ostream& out = std::cout);
    bool avancarQuestao();
    bool isProvaConcluida() const;
};

#endif // BATALHA_TERMINAL_HPP
