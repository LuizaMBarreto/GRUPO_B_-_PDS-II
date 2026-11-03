#ifndef BATALHA_GUI_HPP
#define BATALHA_GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Jogador.hpp"
#include "Questao.hpp"
#include "interface/Botao.hpp"

enum class ResultadoBatalha {
    EM_ANDAMENTO,
    VITORIA,
    DERROTA
};

/**
 * @class BatalhaGUI
 * @brief Gerencia a tela de batalha por turnos com navegação 100% via teclado (WASD/Enter).
 */
class BatalhaGUI {
private:
    const sf::Font& _fonte;
    Jogador& _jogador;
    Questao _questao;
    ResultadoBatalha _resultado;

    // Componentes visuais
    sf::RectangleShape _fundo;
    sf::RectangleShape _caixaQuestao;
    sf::RectangleShape _caixaDialogo;

    // Barras de status
    sf::RectangleShape _barraVidaFundo;
    sf::RectangleShape _barraVidaAtual;
    sf::RectangleShape _barraCansacoFundo;
    sf::RectangleShape _barraCansacoAtual;

    // Textos do HUD
    sf::Text _textoEnunciado;
    sf::Text _textoVida;
    sf::Text _textoCansaco;
    sf::Text _textoMensagemLog1;
    sf::Text _textoMensagemLog2;
    sf::Text _textoInstrucaoTeclado;

    // Botões de Ações (A/D ou W/S para navegar, Enter/Espaço para usar)
    std::vector<Botao> _botoesAcao;
    int _indiceAcaoSelecionada;

    int _vidaInicial;
    bool _batalhaConcluida;

    void atualizarBarras();
    void executarTurnoInimigo();

public:
    BatalhaGUI(float larguraJanela, float alturaJanela, const sf::Font& fonte,
               Jogador& jogador, const Questao& questao);

    void processarEventos(const sf::Event& evento);
    void atualizar();
    void renderizar(sf::RenderWindow& janela);

    bool isBatalhaConcluida() const;
    ResultadoBatalha getResultado() const;
};

#endif // BATALHA_GUI_HPP

