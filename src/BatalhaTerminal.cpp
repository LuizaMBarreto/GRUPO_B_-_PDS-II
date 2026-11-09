#include "BatalhaTerminal.hpp"
#include "Excecoes.hpp"
#include <iostream>

BatalhaTerminal::BatalhaTerminal(Jogador& jogador, const Prova& prova, int numeroProva)
    : _jogador(jogador),
      _questoes(prova.getQuestoes()),
      _numeroProva(numeroProva),
      _indiceQuestaoAtual(0) {
    if (_questoes.empty()) {
        throw IndiceInvalidoException("A prova nao contem questoes para a batalha.");
    }
}

const Questao& BatalhaTerminal::getQuestaoAtual() const {
    if (_indiceQuestaoAtual >= _questoes.size()) {
        throw IndiceInvalidoException("Indice de questao fora dos limites da prova.");
    }
    return _questoes[_indiceQuestaoAtual];
}

Questao& BatalhaTerminal::getQuestaoAtual() {
    if (_indiceQuestaoAtual >= _questoes.size()) {
        throw IndiceInvalidoException("Indice de questao fora dos limites da prova.");
    }
    return _questoes[_indiceQuestaoAtual];
}

size_t BatalhaTerminal::getIndiceQuestaoAtual() const {
    return _indiceQuestaoAtual;
}

int BatalhaTerminal::getNumeroProva() const {
    return _numeroProva;
}

bool BatalhaTerminal::isProvaConcluida() const {
    return _indiceQuestaoAtual >= _questoes.size();
}

bool BatalhaTerminal::avancarQuestao() {
    if (_indiceQuestaoAtual + 1 < _questoes.size()) {
        _indiceQuestaoAtual++;
        return true;
    }
    return false;
}

void BatalhaTerminal::executarContraAtaque(std::ostream& out) {
    if (isProvaConcluida()) return;
    Questao& q = getQuestaoAtual();
    if (q.isResolvida()) return;

    q.executarAcaoInimiga(&_jogador);
    out << "A questao contra-atacou! +" << q.getdanoContraAtaque()
        << " de cansaco no estudante.\n";

    if (_jogador.getCansaco() >= 100) {
        out << "\n[!] ALERTA CRITICO: O estudante atingiu " << _jogador.getCansaco()
            << " pontos de cansaco e desmaiou!\n";
    }
}

