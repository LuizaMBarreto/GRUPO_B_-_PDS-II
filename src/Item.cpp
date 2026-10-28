#include "Item.hpp"
#include "Jogador.hpp"
#include "Questao.hpp"

Item::Item(std::string nome, std::string descricao, int quantidade, std::string tipoEfeito)
    : _nome(nome), _descricao(descricao), _quantidade(quantidade), _tipoEfeito(tipoEfeito) {
}

bool Item::usarEmJogador(Jogador* jogador) {
    // Nao e possivel usar o item sem um alvo ou sem unidades disponiveis
    if (jogador == nullptr || _quantidade <= 0) {
        return false;
    }
    
    // O efeito sobre o jogador sera implementado conforme o tipo do item posteriormente
    
    decrementarQuantidade();
    return true;
}

bool Item::usarEmQuestao(Questao* questao) {
    // Nao e possivel usar o item sem um alvo ou sem unidades disponiveis
    if (questao == nullptr || _quantidade <= 0) {
        return false;
    }
    // O efeito sobre a questao sera implementado conforme o tipo do item posteriormente
    
    decrementarQuantidade();
    return true;
}

void Item::adicionarQuantidade(int qtd) {
    _quantidade += qtd;
}

void Item::decrementarQuantidade() {
    // Impede que a quantidade fique negativa
    if (_quantidade > 0) {
        _quantidade--;
    }
}

std::string Item::getNome() const {
    return _nome;
}

std::string Item::getDescricao() const {
    return _descricao;
}

int Item::getQuantidade() const {
    return _quantidade;
}

std::string Item::getTipoEfeito() const {
    return _tipoEfeito;
}