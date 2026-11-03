#ifndef MENU_INICIAL_HPP
#define MENU_INICIAL_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include "interface/Botao.hpp"

enum class AcaoMenu {
    NENHUMA,
    NOVO_JOGO,
    CARREGAR_JOGO,
    SAIR
};

/**
 * @class MenuInicial
 * @brief Tela inicial do jogo com opções de Novo Jogo, Carregar e Sair.
 */
class MenuInicial {
private:
    const sf::Font& _fonte;
    sf::Text _titulo;
    sf::Text _subtitulo;
    sf::Text _rodape;
    std::vector<Botao> _botoes;
    sf::RectangleShape _fundo;
    int _indiceSelecionado;

public:
    MenuInicial(float larguraJanela, float alturaJanela, const sf::Font& fonte);

    AcaoMenu processarEventos(const sf::Event& evento);
    void atualizar();
    void renderizar(sf::RenderWindow& janela);
};

#endif // MENU_INICIAL_HPP

