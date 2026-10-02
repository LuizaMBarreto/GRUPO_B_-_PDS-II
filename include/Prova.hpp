
#ifndef PROVA_HPP
#define PROVA_HPP
#include <vector>
#include "Questao.hpp"

/**
* @file Prova.hpp
* @brief Resumo da classe prova, seus  atributos e suas habilidades
*/


/**
* @class Prova
@brief definição da prova no jogo, contendo de forma quase aninhada questões, nivel de dificuldade e assunto da prova
  */

class Prova{

  private:
std::vector <Questao> questoes; ///< lista de questoes contida na prova
int assunto; /** @note nao tenho certeza quanto a assunto ser representado por um inteiro
*/
int dificuldade; ///< nivel de dificuldade da prova (usualmente definida pela distinção de provas)



  public:
/**
*@brief Construtor da classe Prova
* 

  */
Prova();
/**
 * @brief obtem o valor associdado ao assunto da prova
 * @return retorma o valor associado ao tipo da prova
*/
int getAssunto() const;

/**
* @brief obtém o nível de dificuldade da prova.
* @return nivel de dificuldade (inteiro por enquanto).
*/

int getDificuldade() const;

/**
* @brief obtem a lista de questoes pertencentes a essa prova.
* @return vetor que contém as questoes.
*/
std::vector <Questao> getQuestoes() const;


};

#endif // prova_hpp
