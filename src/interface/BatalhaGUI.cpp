#include "interface/BatalhaGUI.hpp"
#include <algorithm>

BatalhaGUI::BatalhaGUI(float larguraJanela, float alturaJanela, const sf::Font& fonte,
                       Jogador& jogador, const Prova& prova, int numeroProva)
    : _fonte(fonte),
      _jogador(jogador),
      _questoes(prova.getQuestoes()),
      _indiceQuestaoAtual(0),
      _questao(_questoes.empty() ? Questao("Limite", 1, 50, "Fatore a expressao") : _questoes[0]),
      _resultado(ResultadoBatalha::EM_ANDAMENTO),
      _modo(ModoBatalha::ACOES_PRINCIPAIS),
      _numeroProva(numeroProva),
      _indiceSubmenuSelecionado(0),
      _indiceAcaoSelecionada(0),
      _vidaInicial(_questao.getVidaResolucao()),
      _batalhaConcluida(false),
      _aguardandoAvancoQuestao(false) {

    // Fundo da Batalha (Slate Escuro)
    _fundo.setSize(sf::Vector2f(larguraJanela, alturaJanela));
    _fundo.setFillColor(sf::Color(20, 24, 36));

    // Painel da Questão Inimiga (Topo)
    _caixaQuestao.setPosition(50.0f, 30.0f);
    _caixaQuestao.setSize(sf::Vector2f(larguraJanela - 100.0f, 210.0f));
    _caixaQuestao.setFillColor(sf::Color(32, 38, 55));
    _caixaQuestao.setOutlineThickness(2.0f);
    _caixaQuestao.setOutlineColor(sf::Color(100, 120, 160));

    // Enunciado da Questão
    _textoEnunciado.setFont(_fonte);
    _textoEnunciado.setCharacterSize(19);
    _textoEnunciado.setFillColor(sf::Color::White);
    _textoEnunciado.setPosition(70.0f, 45.0f);

    // Barra de Vida da Questão
    _barraVidaFundo.setPosition(70.0f, 175.0f);
    _barraVidaFundo.setSize(sf::Vector2f(400.0f, 24.0f));
    _barraVidaFundo.setFillColor(sf::Color(60, 60, 60));

    _barraVidaAtual.setPosition(70.0f, 175.0f);
    _barraVidaAtual.setSize(sf::Vector2f(400.0f, 24.0f));
    _barraVidaAtual.setFillColor(sf::Color(60, 200, 90));

    _textoVida.setFont(_fonte);
    _textoVida.setCharacterSize(16);
    _textoVida.setFillColor(sf::Color::White);
    _textoVida.setPosition(480.0f, 177.0f);

    // Barra de Cansaço do Jogador
    _barraCansacoFundo.setPosition(70.0f, 275.0f);
    _barraCansacoFundo.setSize(sf::Vector2f(350.0f, 24.0f));
    _barraCansacoFundo.setFillColor(sf::Color(60, 60, 60));

    _barraCansacoAtual.setPosition(70.0f, 275.0f);
    _barraCansacoAtual.setSize(sf::Vector2f(0.0f, 24.0f));
    _barraCansacoAtual.setFillColor(sf::Color(70, 140, 240));

    _textoCansaco.setFont(_fonte);
    _textoCansaco.setCharacterSize(18);
    _textoCansaco.setFillColor(sf::Color::White);
    _textoCansaco.setPosition(70.0f, 245.0f);

    // Caixa de Diálogo / Mensagens de Combate
    _caixaDialogo.setPosition(50.0f, 320.0f);
    _caixaDialogo.setSize(sf::Vector2f(larguraJanela - 100.0f, 125.0f));
    _caixaDialogo.setFillColor(sf::Color(25, 30, 44));
    _caixaDialogo.setOutlineThickness(2.0f);
    _caixaDialogo.setOutlineColor(sf::Color(120, 140, 180));

    _textoMensagemLog1.setFont(_fonte);
    _textoMensagemLog1.setCharacterSize(18);
    _textoMensagemLog1.setFillColor(sf::Color(255, 230, 130)); // Amarelo
    _textoMensagemLog1.setString("A prova comeca! Selecione uma Habilidade ou Item abaixo.");
    _textoMensagemLog1.setPosition(70.0f, 335.0f);

    _textoMensagemLog2.setFont(_fonte);
    _textoMensagemLog2.setCharacterSize(17);
    _textoMensagemLog2.setFillColor(sf::Color(230, 140, 140)); // Vermelho claro
    _textoMensagemLog2.setString("");
    _textoMensagemLog2.setPosition(70.0f, 375.0f);

    // Submenu de Seleção de Habilidade/Item (ocupa a parte inferior quando ativo)
    _painelSubmenu.setPosition(50.0f, 460.0f);
    _painelSubmenu.setSize(sf::Vector2f(larguraJanela - 100.0f, 185.0f));
    _painelSubmenu.setFillColor(sf::Color(24, 28, 42));
    _painelSubmenu.setOutlineThickness(2.0f);
    _painelSubmenu.setOutlineColor(sf::Color(255, 215, 0));

    _tituloSubmenu.setFont(_fonte);
    _tituloSubmenu.setCharacterSize(17);
    _tituloSubmenu.setFillColor(sf::Color(255, 215, 0));
    _tituloSubmenu.setPosition(70.0f, 470.0f);

    // Botões de Ação na base da tela (Navegáveis via teclado A/D ou W/S)
    float larguraBtn = 205.0f;
    float alturaBtn = 50.0f;
    float yBtns = 500.0f;
    float espacoBtn = 225.0f;
    float xInicial = 50.0f;

    _botoesAcao.emplace_back(xInicial, yBtns, larguraBtn, alturaBtn, "1. Habilidade", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn, yBtns, larguraBtn, alturaBtn, "2. Itens", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn * 2.0f, yBtns, larguraBtn, alturaBtn, "3. Pedir Dica", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn * 3.0f, yBtns, larguraBtn, alturaBtn, "4. Finalizar", _fonte, 18);

    _botoesAcao[0].setSelecionado(true);

    // Instruções de controle por teclado
    _textoInstrucaoTeclado.setFont(_fonte);
    _textoInstrucaoTeclado.setCharacterSize(15);
    _textoInstrucaoTeclado.setFillColor(sf::Color(140, 160, 190));
    _textoInstrucaoTeclado.setString("[A/D ou W/S: Navegar]  |  [ENTER/ESPACO: Executar]  |  [ESC: Cancelar/Fugir]");
    _textoInstrucaoTeclado.setPosition(larguraJanela / 2.0f - 260.0f, 620.0f);

    atualizarEnunciado();
    atualizarBarras();
}

