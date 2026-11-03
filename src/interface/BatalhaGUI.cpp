#include "interface/BatalhaGUI.hpp"
#include <algorithm>

BatalhaGUI::BatalhaGUI(float larguraJanela, float alturaJanela, const sf::Font& fonte,
                       Jogador& jogador, const Questao& questao)
    : _fonte(fonte),
      _jogador(jogador),
      _questao(questao),
      _resultado(ResultadoBatalha::EM_ANDAMENTO),
      _indiceAcaoSelecionada(0),
      _vidaInicial(questao.getVidaResolucao()),
      _batalhaConcluida(false) {

    // Fundo da Batalha (Slate Escuro)
    _fundo.setSize(sf::Vector2f(larguraJanela, alturaJanela));
    _fundo.setFillColor(sf::Color(20, 24, 36));

    // Painel da Questão Inimiga (Topo)
    _caixaQuestao.setPosition(50.0f, 40.0f);
    _caixaQuestao.setSize(sf::Vector2f(larguraJanela - 100.0f, 220.0f));
    _caixaQuestao.setFillColor(sf::Color(32, 38, 55));
    _caixaQuestao.setOutlineThickness(2.0f);
    _caixaQuestao.setOutlineColor(sf::Color(100, 120, 160));

    // Enunciado da Questão
    _textoEnunciado.setFont(_fonte);
    _textoEnunciado.setCharacterSize(22);
    _textoEnunciado.setFillColor(sf::Color::White);
    _textoEnunciado.setString(
        "PROVA 1: LIMITES E CONTINUIDADE\n\n"
        "Desafio: " + _questao.getAssunto() + " (Dificuldade " + std::to_string(_questao.getDificuldade()) + ")\n"
        "Resolva o exercicio aplicando as tecnicas matematicas corretas!"
    );
    _textoEnunciado.setPosition(70.0f, 55.0f);

    // Barra de Vida da Questão
    _barraVidaFundo.setPosition(70.0f, 175.0f);
    _barraVidaFundo.setSize(sf::Vector2f(400.0f, 24.0f));
    _barraVidaFundo.setFillColor(sf::Color(60, 60, 60));

    _barraVidaAtual.setPosition(70.0f, 175.0f);
    _barraVidaAtual.setSize(sf::Vector2f(400.0f, 24.0f));
    _barraVidaAtual.setFillColor(sf::Color(60, 200, 90)); // Verde

    _textoVida.setFont(_fonte);
    _textoVida.setCharacterSize(16);
    _textoVida.setFillColor(sf::Color::White);
    _textoVida.setPosition(480.0f, 177.0f);

    // Barra de Cansaço do Jogador
    _barraCansacoFundo.setPosition(70.0f, 310.0f);
    _barraCansacoFundo.setSize(sf::Vector2f(350.0f, 24.0f));
    _barraCansacoFundo.setFillColor(sf::Color(60, 60, 60));

    _barraCansacoAtual.setPosition(70.0f, 310.0f);
    _barraCansacoAtual.setSize(sf::Vector2f(0.0f, 24.0f));
    _barraCansacoAtual.setFillColor(sf::Color(70, 140, 240)); // Azul

    _textoCansaco.setFont(_fonte);
    _textoCansaco.setCharacterSize(18);
    _textoCansaco.setFillColor(sf::Color::White);
    _textoCansaco.setPosition(70.0f, 280.0f);

    // Caixa de Diálogo / Mensagens de Combate
    _caixaDialogo.setPosition(50.0f, 370.0f);
    _caixaDialogo.setSize(sf::Vector2f(larguraJanela - 100.0f, 150.0f));
    _caixaDialogo.setFillColor(sf::Color(25, 30, 44));
    _caixaDialogo.setOutlineThickness(2.0f);
    _caixaDialogo.setOutlineColor(sf::Color(120, 140, 180));

    _textoMensagemLog1.setFont(_fonte);
    _textoMensagemLog1.setCharacterSize(19);
    _textoMensagemLog1.setFillColor(sf::Color(255, 230, 130)); // Amarelo
    _textoMensagemLog1.setString("A questao de Calculo comeca! Escolha uma acao abaixo.");
    _textoMensagemLog1.setPosition(70.0f, 390.0f);

    _textoMensagemLog2.setFont(_fonte);
    _textoMensagemLog2.setCharacterSize(18);
    _textoMensagemLog2.setFillColor(sf::Color(230, 140, 140)); // Vermelho claro
    _textoMensagemLog2.setString("");
    _textoMensagemLog2.setPosition(70.0f, 430.0f);

    // Botões de Ação na base da tela (Navegáveis via teclado A/D ou W/S)
    float larguraBtn = 205.0f;
    float alturaBtn = 50.0f;
    float yBtns = 560.0f;
    float espacoBtn = 225.0f;
    float xInicial = 50.0f;

    _botoesAcao.emplace_back(xInicial, yBtns, larguraBtn, alturaBtn, "1. Habilidade", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn, yBtns, larguraBtn, alturaBtn, "2. Tomar Cafe", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn * 2.0f, yBtns, larguraBtn, alturaBtn, "3. Pedir Dica", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn * 3.0f, yBtns, larguraBtn, alturaBtn, "4. Finalizar", _fonte, 18);

    _botoesAcao[0].setSelecionado(true);

    // Instruções de controle por teclado
    _textoInstrucaoTeclado.setFont(_fonte);
    _textoInstrucaoTeclado.setCharacterSize(15);
    _textoInstrucaoTeclado.setFillColor(sf::Color(140, 160, 190));
    _textoInstrucaoTeclado.setString("[A/D ou W/S: Navegar Acoes]  |  [ENTER ou ESPACO: Executar]  |  [ESC: Fugir]");
    _textoInstrucaoTeclado.setPosition(larguraJanela / 2.0f - 240.0f, 635.0f);

    atualizarBarras();
}

