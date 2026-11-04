#include "Semestre.hpp"
#include "Excecoes.hpp"


Semestre::Semestre(const Jogador& jogador)
    : _pontuacaoAcumulada(0), _indiceProvaAtual(0), _provas(), _jogador(jogador) {}

void Semestre::adicionarProva(const Prova& prova) {
   _provas.push_back(prova);
}

void Semestre::gerenciarFilaDeTurnos() {
  
}

void Semestre::explorarSala() {
}

void Semestre::somarPontuacao(int pontos) {
    if (pontos < 0) {
        throw ParametroInvalidoException("Pontuacao negativa nao e permitida");
    }
     _pontuacaoAcumulada += pontos;
}

bool Semestre::verificarFimDeCombate() {
    const int LIMITE_CANSACO = 100;   
    return _jogador.getCansaco() >= LIMITE_CANSACO;
}

int Semestre::getPontuacaoAcumulada() const {
    return _pontuacaoAcumulada;
}

size_t Semestre::getIndiceProvaAtual() const {
    return _indiceProvaAtual;
}

const Prova& Semestre::getProvaAtual() const {
    if (_provas.empty()) {
        throw IndiceInvalidoException("Nao ha provas cadastradas no semestre");
    }
    if (_indiceProvaAtual >= _provas.size()) {
        throw IndiceInvalidoException("Indice da prova atual fora dos limites");
    }
    return _provas[_indiceProvaAtual];
}

const Jogador& Semestre::getJogador() const {
    return _jogador;
}
