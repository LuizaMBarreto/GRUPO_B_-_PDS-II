#include "interface/MapaExploracao.hpp"
#include "Item.hpp"
#include <cmath>

MapaExploracao::MapaExploracao(float larguraJanela, float alturaJanela, const sf::Font& fonte)
    : _fonte(fonte),
      _ambienteAtual(TipoAmbiente::CORREDOR),
      _temTexturaPersonagem(false),
      _temTexturaFrente(false),
      _temTexturaTras(false),
      _temTexturaCarteira(false),
      _posicaoJogador(500.0f, 350.0f),
      _velocidadeJogador(240.0f),
      _frameAnimacao(0),
      _tempoAnimacao(0.0f),
      _direcaoOlhar(DirecaoOlhar::BAIXO),
      _emMovimento(false),
      _temTexturaChao(false),
      _numeroProvaAtual(1),
      _tempoMensagem(0.0f),
      _solicitouBatalha(false) {

    // Configura a câmera direta centralizada no jogador
    _camera.setSize(larguraJanela, alturaJanela);
    _camera.setCenter(_posicaoJogador);

    carregarTexturas();
    trocarAmbiente(TipoAmbiente::CORREDOR);
    adicionarItens();

    // Barra de HUD Superior fixada na tela
    _barraHudSuperior.setPosition(0.0f, 0.0f);
    _barraHudSuperior.setSize(sf::Vector2f(larguraJanela, 42.0f));
    _barraHudSuperior.setFillColor(sf::Color(18, 22, 34, 235));
    _barraHudSuperior.setOutlineThickness(1.0f);
    _barraHudSuperior.setOutlineColor(sf::Color(80, 95, 130));

    _textoHudSuperior.setFont(_fonte);
    _textoHudSuperior.setCharacterSize(16);
    _textoHudSuperior.setFillColor(sf::Color(240, 245, 255));
    _textoHudSuperior.setPosition(20.0f, 10.0f);

    // Sprite do Estudante (Jogador)
    if (_temTexturaFrente) {
        _spriteJogador.setTexture(_texturaFrente);
        _spriteJogador.setTextureRect(sf::IntRect(0, 0, 364, 507));
        _spriteJogador.setScale(0.148f, 0.148f);
        _spriteJogador.setOrigin(182.0f, 253.5f);
        _spriteJogador.setPosition(_posicaoJogador);
    } else if (_temTexturaPersonagem) {
        _spriteJogador.setTexture(_texturaPersonagem);
        _spriteJogador.setTextureRect(sf::IntRect(4 * 638, 0, 638, 858));
        _spriteJogador.setScale(0.0874f, 0.0874f);
        _spriteJogador.setOrigin(319.0f, 429.0f);
        _spriteJogador.setPosition(_posicaoJogador);
    } else {
        _fallbackJogador.setSize(sf::Vector2f(32.0f, 32.0f));
        _fallbackJogador.setFillColor(sf::Color(70, 150, 255));
        _fallbackJogador.setOutlineThickness(2.0f);
        _fallbackJogador.setOutlineColor(sf::Color::White);
        _fallbackJogador.setOrigin(16.0f, 16.0f);
        _fallbackJogador.setPosition(_posicaoJogador);
    }

    // Textos do HUD
    _textoInteracao.setFont(_fonte);
    _textoInteracao.setCharacterSize(18);
    _textoInteracao.setFillColor(sf::Color(255, 230, 90)); // Amarelo destaque
    _textoInteracao.setString("");

    _textoStatus.setFont(_fonte);
    _textoStatus.setCharacterSize(15);
    _textoStatus.setFillColor(sf::Color(180, 195, 220));
    _textoStatus.setString("[WASD ou Setas: Mover]  |  [ENTER ou ESPACO: Interagir]  |  [ESC: Menu]");
    _textoStatus.setPosition(20.0f, alturaJanela - 30.0f);

    _textoMensagem.setFont(_fonte);
    _textoMensagem.setCharacterSize(20);
    _textoMensagem.setFillColor(sf::Color(100, 255, 160)); // Verde
    _textoMensagem.setString("");
    _textoMensagem.setPosition(250.0f, 50.0f);

    setProvaAtual(1);
}

