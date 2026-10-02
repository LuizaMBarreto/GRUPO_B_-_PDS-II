#pragma once

#include <string>
#include <vector>
#include "Habilidade.hpp"
#include "Item.hpp"

/**
 * @file Jogador.hpp
 * @brief Definição da classe Jogador e gerenciamento de seus atributos e ações.
 */

/**
 * @class Jogador
 * @brief Representa o jogador no sistema, contendo estatísticas de combate/jogo,
 *        inventário de itens e habilidades disponíveis.
 */
class Jogador {
private:
    std::string _nome;
    int _cansaco;
    int _danoBase;
    std::vector<Habilidade> _habilidades;
    std::vector<Item> _itens;

public:
    /**
     * @brief Construtor da classe Jogador.
     * @param nome Nome do jogador.
     * @param cansaco Nível inicial de cansaço.
     * @param danoBase Dano base inicial do jogador.
     */
    Jogador(const std::string& nome, int cansaco = 0, int danoBase = 10);

    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~Jogador() = default;

    // --- Getters e Métodos de Informação ---

    /**
     * @brief Obtém o nível atual de cansaço do jogador.
     * @return Valor do cansaço.
     */
    int getCansaco() const;

    /**
     * @brief Obtém o dano base do jogador.
     * @return Valor do dano base.
     */
    int getDano() const;

    /**
     * @brief Retorna a lista de habilidades do jogador.
     * @return Vetor de referências constantes para as habilidades.
     */
    const std::vector<Habilidade>& getHabilidades() const;

    /**
     * @brief Retorna o inventário de itens que o jogador carrega.
     * @return Vetor de referências constantes para os itens.
     */
    const std::vector<Item>& getItens() const;

    /**
     * @brief Exibe no console/terminal as habilidades do jogador e seus respectivos efeitos.
     */
    void exibirHabilidades() const;

    /**
     * @brief Exibe no console/terminal os itens do inventário e seus respectivos efeitos.
     */
    void exibirItens() const;

    // --- Métodos de Alteração e Comportamento ---

    /**
     * @brief Altera ou adiciona pontos de cansaço ao jogador.
     * @param delta Valor a ser somado (ou subtraído, se negativo) ao cansaço.
     */
    void alterarCansaco(int delta);

    /**
     * @brief Adiciona uma nova habilidade ao jogador.
     * @param habilidade Objeto da classe Habilidade a ser adicionado.
     */
    void adicionarHabilidade(const Habilidade& habilidade);

    /**
     * @brief Adiciona um novo item ao inventário do jogador.
     * @param item Objeto da classe Item a ser adicionado.
     */
    void adicionarItem(const Item& item);

    /**
     * @brief Usa um item do inventário pelo seu índice.
     * @param indice Índice do item no inventário.
     */
    void usarItem(size_t indice);
};