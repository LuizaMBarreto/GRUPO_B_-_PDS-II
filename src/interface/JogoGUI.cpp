#include "interface/JogoGUI.hpp"
#include "BancoQuestoes.hpp"
#include <iostream>
#include <exception>

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
  if (_fonte.loadFromFile("assets/fonts/default.ttf")) return;
    if (_fonte.loadFromFile("C:/Windows/Fonts/arial.ttf")) return;
    if (_fonte.loadFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) return;
    std::cerr << "[AVISO] Nao foi possivel carregar nenhuma fonte!" << std::endl;

}

void JogoGUI::iniciarNovoJogo() {
    _jogador = std::unique_ptr<Jogador>(new Jogador(BancoQuestoes::criarJogadorInicial("Carlos")));
    _semestre = std::unique_ptr<Semestre>(new Semestre(*_jogador));
    BancoQuestoes::carregarProvasNoSemestre(*_semestre);

    if (_mapaExploracao) {
        _mapaExploracao->resetarPosicaoJogador();
        _mapaExploracao->setProvaAtual(1);
    }
}

void JogoGUI::iniciarBatalha() {
    if (!_semestre || !_jogador) return;

    int numProva = (int)_semestre->getIndiceProvaAtual() + 1;
    const Prova& provaAtual = _semestre->getProvaAtual();

    _batalhaGUI = std::unique_ptr<BatalhaGUI>(new BatalhaGUI(
        _janela.getSize().x, _janela.getSize().y, _fonte, *_jogador, provaAtual, numProva
    ));
    _estadoAtual = EstadoJogo::BATALHA;
}