void MapaExploracao::carregarTexturas() {
    if (_texturaPersonagem.loadFromFile("assets/sprites/personagem.png")) {
        _temTexturaPersonagem = true;
    }

    if (_texturaFrente.loadFromFile("assets/sprites/personagem_fente.png")) {
        _temTexturaFrente = true;
    }

    if (_texturaTras.loadFromFile("assets/sprites/personagem_tras.png")) {
        _temTexturaTras = true;
    }

    if (_texturaCarteira.loadFromFile("assets/sprites/cadeira.png")) {
        _temTexturaCarteira = true;
    }

    if (_texturaChao.loadFromFile("assets/sprites/chao.png")) {
        _texturaChao.setRepeated(true);
        _temTexturaChao = true;
    }
}

void MapaExploracao::trocarAmbiente(TipoAmbiente novo) {
    _ambienteAtual = novo;
    _paredes.clear();
    _paredesVisuais.clear();

    if (_ambienteAtual == TipoAmbiente::CORREDOR) {
        configurarCorredor();
    } else {
        configurarSalaDeAula();
    }
}

void MapaExploracao::configurarCorredor() {
    // Chão do Corredor
    _chaoCorredor.setPosition(50.0f, 250.0f);
    _chaoCorredor.setSize(sf::Vector2f(900.0f, 200.0f));

    if (_temTexturaChao) {
        _chaoCorredor.setTexture(&_texturaChao);
        _chaoCorredor.setTextureRect(sf::IntRect(0, 0, 900, 200));
        _chaoCorredor.setFillColor(sf::Color(200, 200, 220));
    } else {
        _chaoCorredor.setFillColor(sf::Color(38, 44, 58));
    }
    _chaoCorredor.setOutlineThickness(3.0f);
    _chaoCorredor.setOutlineColor(sf::Color(75, 90, 120));

    // Porta da Sala 101 no Corredor
    _portaEntradaSala.setPosition(470.0f, 240.0f);
    _portaEntradaSala.setSize(sf::Vector2f(60.0f, 20.0f));
    _portaEntradaSala.setFillColor(sf::Color(150, 80, 45)); // Madeira
    _portaEntradaSala.setOutlineThickness(2.0f);
    _portaEntradaSala.setOutlineColor(sf::Color(255, 215, 0));

    // Placa da Sala 101
    _placaCorredor.setFont(_fonte);
    _placaCorredor.setString("SALA 101: PROVA DE CALCULO I");
    _placaCorredor.setCharacterSize(15);
    _placaCorredor.setFillColor(sf::Color(255, 240, 180));
    _placaCorredor.setPosition(375.0f, 215.0f);

    // Paredes do Corredor
    std::vector<sf::FloatRect> paredesCorredor = {
        sf::FloatRect(40.0f, 230.0f, 430.0f, 20.0f),   // Parede cima esquerda
        sf::FloatRect(530.0f, 230.0f, 430.0f, 20.0f),  // Parede cima direita
        sf::FloatRect(40.0f, 450.0f, 920.0f, 20.0f),   // Parede inferior
        sf::FloatRect(30.0f, 230.0f, 20.0f, 240.0f),   // Parede esquerda
        sf::FloatRect(940.0f, 230.0f, 20.0f, 240.0f)   // Parede direita
    };
    for (const auto& p : paredesCorredor) {
        _paredes.push_back(p);
        _paredesVisuais.push_back(p);
    }
}

