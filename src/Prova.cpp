#include "Prova.hpp"

// Stub TDD: implementacao minima para compilar. Comportamento real a ser implementado depois.
Prova::Prova() : questoes(), assunto(0), dificuldade(0) {}

Prova::Prova(int assunto, int dificuldade)
    : questoes(), assunto(assunto), dificuldade(dificuldade) {}

void Prova::adicionarQuestao(const Questao& questao) {
    questoes.push_back(questao);
}

int Prova::getAssunto() const {
    return assunto;
}

int Prova::getDificuldade() const {
    return dificuldade;
}

std::vector<Questao> Prova::getQuestoes() const {
    return questoes;
}
