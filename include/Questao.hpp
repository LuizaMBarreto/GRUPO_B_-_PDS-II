/**
 * @file Questao.hpp
 * @brief Definição da classe Questao que atua como inimigo/desafio no jogo.
 */

#ifndef QUESTAO_HPP
#define QUESTAO_HPP

#include <string>
#include <vector>
#include "Habilidade.hpp"

class Jogador;

/**
 * @class Questao
 * @brief Classe que encapsula as propriedades e ações de uma questão matemática.
 */
class Questao {
private:
    std::string _assunto;               /**< Tema da questão (Limite, Derivada, Integral) */
    int _dificuldade;                   /**< Nível de dificuldade (1 a 3) */
    int _vidaResolucao;                 /**< "Pontos de vida"/dificuldade técnica restante */
    int _barraBonus;                    /**< Barra acumulativa de bônus de energia */
    bool _resolvida;                    /**< Status de resolução da questão */
    std::string _dica;                  /**< Texto contendo a dica de resolução */
    std::vector<Habilidade> _habilidadesInimigo; /**< Habilidades de ataque da questão */

public:
    /**
     * @brief Construtor da classe Questao.
     * @param assunto Assunto da questão.
     * @param dificuldade Dificuldade (1=Fácil, 2=Média, 3=Difícil).
     * @param vidaResolucao Quantidade de pontos necessários para ser resolvida.
     * @param dica Dica associada à resolução.
     */
    Questao(std::string assunto, int dificuldade, int vidaResolucao, std::string dica);

    /** @brief Destrutor padrão */
    virtual ~Questao() = default;

    /**
     * @brief Executa um ataque/ação automática da questão contra o jogador.
     * @param jogador Ponteiro para o jogador alvo.
     */
    void executarAcaoInimiga(Jogador* jogador);

    /**
     * @brief Aplica dano de resolução na questão.
     * @param dano Valor de dano/progresso aplicado.
     */
    void receberDanoResolucao(int dano);

    /**
     * @brief Incrementa a barra de bônus da questão.
     * @param pontos Quantidade de bônus acumulada.
     */
    void incrementarBonus(int pontos);

    /**
     * @brief Retorna o texto da dica associada à questão.
     * @return std::string com a dica.
     */
    std::string fornecerDica() const;

    // Getters
    std::string getAssunto() const;
    int getDificuldade() const;
    int getVidaResolucao() const;
    int getBarraBonus() const;
    bool isResolvida() const;
};

#endif // QUESTAO_HPP