void MapaExploracao::configurarSalaDeAula() {
    // Chão da Sala de Aula
    _chaoSala.setPosition(200.0f, 100.0f);
    _chaoSala.setSize(sf::Vector2f(600.0f, 500.0f));

    if (_temTexturaChao) {
        _chaoSala.setTexture(&_texturaChao);
        _chaoSala.setTextureRect(sf::IntRect(0, 0, 600, 500));
        _chaoSala.setFillColor(sf::Color(240, 230, 210)); // Tom mais claro para sala
    } else {
        _chaoSala.setFillColor(sf::Color(50, 60, 80));
    }
    _chaoSala.setOutlineThickness(3.0f);
    _chaoSala.setOutlineColor(sf::Color(90, 110, 145));

    // Lousa verde no topo
    _lousa.setPosition(340.0f, 105.0f);
    _lousa.setSize(sf::Vector2f(320.0f, 35.0f));
    _lousa.setFillColor(sf::Color(30, 85, 50)); // Verde lousa
    _lousa.setOutlineThickness(2.0f);
    _lousa.setOutlineColor(sf::Color(160, 120, 70));

    _textoLousa.setFont(_fonte);
    _textoLousa.setString("P1: d/dx [f(g(x))] = f'(g(x))g'(x)");
    _textoLousa.setCharacterSize(13);
    _textoLousa.setFillColor(sf::Color::White);
    _textoLousa.setPosition(355.0f, 113.0f);

    // Mesa do Professor (local da prova)
    _mesaProfessor.setPosition(440.0f, 170.0f);
    _mesaProfessor.setSize(sf::Vector2f(120.0f, 45.0f));
    _mesaProfessor.setFillColor(sf::Color(140, 75, 40));
    _mesaProfessor.setOutlineThickness(2.0f);
    _mesaProfessor.setOutlineColor(sf::Color(255, 215, 0));

    _placaProva.setFont(_fonte);
    _placaProva.setString("MESA DA PROVA");
    _placaProva.setCharacterSize(14);
    _placaProva.setFillColor(sf::Color::White);
    _placaProva.setPosition(448.0f, 182.0f);

    // Carteiras dos alunos (Fileiras decorativas)
    _carteiras.clear();
    _spritesCarteiras.clear();
    std::vector<sf::Vector2f> posCarteiras = {
        {270.0f, 290.0f}, {450.0f, 290.0f}, {630.0f, 290.0f},
        {270.0f, 400.0f}, {450.0f, 400.0f}, {630.0f, 400.0f}
    };
    for (const auto& pos : posCarteiras) {
        if (_temTexturaCarteira) {
            sf::Sprite sp(_texturaCarteira);
            sp.setScale(0.145f, 0.145f); // ~53px de largura x ~71px de altura
            sp.setPosition(pos.x + 3.0f, pos.y - 15.0f);
            _spritesCarteiras.push_back(sp);
        } else {
            sf::RectangleShape cart(sf::Vector2f(60.0f, 35.0f));
            cart.setPosition(pos);
            cart.setFillColor(sf::Color(120, 85, 60));
            cart.setOutlineThickness(1.0f);
            cart.setOutlineColor(sf::Color(180, 140, 100));
            _carteiras.push_back(cart);
        }
        _paredes.push_back(sf::FloatRect(pos.x, pos.y, 60.0f, 40.0f)); // Colisão com as carteiras
    }

    // Porta de saída para o Corredor
    _portaSaidaSala.setPosition(470.0f, 590.0f);
    _portaSaidaSala.setSize(sf::Vector2f(60.0f, 15.0f));
    _portaSaidaSala.setFillColor(sf::Color(160, 90, 50));
    _portaSaidaSala.setOutlineThickness(2.0f);
    _portaSaidaSala.setOutlineColor(sf::Color(255, 215, 0));

    _placaSaida.setFont(_fonte);
    _placaSaida.setString("SAIDA");
    _placaSaida.setCharacterSize(14);
    _placaSaida.setFillColor(sf::Color::White);
    _placaSaida.setPosition(477.0f, 568.0f);

    // Paredes da Sala de Aula
    std::vector<sf::FloatRect> paredesSala = {
        sf::FloatRect(190.0f, 80.0f, 620.0f, 20.0f),   // Topo
        sf::FloatRect(180.0f, 80.0f, 20.0f, 530.0f),   // Esquerda
        sf::FloatRect(800.0f, 80.0f, 20.0f, 530.0f),   // Direita
        sf::FloatRect(190.0f, 600.0f, 280.0f, 20.0f),  // Baixo esquerda
        sf::FloatRect(530.0f, 600.0f, 280.0f, 20.0f)   // Baixo direita
    };
    for (const auto& p : paredesSala) {
        _paredes.push_back(p);
        _paredesVisuais.push_back(p);
    }

    // Mesa do professor bloqueia passagem (colisão invisível)
    _paredes.push_back(sf::FloatRect(440.0f, 170.0f, 120.0f, 45.0f));
}