BatalhaGUI::BatalhaGUI(float larguraJanela, float alturaJanela, const sf::Font& fonte,
                       Jogador& jogador, const Questao& questao)
    : BatalhaGUI(larguraJanela, alturaJanela, fonte, jogador, Prova(1, 1), 1) {
    _questoes.clear();
    _questoes.push_back(questao);
    _questao = questao;
    _vidaInicial = questao.getVidaResolucao();
    atualizarEnunciado();
    atualizarBarras();
}

void BatalhaGUI::atualizarEnunciado() {
    std::string nomeProva;
    if (_numeroProva == 1) nomeProva = "PROVA 1: LIMITES E CONTINUIDADE";
    else if (_numeroProva == 2) nomeProva = "PROVA 2: DERIVADAS E TAXAS RELACIONADAS";
    else if (_numeroProva == 3) nomeProva = "PROVA 3: INTEGRAIS E TECNICAS DE INTEGRACAO";
    else nomeProva = "PROVA 4: EXAME FINAL DE CALCULO I";

    size_t total = _questoes.empty() ? 1 : _questoes.size();
    size_t atual = _indiceQuestaoAtual + 1;

    std::string strEquacao = _questao.getEquacao().empty() ? "" : ("\nEquacao: " + _questao.getEquacao());

    _textoEnunciado.setString(
        nomeProva + "  (Questao " + std::to_string(atual) + " de " + std::to_string(total) + ")\n\n" +
        "Desafio: " + _questao.getAssunto() + " (Dificuldade " + std::to_string(_questao.getDificuldade()) + ")" +
        strEquacao + "\n" +
        "Resolva o exercicio aplicando as tecnicas e finalize com Fechamento!"
    );
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
        _barraCansacoAtual.setFillColor(sf::Color(70, 140, 240)); // Azul
    } else if (cansaco < 80) {
        _barraCansacoAtual.setFillColor(sf::Color(230, 150, 40)); // Laranja alerta
    } else {
        _barraCansacoAtual.setFillColor(sf::Color(230, 60, 60)); // Vermelho perigo
    }

    _textoCansaco.setString("Estudante: " + std::to_string(cansaco) + " / 100 Cansaco");
}

