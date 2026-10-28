#include "Jogador.hpp"
#include <iostream>

Jogador::Jogador(const std::string& nome, int cansaco, int danoBase)
    : _nome(nome), _cansaco(cansaco), _danoBase(danoBase) {
    if (_cansaco < 0) {
        _cansaco = 0;
    }
}

int Jogador::getCansaco() const {
    return _cansaco;
}

int Jogador::getDano() const {
    return _danoBase;
}

const std::vector<Habilidade>& Jogador::getHabilidades() const {
    return _habilidades;
}

const std::vector<Item>& Jogador::getItens() const {
    return _itens;
}

void Jogador::exibirHabilidades() const {
    std::cout << "--- Habilidades de " << _nome << " ---" << std::endl;
    for (const auto& hab : _habilidades) {
        hab.exibirDetalhes();
    }
}

void Jogador::exibirItens() const {
    std::cout << "--- Inventario de " << _nome << " ---" << std::endl;
    for (const auto& item : _itens) {
        std::cout << "- " << item.getNome() << " (x" << item.getQuantidade() << "): "
                  << item.getDescricao() << std::endl;
    }
}

void Jogador::alterarCansaco(int delta) {
    _cansaco += delta;
    if (_cansaco < 0) {
        _cansaco = 0;
    }
}

void Jogador::adicionarHabilidade(const Habilidade& habilidade) {
    _habilidades.push_back(habilidade);
}

void Jogador::adicionarItem(const Item& item) {
    // Verifica se o item já existe no inventário para apenas incrementar a quantidade
    for (auto& itemExistente : _itens) {
        if (itemExistente.getNome() == item.getNome()) {
            itemExistente.adicionarQuantidade(item.getQuantidade());
            return;
        }
    }
    _itens.push_back(item);
}

void Jogador::usarItem(size_t indice) {
    if (indice >= _itens.size()) {
        return;
    }

    // Tenta aplicar o efeito do item no próprio jogador
    bool usou = _itens[indice].usarEmJogador(this);
    if (usou) {
        // A remoção de decrementarQuantidade() aqui previne o duplo decréscimo
        if (_itens[indice].getQuantidade() <= 0) {
            _itens.erase(_itens.begin() + indice);
        }
    }
}