void BatalhaGUI::atualizarBarras() {
    // 1. Atualiza vida da questão
    float proporcaoVida = 0.0f;
    if (_vidaInicial > 0) {
        proporcaoVida = std::max(0.0f, (float)_questao.getVidaResolucao() / (float)_vidaInicial);
    }
    _barraVidaAtual.setSize(sf::Vector2f(400.0f * proporcaoVida, 24.0f));

    if (proporcaoVida > 0.5f) {
        _barraVidaAtual.setFillColor(sf::Color(70, 200, 90)); // Verde
    } else if (proporcaoVida > 0.2f) {
        _barraVidaAtual.setFillColor(sf::Color(220, 180, 50)); // Amarelo
    } else {
        _barraVidaAtual.setFillColor(sf::Color(220, 70, 70)); // Vermelho
    }

    _textoVida.setString("Resolucao: " + std::to_string(_questao.getVidaResolucao()) + " / " + std::to_string(_vidaInicial) + " HP");

    // 2. Atualiza cansaço do jogador
    int cansaco = _jogador.getCansaco();
    float proporcaoCansaco = std::min(1.0f, (float)cansaco / 100.0f);
    _barraCansacoAtual.setSize(sf::Vector2f(350.0f * proporcaoCansaco, 24.0f));

    if (cansaco < 50) {
        _barraCansacoAtual.setFillColor(sf::Color(70, 140, 240)); // Azul tranquilo
    } else if (cansaco < 80) {
        _barraCansacoAtual.setFillColor(sf::Color(230, 150, 40)); // Laranja alerta
    } else {
        _barraCansacoAtual.setFillColor(sf::Color(230, 60, 60)); // Vermelho perigo
    }

    _textoCansaco.setString("Estudante: " + std::to_string(cansaco) + " / 100 Cansaco");
}

void BatalhaGUI::executarTurnoInimigo() {
    if (_questao.isResolvida()) {
        _resultado = ResultadoBatalha::VITORIA;
        _batalhaConcluida = true;
        _textoMensagemLog2.setString("VITORIA! A questao foi resolvida! Pressione ENTER para retornar.");
        return;
    }

    _questao.executarAcaoInimiga(&_jogador);
    _textoMensagemLog2.setString("A questao contra-atacou! +" + std::to_string(_questao.getdanoContraAtaque()) + " de cansaco.");

    atualizarBarras();

    if (_jogador.getCansaco() >= 100) {
        _resultado = ResultadoBatalha::DERROTA;
        _batalhaConcluida = true;
        _textoMensagemLog2.setString("DERROTA! O estudante desmaiou de cansaco! Pressione ENTER.");
    }
}

