#include "Semestre.hpp"


Semestre::Semestre(const Jogador& jogador)
    : _pontuacaoAcumulada(0), _indiceProvaAtual(0), _provas(), _jogador(jogador) {}

void Semestre::adicionarProva(const Prova& prova) {
    (void)prova;
}

void Semestre::gerenciarFilaDeTurnos() {
}

void Semestre::explorarSala() {
}

void Semestre::somarPontuacao(int pontos) {
    (void)pontos;
}

bool Semestre::verificarFimDeCombate() {
    return false;
}

int Semestre::getPontuacaoAcumulada() const {
    return _pontuacaoAcumulada;
}

size_t Semestre::getIndiceProvaAtual() const {
    return _indiceProvaAtual;
}

const Prova& Semestre::getProvaAtual() const {
    static const Prova provaVazia;
    return provaVazia;
}

const Jogador& Semestre::getJogador() const {
    return _jogador;
}
