#pragma once

#include <string>

class Jogador;

/**
 * @file Habilidade.hpp
 * @brief Definição da classe Habilidade e das suas propriedades de efeito.
 */

/**
 * @class Habilidade
 * @brief Representa uma habilidade especial que pode ser aplicada no jogador ou em inimigos.
 */
class Habilidade {
private:
    std::string _nome;
    std::string _descricao;
    int _efeitoValor;
    bool _afetaInimigo; // true se afeta o inimigo, false se afeta o próprio jogador

public:
    /**
     * @brief Construtor da classe Habilidade.
     * @param nome Nome da habilidade.
     * @param descricao Descrição detalhada do efeito.
     * @param efeitoValor Valor numérico do impacto (ex: dano extra, redução de cansaço).
     * @param afetaInimigo Indica se o alvo principal é o inimigo.
     */
    Habilidade(const std::string& nome, const std::string& descricao, int efeitoValor, bool afetaInimigo = true);

    /**
     * @brief Destrutor virtual padrão.
     */
    virtual ~Habilidade() = default;

    // --- Getters ---

    /**
     * @brief Obtém o nome da habilidade.
     * @return Nome da habilidade.
     */
    std::string getNome() const;

    /**
     * @brief Obtém a descrição do efeito da habilidade.
     * @return Texto descritivo da habilidade.
     */
    std::string getDescricao() const;

    /**
     * @brief Obtém o valor do efeito numérico da habilidade.
     * @return Valor do efeito.
     */
    int getEfeitoValor() const;

    /**
     * @brief Verifica se a habilidade é direcionada a inimigos.
     * @return true se afetar inimigos, false se afetar o jogador.
     */
    bool afetaInimigo() const;

    // --- Métodos de Comportamento ---

    /**
     * @brief Aplica o efeito da habilidade no alvo (Jogador ou Inimigo).
     * @param alvo Referência ao Jogador afetado ou utilizador.
     */
    void aplicarEfeito(Jogador& alvo) const;

    /**
     * @brief Exibe as informações e efeitos da habilidade no console/terminal.
     */
    void exibirDetalhes() const;
};