void MapaExploracao::adicionarItens() {
    _itensNoChao.clear();

    // 1. Café Quente no Corredor
    ItemNoMapa cafe;
    cafe.nome = "Cafe";
    cafe.posicao = sf::Vector2f(200.0f, 350.0f);
    cafe.coletado = false;
    cafe.ambiente = TipoAmbiente::CORREDOR;
    cafe.forma.setSize(sf::Vector2f(20.0f, 20.0f));
    cafe.forma.setOrigin(10.0f, 10.0f);
    cafe.forma.setPosition(cafe.posicao);
    cafe.forma.setFillColor(sf::Color(180, 100, 50));
    cafe.forma.setOutlineThickness(2.0f);
    cafe.forma.setOutlineColor(sf::Color(255, 230, 150));
    _itensNoChao.push_back(cafe);

    // 2. Livro de Dicas dentro da Sala de Aula
    ItemNoMapa dica;
    dica.nome = "Livro de Dicas";
    dica.posicao = sf::Vector2f(720.0f, 200.0f);
    dica.coletado = false;
    dica.ambiente = TipoAmbiente::SALA_DE_AULA;
    dica.forma.setSize(sf::Vector2f(20.0f, 20.0f));
    dica.forma.setOrigin(10.0f, 10.0f);
    dica.forma.setPosition(dica.posicao);
    dica.forma.setFillColor(sf::Color(50, 150, 90));
    dica.forma.setOutlineThickness(2.0f);
    dica.forma.setOutlineColor(sf::Color::White);
    _itensNoChao.push_back(dica);
}

bool MapaExploracao::verificarColisao(const sf::FloatRect& novaCaixa) const {
    for (const auto& parede : _paredes) {
        if (parede.intersects(novaCaixa)) {
            return true;
        }
    }
    return false;
}

void MapaExploracao::processarEventos(const sf::Event& evento, Jogador& jogador) {
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {

            // 1. Transição: Entrar na Sala de Aula pelo Corredor
            if (_ambienteAtual == TipoAmbiente::CORREDOR) {
                float distPorta = std::hypot(_posicaoJogador.x - 500.0f, _posicaoJogador.y - 250.0f);
                if (distPorta < 65.0f) {
                    trocarAmbiente(TipoAmbiente::SALA_DE_AULA);
                    _posicaoJogador = sf::Vector2f(500.0f, 540.0f); // Surge na entrada da sala
                    _spriteJogador.setPosition(_posicaoJogador);
                    _fallbackJogador.setPosition(_posicaoJogador);
                    _camera.setCenter(_posicaoJogador);
                    _textoMensagem.setString("Voce entrou na Sala 101: Sala de Prova!");
                    _tempoMensagem = 2.5f;
                    return;
                }
            }

            // 2. Transição: Sair da Sala de Aula para o Corredor
            else if (_ambienteAtual == TipoAmbiente::SALA_DE_AULA) {
                float distSaida = std::hypot(_posicaoJogador.x - 500.0f, _posicaoJogador.y - 590.0f);
                if (distSaida < 65.0f) {
                    trocarAmbiente(TipoAmbiente::CORREDOR);
                    _posicaoJogador = sf::Vector2f(500.0f, 290.0f); // Surge em frente à porta no corredor
                    _spriteJogador.setPosition(_posicaoJogador);
                    _fallbackJogador.setPosition(_posicaoJogador);
                    _camera.setCenter(_posicaoJogador);
                    _textoMensagem.setString("Voce voltou ao Corredor.");
                    _tempoMensagem = 2.5f;
                    return;
                }

                // 3. Iniciar Prova na Mesa do Professor (apenas dentro da sala!)
                float distMesa = std::hypot(_posicaoJogador.x - 500.0f, _posicaoJogador.y - 190.0f);
                if (distMesa < 75.0f) {
                    _solicitouBatalha = true;
                    return;
                }
            }

            // 4. Coletar Itens no chão do ambiente atual
            for (auto& item : _itensNoChao) {
                if (!item.coletado && item.ambiente == _ambienteAtual) {
                    float distItem = std::hypot(_posicaoJogador.x - item.posicao.x, _posicaoJogador.y - item.posicao.y);
                    if (distItem < 45.0f) {
                        item.coletado = true;
                        if (item.nome == "Cafe") {
                            jogador.adicionarItem(Item("Cafe", "Reduz o cansaco em 10 pontos", 1, "CURA_ENERGIA"));
                            _textoMensagem.setString("Voce pegou: Cafe Quente! (+1 no inventario)");
                        } else {
                            jogador.adicionarItem(Item("Dica de Calculo", "Revela a dica da questao", 1, "DICA"));
                            _textoMensagem.setString("Voce pegou: Livro de Dicas! (+1 no inventario)");
                        }
                        _tempoMensagem = 2.5f;
                        break;
                    }
                }
            }
        }
    }
}