bool BatalhaTerminal::usarHabilidade(size_t indiceHabilidade, std::ostream& out) {
    const auto& habs = _jogador.getHabilidades();
    if (indiceHabilidade >= habs.size()) {
        out << "Indice de habilidade invalido!\n";
        return false;
    }

    const Habilidade& hab = habs[indiceHabilidade];
    Questao& q = getQuestaoAtual();

    // Habilidade de suporte (ex: Pausa para o Café)
    if (!hab.afetaInimigo()) {
        hab.aplicarEfeito(_jogador);
        out << "\nVoce usou '" << hab.getNome() << "'!\n";
        out << "Efeito: Cansaco reduzido em " << hab.getEfeitoValor()
            << " pontos. Cansaco atual: " << _jogador.getCansaco() << " / 100\n";
        executarContraAtaque(out);
        return true;
    }

    // Regras de compatibilidade temática matemática (Stewart):
    // Prova 1 (Limites): "Fatoracao Algebrica", "Multiplicar Conjugado", "Regra de L'Hopital"
    // Prova 2 (Derivadas): "Regra da Cadeia", "Regra de L'Hopital"
    // Prova 3 (Integrais): "Integracao por Partes"
    // Prova 4 (Geral): Todas as habilidades aplicáveis
    bool compativel = false;
    std::string nomeHab = hab.getNome();

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
        hab.aplicarEfeito(q);
        q.concluirEtapaPrevia();
        out << "\n[SUCESSO] Habilidade compativel com o topico da questao!\n";
        out << "Voce aplicou '" << nomeHab << "' causando "
            << hab.getEfeitoValor() << " de progresso na resolucao.\n";

        // Exibe a transformação algébrica da equação conforme a técnica aplicada
        if (nomeHab == "Fatoracao Algebrica") {
            out << "Desenvolvimento: Fatorando (x^2 - 9) = (x - 3)(x + 3) e cancelando (x - 3):\n";
            q.setEquacao("lim (x -> 3) [ x + 3 ]");
            out << "Nova Equacao Simplificada: " << q.getEquacao() << "\n";
        } else if (nomeHab == "Multiplicar Conjugado") {
            out << "Desenvolvimento: Multiplicando por (sqrt(t^2 + 9) + 3)/(sqrt(t^2 + 9) + 3) e simplificando t^2:\n";
            q.setEquacao("lim (t -> 0) [ 1 / (sqrt(t^2 + 9) + 3) ]");
            out << "Nova Equacao Simplificada: " << q.getEquacao() << "\n";
        } else if (nomeHab == "Regra da Cadeia") {
            out << "Desenvolvimento: Aplicando d/dx[u^4] = 4*u^3 * u', onde u = 3x^2 - 5x + 2 e u' = 6x - 5:\n";
            q.setEquacao("f'(x) = 4 * (6x - 5) * (3x^2 - 5x + 2)^3");
            out << "Nova Expressao Derivada: " << q.getEquacao() << "\n";
        } else if (nomeHab == "Integracao por Partes") {
            out << "Desenvolvimento: Escolhendo u = x, dv = sin(x)dx --> du = dx, v = -cos(x):\n";
            out << "Aplicando integral(u dv) = uv - integral(v du) = -x*cos(x) - integral(-cos(x) dx):\n";
            q.setEquacao("-x * cos(x) + integral(cos(x) dx)");
            out << "Nova Expressao da Integral: " << q.getEquacao() << "\n";
        } else if (nomeHab == "Regra de L'Hopital") {
            out << "Desenvolvimento: Forma 0/0 detectada. Derivando numerador e denominador separadamente:\n";
            q.setEquacao("lim (x -> 0) [ 2 / cos(x) ]");
            out << "Nova Equacao Simplificada: " << q.getEquacao() << "\n";
        }

        out << "Vida restante da questao: " << q.getVidaResolucao() << " HP\n";
        out << "Status: Etapa previa concluida! Agora voce pode tentar finalizar (opcao 4*).\n";
    } else {
        // Técnica matematicamente incorreta/incompatível
        int danoReduzido = 5;
        q.receberDanoResolucao(danoReduzido);
        out << "\n[AVISO] Tecnica matematicamente incompativel para este problema!\n";
        out << "'" << nomeHab << "' causou apenas " << danoReduzido
            << " de progresso residual por esforco bruto.\n";
        out << "Penalidade: +10 de cansaco extra por confusao teorica.\n";
        _jogador.alterarCansaco(10);
        out << "A etapa previa continua pendente. Consulte as Dicas (opcao 3) se tiver duvida.\n";
    }

    if (q.isResolvida() || q.getVidaResolucao() == 0) {
        out << "\n[VITORIA NA QUESTAO] A vida da questao chegou a 0 HP! Questao resolvida!\n";
    } else {
        executarContraAtaque(out);
    }

    return true;
}