void JogoGUI::executar() {
    sf::Clock relogio;

    while (_janela.isOpen()) {
        float dt = relogio.restart().asSeconds();

        try {
            processarEventos();
            atualizar(dt);
            renderizar();
        } catch (const std::exception& e) {
            std::cerr << "[ERRO] " << e.what() << std::endl;
        }
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

                        if (_batalhaGUI->getResultado() == ResultadoBatalha::VITORIA) {
                            _semestre->somarPontuacao(25);
                            if (_semestre->temProximaProva()) {
                                _semestre->gerenciarFilaDeTurnos();
                                _mapaExploracao->setProvaAtual((int)_semestre->getIndiceProvaAtual() + 1);
                                _estadoAtual = EstadoJogo::EXPLORACAO;
                            } else {
                                // Finalizou todas as 4 provas do semestre!
                                _estadoAtual = EstadoJogo::VITORIA;
                            }
                        } else if (_batalhaGUI->getResultado() == ResultadoBatalha::DERROTA) {
                            _estadoAtual = EstadoJogo::GAME_OVER;
                        }
                        _batalhaGUI.reset();
                    }
                }
            }
        } else if (_estadoAtual == EstadoJogo::GAME_OVER || _estadoAtual == EstadoJogo::VITORIA) {
            if (evento.type == sf::Event::KeyPressed) {
                if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
                    iniciarNovoJogo();
                    _estadoAtual = EstadoJogo::EXPLORACAO;
                } else if (evento.key.code == sf::Keyboard::Escape) {
                    _estadoAtual = EstadoJogo::MENU_INICIAL;
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

void JogoGUI::renderizarGameOver() {
    float largura = _janela.getSize().x;
    float altura = _janela.getSize().y;

    sf::RectangleShape fundo(sf::Vector2f(largura, altura));
    fundo.setFillColor(sf::Color(25, 14, 18));
    _janela.draw(fundo);

    sf::RectangleShape painel(sf::Vector2f(largura - 160.0f, altura - 180.0f));
    painel.setPosition(80.0f, 90.0f);
    painel.setFillColor(sf::Color(38, 20, 26));
    painel.setOutlineThickness(3.0f);
    painel.setOutlineColor(sf::Color(220, 60, 60));
    _janela.draw(painel);

    sf::Text titulo("REPROVADO POR CANSACO!", _fonte, 34);
    titulo.setFillColor(sf::Color(255, 80, 80));
    titulo.setPosition(largura / 2.0f - 240.0f, 150.0f);
    _janela.draw(titulo);

    sf::Text desc("O estudante atingiu 100 pontos de cansaco e desmaiou durante a prova...", _fonte, 18);
    desc.setFillColor(sf::Color(220, 200, 200));
    desc.setPosition(largura / 2.0f - 340.0f, 230.0f);
    _janela.draw(desc);

    int pts = _semestre ? _semestre->getPontuacaoAcumulada() : 0;
    sf::Text nota("Pontuacao alcancada: " + std::to_string(pts) + " / 100 pontos", _fonte, 20);
    nota.setFillColor(sf::Color(255, 215, 0));
    nota.setPosition(largura / 2.0f - 180.0f, 280.0f);
    _janela.draw(nota);

    sf::Text dica("DICA: Use 'Pausa para o Cafe' ou tome 'Cafe Quente' do inventario para nao desmaiar!", _fonte, 16);
    dica.setFillColor(sf::Color(160, 180, 210));
    dica.setPosition(largura / 2.0f - 350.0f, 340.0f);
    _janela.draw(dica);

    sf::Text instrucao("[ENTER ou ESPACO]: Tentar Novamente   |   [ESC]: Menu Inicial", _fonte, 18);
    instrucao.setFillColor(sf::Color(255, 230, 90));
    instrucao.setPosition(largura / 2.0f - 280.0f, 440.0f);
    _janela.draw(instrucao);
}

void JogoGUI::renderizarVitoria() {
    float largura = _janela.getSize().x;
    float altura = _janela.getSize().y;

    sf::RectangleShape fundo(sf::Vector2f(largura, altura));
    fundo.setFillColor(sf::Color(14, 25, 20));
    _janela.draw(fundo);

    sf::RectangleShape painel(sf::Vector2f(largura - 160.0f, altura - 180.0f));
    painel.setPosition(80.0f, 90.0f);
    painel.setFillColor(sf::Color(20, 42, 32));
    painel.setOutlineThickness(3.0f);
    painel.setOutlineColor(sf::Color(255, 215, 0));
    _janela.draw(painel);

    sf::Text titulo("PARABENS! APROVADO EM CALCULO I!", _fonte, 32);
    titulo.setFillColor(sf::Color(255, 215, 0));
    titulo.setPosition(largura / 2.0f - 320.0f, 150.0f);
    _janela.draw(titulo);

    sf::Text desc("Voce superou Limites, Derivadas, Integrais e o Exame Final com excelencia!", _fonte, 19);
    desc.setFillColor(sf::Color(210, 245, 220));
    desc.setPosition(largura / 2.0f - 350.0f, 230.0f);
    _janela.draw(desc);

    int pts = _semestre ? _semestre->getPontuacaoAcumulada() : 100;
    sf::Text nota("Nota Final Acumulada: " + std::to_string(pts) + " / 100 pontos", _fonte, 22);
    nota.setFillColor(sf::Color(100, 255, 150));
    nota.setPosition(largura / 2.0f - 190.0f, 280.0f);
    _janela.draw(nota);

    sf::Text mencao("Mencao: Aprovado sem exame especial. O Stewart foi dominado!", _fonte, 17);
    mencao.setFillColor(sf::Color(180, 220, 255));
    mencao.setPosition(largura / 2.0f - 270.0f, 340.0f);
    _janela.draw(mencao);

    sf::Text instrucao("[ENTER ou ESPACO]: Jogar Novamente   |   [ESC]: Menu Inicial", _fonte, 18);
    instrucao.setFillColor(sf::Color(255, 230, 90));
    instrucao.setPosition(largura / 2.0f - 270.0f, 440.0f);
    _janela.draw(instrucao);
}

void JogoGUI::renderizar() {
    _janela.clear(sf::Color(15, 18, 28));

    if (_estadoAtual == EstadoJogo::MENU_INICIAL) {
        _menuInicial->renderizar(_janela);
    } else if (_estadoAtual == EstadoJogo::EXPLORACAO) {
        int qtdCafe = 0;
        int qtdDica = 0;
        if (_jogador) {
            for (const auto& item : _jogador->getItens()) {
                if (item.getNome() == "Cafe Quente" || item.getNome() == "Cafe") {
                    qtdCafe += item.getQuantidade();
                } else {
                    qtdDica += item.getQuantidade();
                }
            }
        }
        int pontuacao = _semestre ? _semestre->getPontuacaoAcumulada() : 0;
        int cansaco = _jogador ? _jogador->getCansaco() : 0;
        _mapaExploracao->renderizarComHUD(_janela, pontuacao, cansaco, qtdCafe, qtdDica);
    } else if (_estadoAtual == EstadoJogo::BATALHA) {
        if (_batalhaGUI) {
            _batalhaGUI->renderizar(_janela);
        }
    } else if (_estadoAtual == EstadoJogo::GAME_OVER) {
        renderizarGameOver();
    } else if (_estadoAtual == EstadoJogo::VITORIA) {
        renderizarVitoria();
    }

    _janela.display();
}
