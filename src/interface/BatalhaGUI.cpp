#include "../../include/interface/BatalhaGUI.hpp"
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
      _aguardandoAvancoQuestao(false),
      _aguardandoEncerramentoBatalha(false) {

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
    _caixaDialogo.setPosition(50.0f, 310.0f);
    _caixaDialogo.setSize(sf::Vector2f(larguraJanela - 100.0f, 135.0f));
    _caixaDialogo.setFillColor(sf::Color(25, 30, 44));
    _caixaDialogo.setOutlineThickness(2.0f);
    _caixaDialogo.setOutlineColor(sf::Color(120, 140, 180));

    _textoMensagemLog1.setFont(_fonte);
    _textoMensagemLog1.setCharacterSize(16);
    _textoMensagemLog1.setFillColor(sf::Color(255, 230, 130)); // Amarelo
    _textoMensagemLog1.setString("A prova comeca! Selecione uma Habilidade ou Item abaixo.");
    _textoMensagemLog1.setPosition(70.0f, 320.0f);

    _textoMensagemLog2.setFont(_fonte);
    _textoMensagemLog2.setCharacterSize(15);
    _textoMensagemLog2.setFillColor(sf::Color(130, 225, 255)); // Ciano claro
    _textoMensagemLog2.setString("");
    _textoMensagemLog2.setPosition(70.0f, 355.0f);

    _textoMensagemLog3.setFont(_fonte);
    _textoMensagemLog3.setCharacterSize(15);
    _textoMensagemLog3.setFillColor(sf::Color(240, 150, 150)); // Vermelho claro / Rosa alerta
    _textoMensagemLog3.setString("");
    _textoMensagemLog3.setPosition(70.0f, 395.0f);

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

    // Botões de Ação na base da tela (Navegáveis via teclado A/D, W/S ou números 1-4)
    float larguraBtn = 205.0f;
    float alturaBtn = 50.0f;
    float yBtns = 500.0f;
    float espacoBtn = 225.0f;
    float xInicial = 50.0f;

    _botoesAcao.emplace_back(xInicial, yBtns, larguraBtn, alturaBtn, "1. Habilidades", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn, yBtns, larguraBtn, alturaBtn, "2. Itens", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn * 2.0f, yBtns, larguraBtn, alturaBtn, "3. Dicas", _fonte, 18);
    _botoesAcao.emplace_back(xInicial + espacoBtn * 3.0f, yBtns, larguraBtn, alturaBtn, "4. Finalizar", _fonte, 18);

    _botoesAcao[0].setSelecionado(true);

    // Instruções de controle por teclado
    _textoInstrucaoTeclado.setFont(_fonte);
    _textoInstrucaoTeclado.setCharacterSize(15);
    _textoInstrucaoTeclado.setFillColor(sf::Color(140, 160, 190));
    _textoInstrucaoTeclado.setString("[1-4 ou A/D/W/S: Navegar]  |  [ENTER/ESPACO: Executar]  |  [ESC: Cancelar]");
    _textoInstrucaoTeclado.setPosition(larguraJanela / 2.0f - 270.0f, 620.0f);

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
        nomeProva + "  (Questao " + std::to_string(atual) + " de " + std::to_string(total) + ")\n\n" 
        + "(Dificuldade " + std::to_string(_questao.getDificuldade()) + ")" +
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

    // 3. Atualiza indicador de finalização no botão 4
    if (_botoesAcao.size() > 3) {
        _botoesAcao[3].setTexto(_questao.isProntaParaFinalizar() ? "4. Finalizar*" : "4. Finalizar");
    }
}

