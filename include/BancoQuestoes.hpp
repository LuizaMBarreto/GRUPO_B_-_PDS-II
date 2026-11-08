/**
 * @file BancoQuestoes.hpp
 * @brief Gerenciador de inicialização das Provas de Cálculo I e Habilidades do Jogador.
 */

#ifndef BANCO_QUESTOES_HPP
#define BANCO_QUESTOES_HPP

#include "Semestre.hpp"
#include "Jogador.hpp"
#include <string>

/**
 * @class BancoQuestoes
 * @brief Popula o Semestre com as 4 Provas temáticas (Stewart) e fornece as habilidades do Estudante.
 */
class BancoQuestoes {
public:
    /**
     * @brief Cria uma instância inicial do Jogador com atributos e habilidades de Cálculo I.
     * @param nome Nome do estudante.
     * @return Jogador pronto para iniciar o semestre.
     */
    static Jogador criarJogadorInicial(const std::string& nome = "Carlos");

    /**
     * @brief Carrega as 4 Provas do semestre (P1, P2, P3, P4) completas no Semestre.
     * @param semestre Referência ao Semestre onde as provas serão inseridas.
     */
    static void carregarProvasNoSemestre(Semestre& semestre);
};

#endif // BANCO_QUESTOES_HPP