bool BatalhaTerminal::usarItem(size_t indiceItem, std::ostream& out) {
    const auto& itens = _jogador.getItens();
    if (indiceItem >= itens.size()) {
        out << "Indice de item invalido!\n";
        return false;
    }

    Item item = itens[indiceItem]; // Cópia das informações antes do uso
    std::string nomeItem = item.getNome();
    std::string tipoEfeito = item.getTipoEfeito();
     if (item.getQuantidade() <= 0) {
        out << "\nVoce nao tem mais '" << nomeItem << "'! Colete mais para poder usar.\n";
        return false;
    }

    if (tipoEfeito == "CURA_ENERGIA") {
        _jogador.usarItem(indiceItem);
        out << "\n[ITEM USADO] Voce tomou '" << nomeItem << "'!\n";
        out << "Efeito: Reduziu 20 pontos de cansaco. Cansaco atual: "
            << _jogador.getCansaco() << " / 100\n";
        executarContraAtaque(out);
    } else if (tipoEfeito == "DICA") {
        Questao& q = getQuestaoAtual();
        _jogador.usarItem(indiceItem);
        out << "\n[ITEM USADO] Voce consultou o '" << nomeItem << "'!\n";
        out << "Stewart (Anotacao revelada): \"" << q.fornecerDica() << "\"\n";
        out << "(Consultar as anotacoes nao consome turno da batalha)\n";
    } else {
        _jogador.usarItem(indiceItem);
        out << "\nVoce usou '" << nomeItem << "'.\n";
        executarContraAtaque(out);
    }

    return true;
}

void BatalhaTerminal::exibirEstadoAtual(std::ostream& out) const {
    const Questao& q = getQuestaoAtual();

    out << "\n========================================\n";
    out << "PROVA " << _numeroProva << " - QUESTAO " << (_indiceQuestaoAtual + 1)
        << " DE " << _questoes.size() << "\n";
    out << "========================================\n";
    out << "Enunciado: " << q.getAssunto() << "\n";
    if (!q.getEquacao().empty()) {
        out << "Equacao:   " << q.getEquacao() << "\n";
    }
    out << "Vida da Questao: " << q.getVidaResolucao() << " HP\n";
    out << "Cansaco do Estudante: " << _jogador.getCansaco() << " / 100\n";
    out << "----------------------------------------\n";
    out << "1. Habilidades | 2. Itens | 3. Dicas | "
        << (q.isProntaParaFinalizar() ? "4. Finalizar*" : "4. Finalizar") << "\n";
    out << "----------------------------------------\n";
    out << "Escolha uma opcao (1-4): ";
}

void BatalhaTerminal::processarOpcao(int opcao, std::ostream& out) {
    const Questao& q = getQuestaoAtual();

    if (opcao == 1) {
        out << "\n--- LISTA DE HABILIDADES ---\n";
        const auto& habs = _jogador.getHabilidades();
        if (habs.empty()) {
            out << "Nenhuma habilidade disponivel.\n";
        } else {
            for (size_t i = 0; i < habs.size(); ++i) {
                out << (i + 1) << ". " << habs[i].getNome()
                    << " (" << (habs[i].afetaInimigo() ? "Dano: " : "Reduz Cansaco: ")
                    << habs[i].getEfeitoValor() << " pts)"
                    << " - " << habs[i].getDescricao() << "\n";
            }
            out << "Digite o numero da habilidade para usar (ou 0 para apenas voltar): ";
        }
    } else if (opcao == 2) {
        out << "\n--- LISTA DE ITENS ---\n";
        const auto& itens = _jogador.getItens();
        if (itens.empty()) {
            out << "Nenhum item no inventario.\n";
        } else {
            for (size_t i = 0; i < itens.size(); ++i) {
                out << (i + 1) << ". " << itens[i].getNome()
                    << " (x" << itens[i].getQuantidade() << ")"
                    << " - " << itens[i].getDescricao() << "\n";
            }
            out << "Digite o numero do item para usar (ou 0 para apenas voltar): ";
        }
    } else if (opcao == 3) {
        out << "\n--- DICA DA QUESTAO ---\n";
        out << "Stewart: \"" << q.fornecerDica() << "\"\n";
    } else if (opcao == 4) {
        out << "\n--- VERIFICACAO DE FINALIZACAO ---\n";
        if (q.isProntaParaFinalizar()) {
            out << "Status: E possivel finalizar a questao agora! (Etapa previa concluida)\n";
        } else {
            out << "Status: Nao e possivel finalizar ainda. Conclua as etapas previas com habilidades primeiro.\n";
        }
    } else {
        out << "\nOpcao invalida! Digite 1, 2, 3 ou 4.\n";
    }
}

