#include "interface/JogoGUI.hpp"
#include <iostream>

JogoGUI::JogoGUI(unsigned int largura, unsigned int altura)
    : _janela(sf::VideoMode(largura, altura), "Derrote Calculo I", sf::Style::Titlebar | sf::Style::Close),
      _estadoAtual(EstadoJogo::MENU_INICIAL) {

    _janela.setFramerateLimit(60);

    carregarFonte();

    _menuInicial = std::unique_ptr<MenuInicial>(new MenuInicial(largura, altura, _fonte));
    _mapaExploracao = std::unique_ptr<MapaExploracao>(new MapaExploracao(largura, altura, _fonte));

    iniciarNovoJogo();
}

void JogoGUI::carregarFonte() {
    if (!_fonte.loadFromFile("assets/fonts/default.ttf")) {
        if (!_fonte.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
            std::cerr << "[AVISO] Nao foi possivel carregar a fonte padrao!" << std::endl;
        }
    }
}

void JogoGUI::iniciarNovoJogo() {
    _jogador = std::unique_ptr<Jogador>(new Jogador("Carlos", 0, 10));
    _semestre = std::unique_ptr<Semestre>(new Semestre(*_jogador));
    if (_mapaExploracao) {
        _mapaExploracao->resetarPosicaoJogador();
    }
}

void JogoGUI::iniciarBatalha() {
    // Carrega a primeira questão da Prova 1 (Limite com fatoração)
    Questao q("Limite por Fatoracao", 1, 50, "Fatore o numerador usando diferenca de quadrados: (x-3)(x+3)", 15);
    _batalhaGUI = std::unique_ptr<BatalhaGUI>(new BatalhaGUI(1000, 700, _fonte, *_jogador, q));
    _estadoAtual = EstadoJogo::BATALHA;
}

void JogoGUI::executar() {
    sf::Clock relogio;

    while (_janela.isOpen()) {
        float dt = relogio.restart().asSeconds();

        processarEventos();
        atualizar(dt);
        renderizar();
    }
}

void JogoGUI::processarEventos() {
    sf::Event evento;

    while (_janela.pollEvent(evento)) {
        if (evento.type == sf::Event::Closed) {
            _janela.close();
            return;
        }

        if (_estadoAtual == EstadoJogo::MENU_INICIAL) {
            AcaoMenu acao = _menuInicial->processarEventos(evento);
            if (acao == AcaoMenu::NOVO_JOGO) {
                iniciarNovoJogo();
                _estadoAtual = EstadoJogo::EXPLORACAO;
            } else if (acao == AcaoMenu::CARREGAR_JOGO) {
                std::cout << "[JogoGUI] Carregar jogo selecionado." << std::endl;
            } else if (acao == AcaoMenu::SAIR) {
                _janela.close();
            }
        } else if (_estadoAtual == EstadoJogo::EXPLORACAO) {
            _mapaExploracao->processarEventos(evento, *_jogador);

            if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
                _estadoAtual = EstadoJogo::MENU_INICIAL;
            }

            if (_mapaExploracao->deveIniciarBatalha()) {
                _mapaExploracao->resetarSinalBatalha();
                iniciarBatalha();
            }
        } else if (_estadoAtual == EstadoJogo::BATALHA) {
            if (_batalhaGUI) {
                _batalhaGUI->processarEventos(evento);

                if (_batalhaGUI->isBatalhaConcluida()) {
                    if (evento.type == sf::Event::KeyPressed &&
                       (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space)) {
                        _estadoAtual = EstadoJogo::EXPLORACAO;
                        _batalhaGUI.reset();
                    }
                }

                if (evento.type == sf::Event::KeyPressed && evento.key.code == sf::Keyboard::Escape) {
                    _estadoAtual = EstadoJogo::EXPLORACAO;
                    _batalhaGUI.reset();
                }
            }
        }
    }
}

void JogoGUI::atualizar(float dt) {
    if (_estadoAtual == EstadoJogo::MENU_INICIAL) {
        _menuInicial->atualizar();
    } else if (_estadoAtual == EstadoJogo::EXPLORACAO) {
        _mapaExploracao->atualizar(dt);
        if (_mapaExploracao->deveIniciarBatalha()) {
            _mapaExploracao->resetarSinalBatalha();
            iniciarBatalha();
        }
    } else if (_estadoAtual == EstadoJogo::BATALHA) {
        if (_batalhaGUI) {
            _batalhaGUI->atualizar();
        }
    }
}

void JogoGUI::renderizar() {
    _janela.clear(sf::Color(15, 18, 28));

    if (_estadoAtual == EstadoJogo::MENU_INICIAL) {
        _menuInicial->renderizar(_janela);
    } else if (_estadoAtual == EstadoJogo::EXPLORACAO) {
        _mapaExploracao->renderizar(_janela);
    } else if (_estadoAtual == EstadoJogo::BATALHA) {
        if (_batalhaGUI) {
            _batalhaGUI->renderizar(_janela);
        }
    }

    _janela.display();
}
