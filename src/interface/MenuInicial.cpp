#include "interface/MenuInicial.hpp"

MenuInicial::MenuInicial(float larguraJanela, float alturaJanela, const sf::Font& fonte)
    : _fonte(fonte), _indiceSelecionado(0) {

    // Fundo elegante escuro
    _fundo.setSize(sf::Vector2f(larguraJanela, alturaJanela));
    _fundo.setFillColor(sf::Color(18, 22, 34));

    // Título Principal
    _titulo.setFont(_fonte);
    _titulo.setString("CALCULO I");
    _titulo.setCharacterSize(56);
    _titulo.setFillColor(sf::Color(255, 215, 0)); // Dourado
    _titulo.setStyle(sf::Text::Bold);
    sf::FloatRect boundsT = _titulo.getLocalBounds();
    _titulo.setOrigin(boundsT.left + boundsT.width / 2.0f, boundsT.top + boundsT.height / 2.0f);
    _titulo.setPosition(larguraJanela / 2.0f, alturaJanela * 0.18f);

    // Subtítulo
    _subtitulo.setFont(_fonte);
    _subtitulo.setString("Derrote Cálculo I");
    _subtitulo.setCharacterSize(22);
    _subtitulo.setFillColor(sf::Color(180, 200, 230));
    sf::FloatRect boundsS = _subtitulo.getLocalBounds();
    _subtitulo.setOrigin(boundsS.left + boundsS.width / 2.0f, boundsS.top + boundsS.height / 2.0f);
    _subtitulo.setPosition(larguraJanela / 2.0f, alturaJanela * 0.27f);

    // Botões
    float btnLargura = 280.0f;
    float btnAltura = 55.0f;
    float btnX = (larguraJanela - btnLargura) / 2.0f;
    float btnYInicial = alturaJanela * 0.42f;
    float espacamento = 75.0f;

    _botoes.emplace_back(btnX, btnYInicial, btnLargura, btnAltura, "Novo Jogo", _fonte, 24);
    _botoes.emplace_back(btnX, btnYInicial + espacamento, btnLargura, btnAltura, "Carregar", _fonte, 24);
    _botoes.emplace_back(btnX, btnYInicial + espacamento * 2.0f, btnLargura, btnAltura, "Sair", _fonte, 24);

    // Primeiro botão começa selecionado
    _botoes[0].setSelecionado(true);

    // Rodapé
    _rodape.setFont(_fonte);
    _rodape.setString("[W/S ou Setas: Navegar]  |  [ENTER ou ESPACO: Confirmar]");
    _rodape.setCharacterSize(16);
    _rodape.setFillColor(sf::Color(140, 160, 190));
    sf::FloatRect boundsR = _rodape.getLocalBounds();
    _rodape.setOrigin(boundsR.left + boundsR.width / 2.0f, boundsR.top + boundsR.height / 2.0f);
    _rodape.setPosition(larguraJanela / 2.0f, alturaJanela * 0.92f);
}

AcaoMenu MenuInicial::processarEventos(const sf::Event& evento) {
    if (evento.type == sf::Event::KeyPressed) {
        if (evento.key.code == sf::Keyboard::W || evento.key.code == sf::Keyboard::Up) {
            _indiceSelecionado = (_indiceSelecionado - 1 + (int)_botoes.size()) % (int)_botoes.size();
            for (size_t i = 0; i < _botoes.size(); ++i) {
                _botoes[i].setSelecionado((int)i == _indiceSelecionado);
            }
        } else if (evento.key.code == sf::Keyboard::S || evento.key.code == sf::Keyboard::Down) {
            _indiceSelecionado = (_indiceSelecionado + 1) % (int)_botoes.size();
            for (size_t i = 0; i < _botoes.size(); ++i) {
                _botoes[i].setSelecionado((int)i == _indiceSelecionado);
            }
        } else if (evento.key.code == sf::Keyboard::Return || evento.key.code == sf::Keyboard::Space) {
            if (_indiceSelecionado == 0) return AcaoMenu::NOVO_JOGO;
            if (_indiceSelecionado == 1) return AcaoMenu::CARREGAR_JOGO;
            if (_indiceSelecionado == 2) return AcaoMenu::SAIR;
        }
    }
    return AcaoMenu::NENHUMA;
}

void MenuInicial::atualizar() {
}

void MenuInicial::renderizar(sf::RenderWindow& janela) {
    janela.draw(_fundo);
    janela.draw(_titulo);
    janela.draw(_subtitulo);
    janela.draw(_rodape);

    for (auto& btn : _botoes) {
        btn.renderizar(janela);
    }
}