void BatalhaTerminal::executarLoop(std::istream& in, std::ostream& out) {
    int opcao = 0;
    while (!isProvaConcluida()) {
        exibirEstadoAtual(out);
        if (!(in >> opcao)) {
            break;
        }

        if (opcao == 1) {
            processarOpcao(1, out);
            int habEscolhida = 0;
            if (in >> habEscolhida && habEscolhida > 0) {
                usarHabilidade(static_cast<size_t>(habEscolhida - 1), out);
            }
        } else if (opcao == 2) {
            processarOpcao(2, out);
            int itemEscolhido = 0;
            if (in >> itemEscolhido && itemEscolhido > 0) {
                usarItem(static_cast<size_t>(itemEscolhido - 1), out);
            }
        } else if (opcao == 4) {
            processarOpcao(4, out);
            Questao& q = getQuestaoAtual();
            if (q.isProntaParaFinalizar()) {
                q.tentarFinalizar();
                out << "[SUCESSO] Fechamento e Substituicao Direta realizados! Questao finalizada com exito!\n";

                // Exibe a avaliação final da equação
                std::string assunto = q.getAssunto();
                if (assunto.find("Polinomial") != std::string::npos) {
                    out << "Conclusao: Substituindo x = 3 em (x + 3) --> 3 + 3 = 6\n";
                    out << "Resultado Final da Equacao: L = 6\n";
                } else if (assunto.find("Racionalizacao") != std::string::npos) {
                    out << "Conclusao: Substituindo t = 0 em 1/(sqrt(0 + 9) + 3) = 1/(3 + 3) = 1/6\n";
                    out << "Resultado Final da Equacao: L = 1/6\n";
                } else if (assunto.find("Cadeia") != std::string::npos) {
                    out << "Conclusao: Expressao da derivada completamente fatorada e simplificada.\n";
                    out << "Resultado Final: f'(x) = 4(6x - 5)(3x^2 - 5x + 2)^3\n";
                } else if (assunto.find("Quociente") != std::string::npos) {
                    out << "Conclusao: Numerador expandido (6x + 3) - (6x - 2) = 5.\n";
                    out << "Resultado Final: g'(x) = 5 / (2x + 1)^2\n";
                } else if (assunto.find("Partes") != std::string::npos) {
                    out << "Conclusao: Integrando cos(x)dx obtemos sin(x) + C.\n";
                    out << "Resultado Final: -x * cos(x) + sin(x) + C\n";
                } else if (assunto.find("Substituicao") != std::string::npos) {
                    out << "Conclusao: Integrando sqrt(u)du = (2/3)u^(3/2) e voltando u = 1 + e^x:\n";
                    out << "Resultado Final: (2/3) * (1 + e^x)^(3/2) + C\n";
                } else if (assunto.find("L'Hopital") != std::string::npos) {
                    out << "Conclusao: Substituindo x = 0 em 2/cos(0) = 2/1 = 2.\n";
                    out << "Resultado Final da Equacao: L = 2\n";
                } else {
                    out << "Resultado Final: Integral avaliada com sucesso (+ C adicionada).\n";
                }
            }
        } else {
            processarOpcao(opcao, out);
        }

        Questao& qAtual = getQuestaoAtual();
        if (qAtual.isResolvida() || qAtual.getVidaResolucao() == 0) {
            if (_indiceQuestaoAtual + 1 < _questoes.size()) {
                out << "\n[!] Avancando para a proxima questao da prova...\n";
                avancarQuestao();
            } else {
                out << "\n========================================\n";
                out << "TODAS AS QUESTOES DA PROVA FORAM CONCLUIDAS COM SUCESSO!\n";
                out << "========================================\n";
                break;
            }
        }

        if (_jogador.getCansaco() >= 100) {
            out << "\n[FIM DE JOGO] Estudante reprovado por exaustao!\n";
            break;
        }

        out << "\nPressione Enter ou digite 0 para continuar (qualquer outro numero para sair): ";
        int cont = 0;
        if (!(in >> cont) || cont != 0) {
            break;
        }
    }
}