void BatalhaGUI::processarEventos(const sf::Event& evento) {
    if (evento.type == sf::Event::KeyPressed) {
        // Se a batalha já acabou, qualquer ENTER ou ESPAÇO fecha a tela
        if (_batalhaConcluida) {
            if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
                // Estado final
            }
            return;
        }

        // Navegação entre ações via Teclado (A/D ou W/S ou Setas)
        if (evento.key.code == sf::Keyboard::A || evento.key.code == sf::Keyboard::Left ||
            evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up) {
            _indiceAcaoSelecionada = (_indiceAcaoSelecionada - 1 + (int)_botoesAcao.size()) % (int)_botoesAcao.size();
            for (size_t i = 0; i < _botoesAcao.size(); ++i) {
                _botoesAcao[i].setSelecionado((int)i == _indiceAcaoSelecionada);
            }
        } else if (evento.key.code == sf::Keyboard::D || evento.key.code == sf::Keyboard::Right ||
                   evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down) {
            _indiceAcaoSelecionada = (_indiceAcaoSelecionada + 1) % (int)_botoesAcao.size();
            for (size_t i = 0; i < _botoesAcao.size(); ++i) {
                _botoesAcao[i].setSelecionado((int)i == _indiceAcaoSelecionada);
            }
        } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
            // Executa a ação selecionada
            if (_indiceAcaoSelecionada == 0) {
                // 1. Usar Habilidade Matemática (Fatoração / Regra da Cadeia)
                int dano = 25;
                _questao.receberDanoResolucao(dano);
                _questao.concluirEtapaPrevia(); // Desbloqueia finalização
                _textoMensagemLog1.setString("Voce aplicou Fatoracao Algebrica! Causou 25 de progresso.");
                executarTurnoInimigo();
            } else if (_indiceAcaoSelecionada == 1) {
                // 2. Tomar Café (recupera energia / cansaço)
                if (_jogador.getCansaco() > 0) {
                    _jogador.alterarCansaco(-20);
                    _textoMensagemLog1.setString("Voce tomou um Cafe quente! Cansaco reduzido em 20 pontos.");
                } else {
                    _textoMensagemLog1.setString("O estudante ja esta bem disposto (cansaco zero)!");
                }
                executarTurnoInimigo();
            } else if (_indiceAcaoSelecionada == 2) {
                // 3. Pedir Dica
                _textoMensagemLog1.setString("DICA DO STEWART: " + _questao.fornecerDica());
                _textoMensagemLog2.setString("Consultar suas anotacoes nao gasta turno!");
            } else if (_indiceAcaoSelecionada == 3) {
                // 4. Tentar Finalizar
                if (_questao.tentarFinalizar()) {
                    _resultado = ResultadoBatalha::VITORIA;
                    _batalhaConcluida = true;
                    _textoMensagemLog1.setString("Substituicao Direta executada com perfeicao!");
                    _textoMensagemLog2.setString("QUESTAO RESOLVIDA COM SUCESSO! Pressione ENTER.");
                    atualizarBarras();
                } else {
                    _textoMensagemLog1.setString("Nao foi possivel finalizar! Conclua a etapa previa com Habilidades.");
                    executarTurnoInimigo();
                }
            }
        }
    }
}

void BatalhaGUI::atualizar() {
    atualizarBarras();
}

void BatalhaGUI::renderizar(sf::RenderWindow& janela) {
    janela.draw(_fundo);

    // Painel da Questão e Barras
    janela.draw(_caixaQuestao);
    janela.draw(_textoEnunciado);
    janela.draw(_barraVidaFundo);
    janela.draw(_barraVidaAtual);
    janela.draw(_textoVida);

    // Status do Jogador
    janela.draw(_textoCansaco);
    janela.draw(_barraCansacoFundo);
    janela.draw(_barraCansacoAtual);

    // Diálogo e Feedback
    janela.draw(_caixaDialogo);
    janela.draw(_textoMensagemLog1);
    janela.draw(_textoMensagemLog2);

    // Botões de Ação
    for (auto& btn : _botoesAcao) {
        btn.renderizar(janela);
    }

    janela.draw(_textoInstrucaoTeclado);
}

bool BatalhaGUI::isBatalhaConcluida() const {
    return _batalhaConcluida;
}

ResultadoBatalha BatalhaGUI::getResultado() const {
    return _resultado;
}

