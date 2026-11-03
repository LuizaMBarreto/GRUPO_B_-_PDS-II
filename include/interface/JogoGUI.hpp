#ifndef JOGO_GUI_HPP
#define JOGO_GUI_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include "interface/MenuInicial.hpp"
#include "interface/MapaExploracao.hpp"
#include "interface/BatalhaGUI.hpp"
#include "Jogador.hpp"
#include "Semestre.hpp"

enum class EstadoJogo {
    MENU_INICIAL,
    EXPLORACAO,
    BATALHA,
    GAME_OVER,
    VITORIA
};

/**
 * @class JogoGUI
 * @brief Gerenciador central da interface gráfica e da máquina de estados do jogo.
 */
class JogoGUI {
private:
    sf::RenderWindow _janela;
    sf::Font _fonte;
    EstadoJogo _estadoAtual;

    std::unique_ptr<MenuInicial> _menuInicial;
    std::unique_ptr<MapaExploracao> _mapaExploracao;
    std::unique_ptr<BatalhaGUI> _batalhaGUI;
    std::unique_ptr<Jogador> _jogador;
    std::unique_ptr<Semestre> _semestre;

    void carregarFonte();
    void iniciarNovoJogo();
    void iniciarBatalha();

public:
    JogoGUI(unsigned int largura = 1000, unsigned int altura = 700);

    void executar();
    void processarEventos();
    void atualizar(float dt);
    void renderizar();
};

#endif // JOGO_GUI_HPP

