#ifndef MAPA_EXPLORACAO_HPP
#define MAPA_EXPLORACAO_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Jogador.hpp"

enum class TipoAmbiente {
    CORREDOR,
    SALA_DE_AULA
};

struct ItemNoMapa {
    std::string nome;
    sf::Vector2f posicao;
    bool coletado;
    sf::RectangleShape forma;
    TipoAmbiente ambiente;
};

/**
 * @class MapaExploracao
 * @brief Gerencia a movimentação no mapa 2D, transições de ambiente (Corredor <-> Sala),
 *        câmera que segue o jogador e controles via teclado (WASD/Enter).
 */
class MapaExploracao {
private:
    const sf::Font& _fonte;
    TipoAmbiente _ambienteAtual;

    // Jogador no mapa
    sf::RectangleShape _spriteJogador;
    sf::Vector2f _posicaoJogador;
    float _velocidadeJogador;

    // Câmera dinâmica
    sf::View _camera;

    // Textura opcional do chão
    sf::Texture _texturaChao;
    bool _temTexturaChao;

    // Paredes e colisões ativas do ambiente atual
    std::vector<sf::FloatRect> _paredes;

    // Elementos do Corredor
    sf::RectangleShape _chaoCorredor;
    sf::RectangleShape _portaEntradaSala;
    sf::Text _placaCorredor;

    // Elementos da Sala de Aula
    sf::RectangleShape _chaoSala;
    sf::RectangleShape _lousa;
    sf::Text _textoLousa;
    std::vector<sf::RectangleShape> _carteiras;
    sf::RectangleShape _mesaProfessor;
    sf::Text _placaProva;
    sf::RectangleShape _portaSaidaSala;
    sf::Text _placaSaida;

    // Itens no chão
    std::vector<ItemNoMapa> _itensNoChao;

    // Textos e HUD do mapa
    sf::Text _textoInteracao;
    sf::Text _textoStatus;
    sf::Text _textoMensagem;
    float _tempoMensagem;

    bool _solicitouBatalha;

    void carregarTexturas();
    void configurarCorredor();
    void configurarSalaDeAula();
    void trocarAmbiente(TipoAmbiente novo);
    void adicionarItens();
    bool verificarColisao(const sf::FloatRect& novaCaixa) const;

public:
    MapaExploracao(float larguraJanela, float alturaJanela, const sf::Font& fonte);

    void processarEventos(const sf::Event& evento, Jogador& jogador);
    void atualizar(float dt);
    void renderizar(sf::RenderWindow& janela);

    bool deveIniciarBatalha();
    void resetarSinalBatalha();
    void resetarPosicaoJogador();
    TipoAmbiente getAmbienteAtual() const;
};

#endif // MAPA_EXPLORACAO_HPP
