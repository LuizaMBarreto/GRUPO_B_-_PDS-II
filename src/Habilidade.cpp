#include "Habilidade.hpp"
#include "Jogador.hpp"
#include "Questao.hpp"
#include <iostream>

Habilidade::Habilidade(const std::string& nome, const std::string& descricao, int efeitoValor, bool afetaInimigo)
    : _nome(nome), _descricao(descricao), _efeitoValor(efeitoValor), _afetaInimigo(afetaInimigo) {}

std::string Habilidade::getNome() const {
    return _nome;
}

std::string Habilidade::getDescricao() const {
    return _descricao;
}

int Habilidade::getEfeitoValor() const {
    return _efeitoValor;
}

bool Habilidade::afetaInimigo() const {
    return _afetaInimigo;
}

void Habilidade::aplicarEfeito(Jogador& alvo) const {
    if (!_afetaInimigo) {
        // Habilidade de suporte: reduz o cansaço do jogador de acordo com o valor do efeito
        alvo.alterarCansaco(-_efeitoValor);
    }
}

void Habilidade::aplicarEfeito(Questao& alvo) const {
    if (_afetaInimigo) {
        // Habilidade ofensiva: causa dano de resolução na questão
        alvo.receberDanoResolucao(_efeitoValor);
    }
}

void Habilidade::exibirDetalhes() const {
    std::cout << "Habilidade: " << _nome << " | Efeito: " << _descricao
              << " | Valor: " << _efeitoValor
              << " | Alvo: " << (_afetaInimigo ? "Inimigo" : "Jogador") << std::endl;
}