void MapaExploracao::atualizarPosicaoSprite(const sf::Vector2f& direcao, float dt) {
    _spriteJogador.setPosition(_posicaoJogador);
    _fallbackJogador.setPosition(_posicaoJogador);

    // Determina a direção prioritária do olhar
    if (std::abs(direcao.x) > std::abs(direcao.y)) {
        if (direcao.x > 0.0f) _direcaoOlhar = DirecaoOlhar::DIREITA;
        else if (direcao.x < 0.0f) _direcaoOlhar = DirecaoOlhar::ESQUERDA;
    } else if (std::abs(direcao.y) > 0.0f) {
        if (direcao.y > 0.0f) _direcaoOlhar = DirecaoOlhar::BAIXO;
        else if (direcao.y < 0.0f) _direcaoOlhar = DirecaoOlhar::CIMA;
    }

    _emMovimento = (direcao.x != 0.0f || direcao.y != 0.0f);

    if (_emMovimento) {
        _tempoAnimacao += dt;
        if (_tempoAnimacao >= 0.15f) {
            _tempoAnimacao = 0.0f;
            _frameAnimacao = (_frameAnimacao + 1) % 4;
        }
    } else {
        _frameAnimacao = 0; // Frame de repouso
        _tempoAnimacao = 0.0f;
    }

    if (_direcaoOlhar == DirecaoOlhar::BAIXO && _temTexturaFrente) {
        _spriteJogador.setTexture(_texturaFrente);
        _spriteJogador.setTextureRect(sf::IntRect(_frameAnimacao * 364, 0, 364, 507));
        _spriteJogador.setScale(0.148f, 0.148f);
        _spriteJogador.setOrigin(182.0f, 253.5f);
    } else if (_direcaoOlhar == DirecaoOlhar::CIMA && _temTexturaTras) {
        _spriteJogador.setTexture(_texturaTras);
        _spriteJogador.setTextureRect(sf::IntRect(_frameAnimacao * 364, 0, 364, 507));
        _spriteJogador.setScale(0.148f, 0.148f);
        _spriteJogador.setOrigin(182.0f, 253.5f);
    } else if (_temTexturaPersonagem) {
        _spriteJogador.setTexture(_texturaPersonagem);
        // Frames 0 a 3: Direita. Frames 4 a 7: Esquerda.
        int baseFrame = (_direcaoOlhar == DirecaoOlhar::DIREITA) ? 0 : 4;
        int indiceFrame = baseFrame + _frameAnimacao;
        _spriteJogador.setTextureRect(sf::IntRect(indiceFrame * 638, 0, 638, 858));
        _spriteJogador.setScale(0.0874f, 0.0874f);
        _spriteJogador.setOrigin(319.0f, 429.0f);
    }
}

