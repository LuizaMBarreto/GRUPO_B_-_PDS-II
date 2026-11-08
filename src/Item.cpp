#include "Item.hpp"
#include "Jogador.hpp"
#include "Questao.hpp"
#include "Excecoes.hpp"

Item::Item(std::string nome, std::string descricao, int quantidade, std::string tipoEfeito)
    : _nome(nome), _descricao(descricao), _quantidade(quantidade), _tipoEfeito(tipoEfeito) {
}

void Item::usarEmJogador(Jogador* jogador) {
    if (jogador == nullptr) {
        throw ParametroInvalidoException("Tentativa de usar item em jogador nulo (nullptr).");
    }
    if (_quantidade <= 0) {
        throw ItemEsgotadoException("Item '" + _nome + "' esta esgotado!");
    }
    
    if (_tipoEfeito == "CURA_ENERGIA") {
        jogador->alterarCansaco(-20);
    }
    decrementarQuantidade();
}

void Item::usarEmQuestao(Questao* questao) {
    if (questao == nullptr) {
        throw ParametroInvalidoException("Tentativa de usar item em questao nula (nullptr).");
    }
    if (_quantidade <= 0) {
        throw ItemEsgotadoException("Item '" + _nome + "' esta esgotado!");
    }
    
    decrementarQuantidade();
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