void BatalhaGUI::atualizarSubmenu() {
    _textosSubmenu.clear();

    if (_modo == ModoBatalha::SELECIONANDO_HABILIDADE) {
        _tituloSubmenu.setString("SELECIONE A HABILIDADE MATEMATICA [W/S: Navegar | ENTER: Aplicar | ESC: Voltar]");
        const auto& habs = _jogador.getHabilidades();
        if (habs.empty()) {
            sf::Text t("Nenhuma habilidade cadastrada.", _fonte, 16);
            t.setPosition(75.0f, 510.0f);
            t.setFillColor(sf::Color(180, 180, 180));
            _textosSubmenu.push_back(t);
            return;
        }

        for (size_t i = 0; i < habs.size(); ++i) {
            std::string linha;
            if ((int)i == _indiceSubmenuSelecionado) {
                linha = "> " + habs[i].getNome();
            } else {
                linha = "  " + habs[i].getNome();
            }

            if (habs[i].afetaInimigo()) {
                linha += "  [-" + std::to_string(habs[i].getEfeitoValor()) + " HP] (" + habs[i].getDescricao() + ")";
            } else {
                linha += "  [-" + std::to_string(habs[i].getEfeitoValor()) + " Cansaco] (" + habs[i].getDescricao() + ")";
            }

            sf::Text t(linha, _fonte, 15);
            // Divide em duas colunas ou lista compacta
            float yPos = 505.0f + (float)(i % 4) * 28.0f;
            float xPos = (i < 4) ? 75.0f : 520.0f;
            t.setPosition(xPos, yPos);

            if ((int)i == _indiceSubmenuSelecionado) {
                t.setFillColor(sf::Color(255, 230, 80));
            } else {
                t.setFillColor(sf::Color(200, 210, 225));
            }
            _textosSubmenu.push_back(t);
        }
    } else if (_modo == ModoBatalha::SELECIONANDO_ITEM) {
        _tituloSubmenu.setString("INVENTARIO DE ITENS [W/S: Navegar | ENTER: Consumir | ESC: Voltar]");
        const auto& itens = _jogador.getItens();
        if (itens.empty()) {
            sf::Text t("Nenhum item disponivel no inventario.", _fonte, 16);
            t.setPosition(75.0f, 515.0f);
            t.setFillColor(sf::Color(180, 180, 180));
            _textosSubmenu.push_back(t);
            return;
        }

        for (size_t i = 0; i < itens.size(); ++i) {
            std::string linha;
            if ((int)i == _indiceSubmenuSelecionado) {
                linha = "> " + itens[i].getNome() + " (x" + std::to_string(itens[i].getQuantidade()) + ")";
            } else {
                linha = "  " + itens[i].getNome() + " (x" + std::to_string(itens[i].getQuantidade()) + ")";
            }
            linha += "  -  " + itens[i].getDescricao();

            sf::Text t(linha, _fonte, 16);
            t.setPosition(75.0f, 510.0f + (float)i * 32.0f);

            if ((int)i == _indiceSubmenuSelecionado) {
                t.setFillColor(sf::Color(100, 220, 255));
            } else {
                t.setFillColor(sf::Color(200, 210, 225));
            }
            _textosSubmenu.push_back(t);
        }
    }
}