void MapaExploracao::atualizar(float dt) {
    // 1. Movimentação via Teclado (WASD / Setas)
    sf::Vector2f direcao(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        direcao.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        direcao.y += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        direcao.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        direcao.x += 1.0f;
    }

    if (direcao.x != 0.0f && direcao.y != 0.0f) {
        direcao /= 1.4142f;
    }

    // Testa colisão em X
    sf::Vector2f novaPos = _posicaoJogador;
    novaPos.x += direcao.x * _velocidadeJogador * dt;
    sf::FloatRect caixaX(novaPos.x - 16.0f, _posicaoJogador.y - 16.0f, 32.0f, 32.0f);
    if (!verificarColisao(caixaX)) {
        _posicaoJogador.x = novaPos.x;
    }

    // Testa colisão em Y
    novaPos.y = _posicaoJogador.y + direcao.y * _velocidadeJogador * dt;
    sf::FloatRect caixaY(_posicaoJogador.x - 16.0f, novaPos.y - 16.0f, 32.0f, 32.0f);
    if (!verificarColisao(caixaY)) {
        _posicaoJogador.y = novaPos.y;
    }

    atualizarPosicaoSprite(direcao, dt);

    // Câmera segue diretamente o jogador (sem suavização e sem clamp)
    _camera.setCenter(_posicaoJogador);

    // 2. Atualiza Dicas de Interação dinâmicas
    _textoInteracao.setString("");

    if (_ambienteAtual == TipoAmbiente::CORREDOR) {
        float distPorta = std::hypot(_posicaoJogador.x - 500.0f, _posicaoJogador.y - 250.0f);
        if (distPorta < 65.0f) {
            _textoInteracao.setString("[ENTER ou ESPACO] Entrar na Sala");
            _textoInteracao.setPosition(370.0f, 290.0f);
        }
    } else if (_ambienteAtual == TipoAmbiente::SALA_DE_AULA) {
        float distSaida = std::hypot(_posicaoJogador.x - 500.0f, _posicaoJogador.y - 590.0f);
        float distMesa = std::hypot(_posicaoJogador.x - 500.0f, _posicaoJogador.y - 190.0f);

        if (distSaida < 65.0f) {
            _textoInteracao.setString("[ENTER ou ESPACO] Sair para o Corredor");
            _textoInteracao.setPosition(370.0f, 520.0f);
        } else if (distMesa < 75.0f) {
            _textoInteracao.setString("[ENTER ou ESPACO] Iniciar Prova de Calculo I!");
            _textoInteracao.setPosition(320.0f, 230.0f);
        }
    }

    // Dicas de itens
    for (const auto& item : _itensNoChao) {
        if (!item.coletado && item.ambiente == _ambienteAtual) {
            float distItem = std::hypot(_posicaoJogador.x - item.posicao.x, _posicaoJogador.y - item.posicao.y);
            if (distItem < 45.0f) {
                _textoInteracao.setString("[ENTER ou ESPACO] Pegar " + item.nome);
                _textoInteracao.setPosition(item.posicao.x - 70.0f, item.posicao.y - 35.0f);
                break;
            }
        }
    }

    // Temporizador da mensagem
    if (_tempoMensagem > 0.0f) {
        _tempoMensagem -= dt;
    }
}

void MapaExploracao::setProvaAtual(int numeroProva) {
    _numeroProvaAtual = numeroProva;

    if (_numeroProvaAtual == 1) {
        _placaCorredor.setString("SALA 101: PROVA 1 - LIMITES");
        _textoLousa.setString("P1: lim x->3 (x^2-9)/(x-3) = lim (x+3) = 6");
        _placaProva.setString("MESA DA P1");
    } else if (_numeroProvaAtual == 2) {
        _placaCorredor.setString("SALA 101: PROVA 2 - DERIVADAS");
        _textoLousa.setString("P2: d/dx [f(g(x))] = f'(g(x)) * g'(x)");
        _placaProva.setString("MESA DA P2");
    } else if (_numeroProvaAtual == 3) {
        _placaCorredor.setString("SALA 101: PROVA 3 - INTEGRAIS");
        _textoLousa.setString("P3: integral(u dv) = uv - integral(v du)");
        _placaProva.setString("MESA DA P3");
    } else {
        _placaCorredor.setString("SALA 101: PROVA 4 - EXAME FINAL");
        _textoLousa.setString("P4: Stewart Geral | Regra de L'Hopital");
        _placaProva.setString("MESA DA P4");
    }
}

