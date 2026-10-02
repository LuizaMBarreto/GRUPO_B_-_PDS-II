/**
 * @file Semestre.hpp
 * @brief Definição da classe Semestre que controla o fluxo geral do jogo e combates.
 */

#ifndef SEMESTRE_HPP
#define SEMESTRE_HPP

#include <vector>
#include <string>
#include "Prova.hpp"
#include "Jogador.hpp"

/**
 * @class Semestre
 * @brief Gerenciador principal do fluxo do jogo, fila de turnos e progrssão de provas.
 */
class Semestre {
private:
    int _pontuacaoAcumulada;          /**< Soma das pontuações obtidas nas provas */
    size_t _indiceProvaAtual;         /**< Índice da prova atualmente em andamento */
    std::vector<Prova> _provas;       /**< Lista de todas as 4 provas do semestre */
    Jogador _jogador;                 /**< Instância do jogador participante */

public:
    /**
     * @brief Construtor do Semestre.
     * @param jogador Instância do jogador que jogará o semestre.
     */
    explicit Semestre(const Jogador& jogador);

    /** @brief Destrutor padrão */
    virtual ~Semestre() = default;

    /**
     * @brief Adiciona uma nova prova à grade do semestre.
     * @param prova Instância da prova a ser incluída.
     */
    void adicionarProva(const Prova& prova);

    /**
     * @brief Inicia e gerencia a fila de turnos da prova atual.
     */
    void gerenciarFilaDeTurnos();

    /**
     * @brief Permite ao jogador explorar a sala para obter novos itens entre as provas.
     */
    void explorarSala();

    /**
     * @brief Atualiza a pontuação total somando o resultado da prova finalizada.
     * @param pontos Pontos obtidos na última prova.
     */
    void somarPontuacao(int pontos);

    /**
     * @brief Verifica as condições de término do combate (derrota por cansaço ou vitória).
     * @return true se a prova/combate atual deve terminar.
     */
    bool verificarFimDeCombate();

    // Getters
    int getPontuacaoAcumulada() const;
    size_t getIndiceProvaAtual() const;
    const Prova& getProvaAtual() const;
    const Jogador& getJogador() const;
};

#endif // SEMESTRE_HPP