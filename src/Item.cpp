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
    
    // Efeito coerente aplicado sobre o jogador
    if (_tipoEfeito == "CURA_ENERGIA") {
        jogador->alterarCansaco(-20); 
    }
    
    decrementarQuantidade();
    return true;
}

bool Item::usarEmQuestao(Questao* questao) {
    if (questao == nullptr || _quantidade <= 0) {
        return false;
    }
    
    decrementarQuantidade();
    return true;
}

void Item::adicionarQuantidade(int qtd) {
    _quantidade += qtd;
}

void Item::decrementarQuantidade() {
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