void MapaExploracao::renderizar(sf::RenderWindow& janela) {
    renderizarComHUD(janela, 0, 0, 0, 0);
}

void MapaExploracao::renderizarComHUD(sf::RenderWindow& janela, int pontuacao, int cansaco, int qtdCafe, int qtdDica) {
    // 1. Ativa a câmera dinâmica para desenhar o mundo
    janela.setView(_camera);

    if (_ambienteAtual == TipoAmbiente::CORREDOR) {
        janela.draw(_chaoCorredor);
        janela.draw(_portaEntradaSala);
        janela.draw(_placaCorredor);
    } else {
        janela.draw(_chaoSala);
        janela.draw(_lousa);
        janela.draw(_textoLousa);
        if (_temTexturaCarteira) {
            for (const auto& sp : _spritesCarteiras) {
                janela.draw(sp);
            }
        } else {
            for (const auto& carteira : _carteiras) {
                janela.draw(carteira);
            }
        }
        janela.draw(_mesaProfessor);
        janela.draw(_placaProva);
        janela.draw(_portaSaidaSala);
        janela.draw(_placaSaida);
    }

    // Paredes estruturais
    for (const auto& parede : _paredesVisuais) {
        sf::RectangleShape p(sf::Vector2f(parede.width, parede.height));
        p.setPosition(parede.left, parede.top);
        p.setFillColor(sf::Color(65, 75, 100));
        janela.draw(p);
    }

    // Itens no chão do ambiente atual
    for (const auto& item : _itensNoChao) {
        if (!item.coletado && item.ambiente == _ambienteAtual) {
            janela.draw(item.forma);
        }
    }

    // Jogador no mundo
    if (_temTexturaPersonagem) {
        janela.draw(_spriteJogador);
    } else {
        janela.draw(_fallbackJogador);
    }

    // Texto de interação no mundo (perto do objeto/porta)
    if (!_textoInteracao.getString().isEmpty()) {
        janela.draw(_textoInteracao);
    }

    // 2. HUD Fixo na Tela (restaura view padrão)
    janela.setView(janela.getDefaultView());

    // Barra de topo
    std::string nomeProva;
    if (_numeroProvaAtual == 1) nomeProva = "P1 (Limites)";
    else if (_numeroProvaAtual == 2) nomeProva = "P2 (Derivadas)";
    else if (_numeroProvaAtual == 3) nomeProva = "P3 (Integrais)";
    else nomeProva = "P4 (Exame Final)";

    _textoHudSuperior.setString(
        "Semestre: " + nomeProva +
        "   |   Pontos: " + std::to_string(pontuacao) + "/100" +
        "   |   Cansaco: " + std::to_string(cansaco) + "/100" +
        "   |   Cafe: " + std::to_string(qtdCafe) +
        "   |   Livros: " + std::to_string(qtdDica)
    );

    janela.draw(_barraHudSuperior);
    janela.draw(_textoHudSuperior);
    janela.draw(_textoStatus);

    if (_tempoMensagem > 0.0f) {
        janela.draw(_textoMensagem);
    }
}

bool MapaExploracao::deveIniciarBatalha() {
    return _solicitouBatalha;
}

void MapaExploracao::resetarSinalBatalha() {
    _solicitouBatalha = false;
}

void MapaExploracao::resetarPosicaoJogador() {
    trocarAmbiente(TipoAmbiente::CORREDOR);
    _posicaoJogador = sf::Vector2f(500.0f, 350.0f);
    _spriteJogador.setPosition(_posicaoJogador);
    _fallbackJogador.setPosition(_posicaoJogador);
    _camera.setCenter(_posicaoJogador);
}

TipoAmbiente MapaExploracao::getAmbienteAtual() const {
    return _ambienteAtual;
}
