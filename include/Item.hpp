/**
 * @file Item.hpp
 * @brief Definição da classe Item utilizada para consumíveis no jogo.
 */

#ifndef ITEM_HPP
#define ITEM_HPP

#include <string>

class Jogador;
class Questao;

/**
 * @class Item
 * @brief Classe que representa itens armazenados no inventário do jogador.
 */
class Item {
private:
    std::string _nome;        /**< Nome do item */
    std::string _descricao;   /**< Efeito detalhado do item */
    int _quantidade;          /**< Quantidade disponível no inventário */
    std::string _tipoEfeito;  /**< Tipo de efeito (ex: "CURA_ENERGIA", "DICA", "DANO") */

public:
    /**
     * @brief Construtor da classe Item.
     * @param nome Nome do item.
     * @param descricao Breve descrição do item.
     * @param quantidade Quantidade inicial no inventário.
     * @param tipoEfeito Identificador do efeito aplicado pelo item.
     */
    Item(std::string nome, std::string descricao, int quantidade, std::string tipoEfeito);

    /** @brief Destrutor padrão */
    virtual ~Item() = default;

    /**
     * @brief Aplica o efeito do item diretamente no jogador.
     * @param jogador Ponteiro para o jogador.
     * @return true se o item foi aplicado com sucesso, false caso contrário.
     */
    bool usarEmJogador(Jogador* jogador);

    /**
     * @brief Aplica o efeito do item sobre uma questão alvo (ex: revelando dica).
     * @param questao Ponteiro para a questão alvo.
     * @return true se acionado com sucesso, false caso contrário.
     */
    bool usarEmQuestao(Questao* questao);

    /**
     * @brief Incrementa a quantidade do item no inventário.
     * @param qtd Quantidade a ser adicionada.
     */
    void adicionarQuantidade(int qtd);

    /**
     * @brief Decrementa a quantidade do item no inventário após o uso.
     */
    void decrementarQuantidade();

    // Getters
    std::string getNome() const;
    std::string getDescricao() const;
    int getQuantidade() const;
    std::string getTipoEfeito() const;
};

#endif // ITEM_HPP