void BatalhaGUI::atualizarSubmenu() {
    _textosSubmenu.clear();

    if (_modo == ModoBatalha::SELECIONANDO_HABILIDADE) {
        _tituloSubmenu.setString("SELECIONE A HABILIDADE MATEMATICA [W/S ou 1-9: Escolher | ENTER: Aplicar | ESC: Voltar]");
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
                linha = "> " + std::to_string(i + 1) + ". " + habs[i].getNome();
            } else {
                linha = "  " + std::to_string(i + 1) + ". " + habs[i].getNome();
            }

            if (habs[i].afetaInimigo()) {
                linha += "  [-" + std::to_string(habs[i].getEfeitoValor()) + " HP] (" + habs[i].getDescricao() + ")";
            } else {
                linha += "  [-" + std::to_string(habs[i].getEfeitoValor()) + " Cansaco] (" + habs[i].getDescricao() + ")";
            }

            sf::Text t(linha, _fonte, 15);
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
        _tituloSubmenu.setString("INVENTARIO DE ITENS [W/S ou 1-9: Escolher | ENTER: Consumir | ESC: Voltar]");
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
                linha = "> " + std::to_string(i + 1) + ". " + itens[i].getNome() + " (x" + std::to_string(itens[i].getQuantidade()) + ")";
            } else {
                linha = "  " + std::to_string(i + 1) + ". " + itens[i].getNome() + " (x" + std::to_string(itens[i].getQuantidade()) + ")";
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
            _textoMensagemLog3.setString("");
        } else {
            _resultado = ResultadoBatalha::VITORIA;
            _aguardandoEncerramentoBatalha = true;
            _textoMensagemLog1.setString("PROVA CONCLUIDA COM SUCESSO! Parabens pela aprovacao nesta prova!");
            _textoMensagemLog2.setString("Pressione ENTER para retornar a sala de aula.");
            _textoMensagemLog3.setString("");
        }
        atualizarBarras();
        return;
    }

    _questao.executarAcaoInimiga(&_jogador);
    _textoMensagemLog3.setString("A questao contra-atacou! +" + std::to_string(_questao.getdanoContraAtaque()) + " de cansaco no estudante.");

    atualizarBarras();

    if (_jogador.getCansaco() >= 100) {
        _resultado = ResultadoBatalha::DERROTA;
        _aguardandoEncerramentoBatalha = true;
        _textoMensagemLog1.setString("[FIM DE JOGO] Estudante reprovado por exaustao!");
        _textoMensagemLog2.setString("Cansaco atingiu 100 pontos.");
        _textoMensagemLog3.setString("Pressione ENTER para finalizar.");
    }
}

void BatalhaGUI::avancarParaProximaQuestao() {
    if (_indiceQuestaoAtual + 1 < _questoes.size()) {
        _indiceQuestaoAtual++;
        _questao = _questoes[_indiceQuestaoAtual];
        _vidaInicial = _questao.getVidaResolucao();
        _aguardandoAvancoQuestao = false;
        _aguardandoEncerramentoBatalha = false;
        _batalhaConcluida = false;
        _resultado = ResultadoBatalha::EM_ANDAMENTO;
        _modo = ModoBatalha::ACOES_PRINCIPAIS;

        _textoMensagemLog1.setString("Nova questao da prova iniciada!");
        _textoMensagemLog2.setString("Aplique as habilidades correspondentes para avancar.");
        _textoMensagemLog3.setString("");
        atualizarEnunciado();
        atualizarBarras();
    }
}

