/**
 * @file Excecoes.hpp
 * @brief Definição da hierarquia de exceções personalizadas para o jogo.
 */

#ifndef EXCECOES_HPP
#define EXCECOES_HPP

#include <exception>
#include <string>

/**
 * @class ExcecaoJogo
 * @brief Classe base para todas as exceções do jogo.
 */
class ExcecaoJogo : public std::exception {
protected:
    std::string _mensagem;

public:
    explicit ExcecaoJogo(const std::string& mensagem) : _mensagem(mensagem) {}
    virtual ~ExcecaoJogo() noexcept = default;

    virtual const char* what() const noexcept override {
        return _mensagem.c_str();
    }
};

/**
 * @class ParametroInvalidoException
 * @brief Lançada quando um argumento ou parâmetro passado para uma função é inválido
 *        (ex: ponteiro nulo, valores negativos onde não permitido, intervalos incorretos).
 */
class ParametroInvalidoException : public ExcecaoJogo {
public:
    explicit ParametroInvalidoException(const std::string& mensagem = "Parametro fornecido e invalido!")
        : ExcecaoJogo("Erro de Parametro: " + mensagem) {}
};

/**
 * @class IndiceInvalidoException
 * @brief Lançada ao tentar acessar uma posição fora dos limites de um vetor
 *        (ex: item inexistente no inventário, prova inexistente no semestre).
 */
class IndiceInvalidoException : public ExcecaoJogo {
public:
    explicit IndiceInvalidoException(const std::string& mensagem = "Indice fora dos limites!")
        : ExcecaoJogo("Erro de Indice: " + mensagem) {}
};

/**
 * @class ItemEsgotadoException
 * @brief Lançada ao tentar utilizar um item cuja quantidade em estoque é zero ou insuficiente.
 */
class ItemEsgotadoException : public ExcecaoJogo {
public:
    explicit ItemEsgotadoException(const std::string& mensagem = "Item esgotado no inventario!")
        : ExcecaoJogo("Erro de Item: " + mensagem) {}
};

/**
 * @class QuestaoJaResolvidaException
 * @brief Lançada ao tentar aplicar danos ou ações em uma questão que já foi solucionada.
 */
class QuestaoJaResolvidaException : public ExcecaoJogo {
public:
    explicit QuestaoJaResolvidaException(const std::string& mensagem = "A questao ja foi resolvida!")
        : ExcecaoJogo("Erro de Questao: " + mensagem) {}
};

/**
 * @class CansacoExcedidoException
 * @brief Lançada quando o nível de cansaço do jogador ultrapassa o limite tolerável em combate.
 */
class CansacoExcedidoException : public ExcecaoJogo {
public:
    explicit CansacoExcedidoException(const std::string& mensagem = "O jogador atingiu o limite maximo de cansaco!")
        : ExcecaoJogo("Erro de Cansaco: " + mensagem) {}
};

/**
 * @class ArquivoNaoEncontradoException
 * @brief Lançada quando um recurso necessário (arquivo de dados, fonte, sprite) não é localizado.
 */
class ArquivoNaoEncontradoException : public ExcecaoJogo {
public:
    explicit ArquivoNaoEncontradoException(const std::string& mensagem = "Arquivo necessario nao encontrado!")
        : ExcecaoJogo("Erro de Arquivo: " + mensagem) {}
};

#endif // EXCECOES_HPP

