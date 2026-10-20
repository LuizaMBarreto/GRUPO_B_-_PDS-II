#include "Prova.hpp"

// Stub TDD: implementacao minima para compilar. Comportamento real a ser implementado depois.
Prova::Prova() : questoes(), assunto(0), dificuldade(0) {}

int Prova::getAssunto() const {
    return assunto;
}

int Prova::getDificuldade() const {
    return dificuldade;
}

std::vector<Questao> Prova::getQuestoes() const {
    return questoes;
}
