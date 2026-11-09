#include "Prova.hpp"
#include "Excecoes.hpp"

// Stub TDD: implementacao minima para compilar. Comportamento real a ser implementado depois.
Prova::Prova() : questoes(), assunto(0), dificuldade(0) {}

Prova::Prova(int assunto, int dificuldade)
    : questoes(), assunto(assunto), dificuldade(dificuldade) {}

void Prova::adicionarQuestao(const Questao& questao) {
    if (questao.isResolvida() || questao.getVidaResolucao() <= 0) {
        throw ParametroInvalidoException("Nao e possivel adicionar a prova uma questao ja resolvida.");
    }
    questoes.push_back(questao);
}

int Prova::getAssunto() const {
    return assunto;
}

int Prova::getDificuldade() const {
    return dificuldade;
}

const std::vector<Questao>& Prova::getQuestoes() const {
    return questoes;
}

const Questao& Prova::getQuestao(std::size_t indice) const {
    if (indice >= questoes.size()) {
        throw IndiceInvalidoException("Indice de questao invalido na prova.");
    }
    return questoes[indice];
}