void BatalhaGUI::processarEventos(const sf::Event& evento) {
    if (evento.type != sf::Event::KeyPressed) return;

    // Se estiver aguardando confirmação final para encerrar a batalha (vitória ou derrota)
    if (_aguardandoEncerramentoBatalha) {
        if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
            _batalhaConcluida = true;
        }
        return;
    }

    // Se estiver aguardando avanço de questão
    if (_aguardandoAvancoQuestao) {
        if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
            avancarParaProximaQuestao();
        }
        return;
    }

    // Se a batalha já acabou, ignora novos inputs
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
            bool dispararHabilidade = false;

            if (evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up ||
                evento.key.code == sf::Keyboard::A || evento.key.code == sf::Keyboard::Left) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado - 1 + total) % total;
                atualizarSubmenu();
            } else if (evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down ||
                       evento.key.code == sf::Keyboard::D || evento.key.code == sf::Keyboard::Right) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado + 1) % total;
                atualizarSubmenu();
            } else if (evento.key.code >= sf::Keyboard::Num1 && evento.key.code <= sf::Keyboard::Num9) {
                int digito = evento.key.code - sf::Keyboard::Num1;
                if (digito < total) {
                    _indiceSubmenuSelecionado = digito;
                    dispararHabilidade = true;
                }
            } else if (evento.key.code >= sf::Keyboard::Numpad1 && evento.key.code <= sf::Keyboard::Numpad9) {
                int digito = evento.key.code - sf::Keyboard::Numpad1;
                if (digito < total) {
                    _indiceSubmenuSelecionado = digito;
                    dispararHabilidade = true;
                }
            } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
                dispararHabilidade = true;
            }

            if (dispararHabilidade) {
                const auto& hab = habs[_indiceSubmenuSelecionado];
                std::string nomeHab = hab.getNome();

                if (!hab.afetaInimigo()) {
                    hab.aplicarEfeito(_jogador);
                    _textoMensagemLog1.setString("Voce usou '" + nomeHab + "'!");
                    _textoMensagemLog2.setString("Cansaco reduzido em " + std::to_string(hab.getEfeitoValor()) + " pontos. Cansaco: " + std::to_string(_jogador.getCansaco()) + " / 100.");
                    _textoMensagemLog3.setString("");
                    _modo = ModoBatalha::ACOES_PRINCIPAIS;
                    executarTurnoInimigo();
                } else {
                    // Regras de compatibilidade temática matemática (Stewart):
                    // Prova 1 (Limites): "Fatoracao Algebrica", "Multiplicar Conjugado", "Regra de L'Hopital"
                    // Prova 2 (Derivadas): "Regra da Cadeia", "Regra de L'Hopital"
                    // Prova 3 (Integrais): "Integracao por Partes"
                    // Prova 4 (Geral): Todas as habilidades aplicáveis
                    bool compativel = false;
                    if (_numeroProva == 1) {
                        if (nomeHab == "Fatoracao Algebrica" || nomeHab == "Multiplicar Conjugado" || nomeHab == "Regra de L'Hopital") {
                            compativel = true;
                        }
                    } else if (_numeroProva == 2) {
                        if (nomeHab == "Regra da Cadeia" || nomeHab == "Regra de L'Hopital") {
                            compativel = true;
                        }
                    } else if (_numeroProva == 3) {
                        if (nomeHab == "Integracao por Partes") {
                            compativel = true;
                        }
                    } else {
                        // Prova 4 - Geral/Mista
                        compativel = true;
                    }

                    if (compativel) {
                        hab.aplicarEfeito(_questao);
                        _questao.concluirEtapaPrevia();
                        _textoMensagemLog1.setString("[SUCESSO] Habilidade compativel com o topico da questao!");

                        // Exibe a transformação algébrica da equação conforme a técnica aplicada
                        if (nomeHab == "Fatoracao Algebrica") {
                            _questao.setEquacao("lim (x -> 3) [ x + 3 ]");
                            _textoMensagemLog2.setString("Fatorando (x^2 - 9) = (x - 3)(x + 3) e cancelando (x - 3) -> lim (x -> 3) [ x + 3 ]");
                        } else if (nomeHab == "Multiplicar Conjugado") {
                            _questao.setEquacao("lim (t -> 0) [ 1 / (sqrt(t^2 + 9) + 3) ]");
                            _textoMensagemLog2.setString("Multiplicando pelo conjugado e simplificando t^2 -> lim (t -> 0) [ 1 / (sqrt(t^2+9)+3) ]");
                        } else if (nomeHab == "Regra da Cadeia") {
                            _questao.setEquacao("f'(x) = 4 * (6x - 5) * (3x^2 - 5x + 2)^3");
                            _textoMensagemLog2.setString("Regra da Cadeia: d/dx[u^4] = 4*u^3 * u' -> f'(x) = 4(6x - 5)(3x^2 - 5x + 2)^3");
                        } else if (nomeHab == "Integracao por Partes") {
                            _questao.setEquacao("-x * cos(x) + integral(cos(x) dx)");
                            _textoMensagemLog2.setString("Partes: u = x, dv = sin(x)dx -> -x*cos(x) + integral(cos(x) dx)");
                        } else if (nomeHab == "Regra de L'Hopital") {
                            _questao.setEquacao("lim (x -> 0) [ 2 / cos(x) ]");
                            _textoMensagemLog2.setString("Forma 0/0: Derivando numerador e denominador -> lim (x -> 0) [ 2 / cos(x) ]");
                        } else {
                            _textoMensagemLog2.setString("Voce aplicou '" + nomeHab + "' causando " + std::to_string(hab.getEfeitoValor()) + " de progresso.");
                        }

                        atualizarEnunciado();
                        _textoMensagemLog3.setString("Etapa previa concluida! Agora voce pode tentar finalizar (4*).");
                    } else {
                        // Técnica matematicamente incompatível
                        int danoReduzido = 5;
                        _questao.receberDanoResolucao(danoReduzido);
                        _jogador.alterarCansaco(10);
                        _textoMensagemLog1.setString("[AVISO] Tecnica matematicamente incompativel para este problema!");
                        _textoMensagemLog2.setString("'" + nomeHab + "' causou apenas 5 HP de progresso. Penalidade: +10 de cansaco!");
                        _textoMensagemLog3.setString("A etapa previa continua pendente. Consulte as Dicas (opcao 3).");
                    }

                    _modo = ModoBatalha::ACOES_PRINCIPAIS;

                    if (_questao.getVidaResolucao() <= 0) {
                        _questao.concluirEtapaPrevia();
                        _questao.tentarFinalizar();
                    }
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
            bool dispararItem = false;

            if (evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado - 1 + total) % total;
                atualizarSubmenu();
            } else if (evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down) {
                _indiceSubmenuSelecionado = (_indiceSubmenuSelecionado + 1) % total;
                atualizarSubmenu();
            } else if (evento.key.code >= sf::Keyboard::Num1 && evento.key.code <= sf::Keyboard::Num9) {
                int digito = evento.key.code - sf::Keyboard::Num1;
                if (digito < total) {
                    _indiceSubmenuSelecionado = digito;
                    dispararItem = true;
                }
            } else if (evento.key.code >= sf::Keyboard::Numpad1 && evento.key.code <= sf::Keyboard::Numpad9) {
                int digito = evento.key.code - sf::Keyboard::Numpad1;
                if (digito < total) {
                    _indiceSubmenuSelecionado = digito;
                    dispararItem = true;
                }
            } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
                dispararItem = true;
            }

            if (dispararItem) {
                std::string nomeItem = itens[_indiceSubmenuSelecionado].getNome();
                std::string tipoItem = itens[_indiceSubmenuSelecionado].getTipoEfeito();

                if (tipoItem == "DICA") {
                    _jogador.usarItem(_indiceSubmenuSelecionado);
                    _textoMensagemLog1.setString("[ITEM USADO] Stewart: \"" + _questao.fornecerDica() + "\"");
                    _textoMensagemLog2.setString("(Consultar o livro de dicas nao consome turno de combate)");
                    _textoMensagemLog3.setString("");
                    _modo = ModoBatalha::ACOES_PRINCIPAIS;
                } else if (tipoItem == "CURA_ENERGIA") {
                    _jogador.usarItem(_indiceSubmenuSelecionado);
                    _textoMensagemLog1.setString("[ITEM USADO] Voce tomou '" + nomeItem + "'!");
                    _textoMensagemLog2.setString("Efeito: Cansaco reduzido em 20 pontos. Cansaco: " + std::to_string(_jogador.getCansaco()) + " / 100.");
                    _textoMensagemLog3.setString("");
                    _modo = ModoBatalha::ACOES_PRINCIPAIS;
                    executarTurnoInimigo();
                } else {
                    _jogador.usarItem(_indiceSubmenuSelecionado);
                    _textoMensagemLog1.setString("Voce usou '" + nomeItem + "'.");
                    _textoMensagemLog2.setString("");
                    _textoMensagemLog3.setString("");
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
    bool dispararAcao = false;

    if (evento.key.code == sf::Keyboard::Num1 || evento.key.code == sf::Keyboard::Numpad1) {
        _indiceAcaoSelecionada = 0;
        dispararAcao = true;
    } else if (evento.key.code == sf::Keyboard::Num2 || evento.key.code == sf::Keyboard::Numpad2) {
        _indiceAcaoSelecionada = 1;
        dispararAcao = true;
    } else if (evento.key.code == sf::Keyboard::Num3 || evento.key.code == sf::Keyboard::Numpad3) {
        _indiceAcaoSelecionada = 2;
        dispararAcao = true;
    } else if (evento.key.code == sf::Keyboard::Num4 || evento.key.code == sf::Keyboard::Numpad4) {
        _indiceAcaoSelecionada = 3;
        dispararAcao = true;
    } else if (evento.key.code == sf::Keyboard::A || evento.key.code == sf::Keyboard::Left ||
               evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up) {
        _indiceAcaoSelecionada = (_indiceAcaoSelecionada - 1 + (int)_botoesAcao.size()) % (int)_botoesAcao.size();
    } else if (evento.key.code == sf::Keyboard::D || evento.key.code == sf::Keyboard::Right ||
               evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down) {
        _indiceAcaoSelecionada = (_indiceAcaoSelecionada + 1) % (int)_botoesAcao.size();
    } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
        dispararAcao = true;
    }

    for (size_t i = 0; i < _botoesAcao.size(); ++i) {
        _botoesAcao[i].setSelecionado((int)i == _indiceAcaoSelecionada);
    }

    if (dispararAcao) {
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
            // 3. Dicas (Stewart)
            _textoMensagemLog1.setString("DICA DO STEWART: \"" + _questao.fornecerDica() + "\"");
            _textoMensagemLog2.setString("Consultar suas anotacoes nao consome turno de combate.");
            _textoMensagemLog3.setString("");
        } else if (_indiceAcaoSelecionada == 3) {
            // 4. Finalizar
            if (_questao.isProntaParaFinalizar()) {
                _questao.tentarFinalizar();
                _textoMensagemLog1.setString("[SUCESSO] Fechamento e Substituicao Direta realizados!");

                // Avaliação final da equação correspondente ao desafio
                std::string assunto = _questao.getAssunto();
                std::string conclusao;
                if (assunto.find("Polinomial") != std::string::npos) {
                    conclusao = "Substituindo x = 3 em (x + 3) -> 3 + 3 = 6. Resultado Final: L = 6";
                } else if (assunto.find("Racionalizacao") != std::string::npos) {
                    conclusao = "Substituindo t = 0 em 1/(sqrt(9) + 3) = 1/6. Resultado Final: L = 1/6";
                } else if (assunto.find("Cadeia") != std::string::npos) {
                    conclusao = "Derivada fatorada: f'(x) = 4(6x - 5)(3x^2 - 5x + 2)^3";
                } else if (assunto.find("Quociente") != std::string::npos) {
                    conclusao = "Numerador expandido (6x + 3) - (6x - 2) = 5. Resultado: g'(x) = 5 / (2x + 1)^2";
                } else if (assunto.find("Partes") != std::string::npos) {
                    conclusao = "Integrando cos(x)dx -> Resultado: -x * cos(x) + sin(x) + C";
                } else if (assunto.find("Substituicao") != std::string::npos) {
                    conclusao = "Integrando sqrt(u)du = (2/3)u^(3/2) -> Resultado: (2/3)*(1 + e^x)^(3/2) + C";
                } else if (assunto.find("L'Hopital") != std::string::npos) {
                    conclusao = "Substituindo x = 0 em 2/cos(0) = 2/1 = 2. Resultado Final: L = 2";
                } else {
                    conclusao = "Resultado Final: Integral avaliada com sucesso (+ C adicionada).";
                }
                _textoMensagemLog2.setString(conclusao);

                if (_indiceQuestaoAtual + 1 < _questoes.size()) {
                    _aguardandoAvancoQuestao = true;
                    _textoMensagemLog3.setString("QUESTAO RESOLVIDA! Pressione ENTER para a proxima questao.");
                } else {
                    _resultado = ResultadoBatalha::VITORIA;
                    _aguardandoEncerramentoBatalha = true;
                    _textoMensagemLog3.setString("PROVA CONCLUIDA COM SUCESSO! Pressione ENTER.");
                }
                atualizarBarras();
            } else {
                _textoMensagemLog1.setString("[BLOQUEADO] Nao e possivel finalizar ainda!");
                _textoMensagemLog2.setString("Conclua a etapa previa com uma Habilidade compativel antes do fechamento.");
                _textoMensagemLog3.setString("");
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
    janela.draw(_textoMensagemLog3);

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
