#ifndef BATALHA_GUI_HPP
#define BATALHA_GUI_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Jogador.hpp"
#include "Questao.hpp"
#include "Prova.hpp"
#include "interface/Botao.hpp"

enum class ResultadoBatalha {
    EM_ANDAMENTO,
    VITORIA,
    DERROTA
};

enum class ModoBatalha {
    ACOES_PRINCIPAIS,
    SELECIONANDO_HABILIDADE,
    SELECIONANDO_ITEM
};

/**
 * @class BatalhaGUI
 * @brief Gerencia a tela de batalha por turnos com navegação 100% via teclado (WASD/Enter).
 *        Permite selecionar habilidades matemáticas reais do jogador e usar itens de inventário.
 */
class BatalhaGUI {
private:
    const sf::Font& _fonte;
    Jogador& _jogador;
    std::vector<Questao> _questoes;
    size_t _indiceQuestaoAtual;
    Questao _questao;
    ResultadoBatalha _resultado;
    ModoBatalha _modo;
    int _numeroProva;

    // Componentes visuais
    sf::RectangleShape _fundo;
    sf::RectangleShape _caixaQuestao;
    sf::RectangleShape _caixaDialogo;

    // Submenu de Habilidades / Itens
    sf::RectangleShape _painelSubmenu;
    sf::Text _tituloSubmenu;
    std::vector<sf::Text> _textosSubmenu;
    int _indiceSubmenuSelecionado;

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
    sf::Text _textoMensagemLog3;
    sf::Text _textoInstrucaoTeclado;

    // Botões de Ações Principais
    std::vector<Botao> _botoesAcao;
    int _indiceAcaoSelecionada;

    int _vidaInicial;
    bool _batalhaConcluida;
    bool _aguardandoAvancoQuestao;
    bool _aguardandoEncerramentoBatalha;

    void atualizarBarras();
    void atualizarEnunciado();
    void atualizarSubmenu();
    void executarTurnoInimigo();
    void avancarParaProximaQuestao();

public:
    // Construtor principal para Prova inteira
    BatalhaGUI(float larguraJanela, float alturaJanela, const sf::Font& fonte,
               Jogador& jogador, const Prova& prova, int numeroProva = 1);

    // Construtor de compatibilidade para Questão única
    BatalhaGUI(float larguraJanela, float alturaJanela, const sf::Font& fonte,
               Jogador& jogador, const Questao& questao);

    void processarEventos(const sf::Event& evento);
    void atualizar();
    void renderizar(sf::RenderWindow& janela);

    bool isBatalhaConcluida() const;
    ResultadoBatalha getResultado() const;
};

#endif // BATALHA_GUI_HPP