void BatalhaGUI::executarTurnoInimigo() {
    if (_questao.isResolvida() || _questao.getVidaResolucao() <= 0) {
        if (_indiceQuestaoAtual + 1 < _questoes.size()) {
            _aguardandoAvancoQuestao = true;
            _textoMensagemLog1.setString("QUESTAO RESOLVIDA! Pressione ENTER para a proxima questao.");
            _textoMensagemLog2.setString("");
        } else {
            _resultado = ResultadoBatalha::VITORIA;
            _batalhaConcluida = true;
            _textoMensagemLog1.setString("PROVA CONCLUIDA COM SUCESSO! Parabens pela aprovacao nesta prova!");
            _textoMensagemLog2.setString("Pressione ENTER para retornar a sala de aula.");
        }
        atualizarBarras();
        return;
    }

    _questao.executarAcaoInimiga(&_jogador);
    _textoMensagemLog2.setString("A questao contra-atacou! +" + std::to_string(_questao.getdanoContraAtaque()) + " de cansaco.");

    atualizarBarras();

    if (_jogador.getCansaco() >= 100) {
        _resultado = ResultadoBatalha::DERROTA;
        _batalhaConcluida = true;
        _textoMensagemLog1.setString("DERROTA! O estudante desmaiou de cansaco!");
        _textoMensagemLog2.setString("Pressione ENTER para finalizar.");
    }
}

void BatalhaGUI::avancarParaProximaQuestao() {
    if (_indiceQuestaoAtual + 1 < _questoes.size()) {
        _indiceQuestaoAtual++;
        _questao = _questoes[_indiceQuestaoAtual];
        _vidaInicial = _questao.getVidaResolucao();
        _aguardandoAvancoQuestao = false;
        _batalhaConcluida = false;
        _resultado = ResultadoBatalha::EM_ANDAMENTO;
        _modo = ModoBatalha::ACOES_PRINCIPAIS;

        _textoMensagemLog1.setString("Nova questao da prova iniciada!");
        _textoMensagemLog2.setString("Aplique as habilidades correspondentes para avancar.");
        atualizarEnunciado();
        atualizarBarras();
    }
}

