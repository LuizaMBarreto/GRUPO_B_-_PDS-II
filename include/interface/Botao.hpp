#ifndef BOTAO_HPP
#define BOTAO_HPP

#include <SFML/Graphics.hpp>
#include <string>

/**
 * @class Botao
 * @brief Componente de botão interativo para menus e batalhas com SFML.
 */
class Botao {
private:
    sf::RectangleShape _forma;
    sf::Text _texto;
    sf::Color _corNormal;
    sf::Color _corHover;
    sf::Color _corAtivo;
    bool _isHover;
    bool _selecionado;

public:
    Botao(float x, float y, float largura, float altura, 
          const std::string& texto, const sf::Font& fonte, 
          unsigned int tamanhoFonte = 22);

    void setSelecionado(bool selecionado);
    bool isSelecionado() const;

    void atualizar(const sf::Vector2f& posicaoMouse);
    bool foiClicado(const sf::Vector2f& posicaoMouse, const sf::Event& evento);
    void renderizar(sf::RenderWindow& janela);

    void setPosicao(float x, float y);
    void setTexto(const std::string& texto);
    void setCores(sf::Color normal, sf::Color hover, sf::Color ativo);
};

#endif // BOTAO_HPP

