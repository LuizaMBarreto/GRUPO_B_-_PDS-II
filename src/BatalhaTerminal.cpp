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

size_t BatalhaTerminal::getIndiceQuestaoAtual() const {
    return _indiceQuestaoAtual;
}

int BatalhaTerminal::getNumeroProva() const {
    return _numeroProva;
}

void BatalhaTerminal::exibirEstadoAtual(std::ostream& out) const {
    const Questao& q = getQuestaoAtual();

    out << "\n========================================\n";
    out << "PROVA " << _numeroProva << " - QUESTAO " << (_indiceQuestaoAtual + 1)
        << " DE " << _questoes.size() << "\n";
    out << "========================================\n";
    out << "Enunciado: " << q.getAssunto() << "\n";
    out << "Dificuldade: " << q.getDificuldade()
        << " | Vida da Questao: " << q.getVidaResolucao() << " HP\n";
    out << "Cansaco do Estudante: " << _jogador.getCansaco() << " / 100\n";
    out << "----------------------------------------\n";
    out << "1. Habilidades\n";
    out << "2. Itens\n";
    out << "3. Dicas\n";
    out << "4. Finalizar\n";
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
    while (true) {
        exibirEstadoAtual(out);
        if (!(in >> opcao)) {
            break;
        }
        processarOpcao(opcao, out);
        out << "\nPressione Enter ou digite 0 para continuar explorando as opcoes (qualquer outra entrada sai): ";
        int cont = 0;
        if (!(in >> cont) || cont != 0) {
            break;
        }
    }
}