void BatalhaGUI::processarEventos(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    // Se estiver aguardando avanço de questão
    if (_aguardandoAvancoQuestao) {
        if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
            avancarParaProximaQuestao();
        }
        return;
    }

    // Se a batalha já acabou, espera Enter/Espaço para fechar
    if (_batalhaConcluida) {
        return;
    }

    // --- MODO 1: SELECIONANDO HABILIDADE ---
    if (_modo == ModoBatalha::SELECIONANDO_HABILIDADE) {
        const auto& habs = _jogador.getHabilidades();
        int total = (int)habs.size();

        if (evento.key.code == sf::Keyboard::Escape) {
            _modo = ModoBatalha::ACOES_PRINCIPAIS;
            return;
        }

        if (total > 0) {
            if (evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up ||
                evento.key.code == sf::Keyboard::A || evento.key.code == sf::Keyboard::Left) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado - 1 + total) % total;
                atualizarSubmenu();
            } else if (evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down ||
                       evento.key.code == sf::Keyboard::D || evento.key.code == sf::Keyboard::Right) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado + 1) % total;
                atualizarSubmenu();
            } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
                const auto& hab = habs[_indiceSubmenuSelecionado];
                if (hab.afetaInimigo()) {
                    hab.aplicarEfeito(_questao);
                    _questao.concluirEtapaPrevia();
                    _textoMensagemLog1.setString("Voce usou " + hab.getNome() + "! Causou " + std::to_string(hab.getEfeitoValor()) + " de progresso.");
                } else {
                    hab.aplicarEfeito(_jogador);
                    _textoMensagemLog1.setString("Voce usou " + hab.getNome() + "! Reduziu o cansaco em " + std::to_string(hab.getEfeitoValor()) + " pontos.");
                }

                _modo = ModoBatalha::ACOES_PRINCIPAIS;

                // Verifica se a questão já foi vencida pelo dano
                if (_questao.getVidaResolucao() <= 0) {
                    _questao.concluirEtapaPrevia();
                    _questao.tentarFinalizar();
                    executarTurnoInimigo();
                } else {
                    executarTurnoInimigo();
                }
            }
        }
        return;
    }

    // --- MODO 2: SELECIONANDO ITEM ---
    if (_modo == ModoBatalha::SELECIONANDO_ITEM) {
        const auto& itens = _jogador.getItens();
        int total = (int)itens.size();

        if (evento.key.code == sf::Keyboard::Escape) {
            _modo = ModoBatalha::ACOES_PRINCIPAIS;
            return;
        }

        if (total > 0) {
            if (evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado - 1 + total) % total;
                atualizarSubmenu();
            } else if (evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado + 1) % total;
                atualizarSubmenu();
            } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
                std::string nomeItem = itens[_indiceSubmenuSelecionado].getNome();
                std::string tipoItem = itens[_indiceSubmenuSelecionado].getTipoEfeito();

                if (tipoItem == "DICA") {
                    _textoMensagemLog1.setString("DICA DO LIVRO: " + _questao.fornecerDica());
                    _textoMensagemLog2.setString("Consultar o livro de dicas nao consome turno!");
                    _jogador.usarItem(_indiceSubmenuSelecionado);
                    _modo = ModoBatalha::ACOES_PRINCIPAIS;
                } else {
                    _jogador.usarItem(_indiceSubmenuSelecionado);
                    _textoMensagemLog1.setString("Voce usou " + nomeItem + "! Cansaco reduzido.");
                    _modo = ModoBatalha::ACOES_PRINCIPAIS;
                    executarTurnoInimigo();
                }

                if (_indiceSubmenuSelecionado >= (int)_jogador.getItens().size()) {
                    _indiceSubmenuSelecionado = std::max(0, (int)_jogador.getItens().size() - 1);
                }
            }
        }
        return;
    }

    // --- MODO 0: ACOES PRINCIPAIS ---
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
        if (_indiceAcaoSelecionada == 0) {
            // 1. Abrir lista de Habilidades
            _modo = ModoBatalha::SELECIONANDO_HABILIDADE;
            _indiceSubmenuSelecionado = 0;
            atualizarSubmenu();
        } else if (_indiceAcaoSelecionada == 1) {
            // 2. Abrir Inventário de Itens
            _modo = ModoBatalha::SELECIONANDO_ITEM;
            _indiceSubmenuSelecionado = 0;
            atualizarSubmenu();
        } else if (_indiceAcaoSelecionada == 2) {
            // 3. Pedir Dica (não gasta turno)
            _textoMensagemLog1.setString("DICA DO STEWART: " + _questao.fornecerDica());
            _textoMensagemLog2.setString("Consultar suas anotacoes nao consome turno!");
        } else if (_indiceAcaoSelecionada == 3) {
            // 4. Tentar Finalizar
            if (_questao.tentarFinalizar()) {
                _textoMensagemLog1.setString("Substituicao Direta e Fechamento executados com perfeicao!");
                if (_indiceQuestaoAtual + 1 < _questoes.size()) {
                    _aguardandoAvancoQuestao = true;
                    _textoMensagemLog2.setString("QUESTAO RESOLVIDA! Pressione ENTER para a proxima questao.");
                } else {
                    _resultado = ResultadoBatalha::VITORIA;
                    _batalhaConcluida = true;
                    _textoMensagemLog2.setString("PROVA CONCLUIDA COM SUCESSO! Pressione ENTER.");
                }
                atualizarBarras();
            } else {
                _textoMensagemLog1.setString("Nao foi possivel finalizar! Conclua as etapas com Habilidades primeiro.");
                executarTurnoInimigo();
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

    // Se estiver em modo de ação principal
    if (_modo == ModoBatalha::ACOES_PRINCIPAIS) {
        for (auto& btn : _botoesAcao) {
            btn.renderizar(janela);
        }
        janela.draw(_textoInstrucaoTeclado);
    } else {
        // Se estiver em submenu de Habilidade ou Item
        janela.draw(_painelSubmenu);
        janela.draw(_tituloSubmenu);
        for (const auto& itemTxt : _textosSubmenu) {
            janela.draw(itemTxt);
        }
    }
}

bool BatalhaGUI::isBatalhaConcluida() const {
    return _batalhaConcluida;
}

ResultadoBatalha BatalhaGUI::getResultado() const {
    return _resultado;
}
