#include "interface/Botao.hpp"

Botao::Botao(float x, float y, float largura, float altura,
             const std::string& texto, const sf::Font& fonte,
             unsigned int tamanhoFonte)
    : _corNormal(sf::Color(45, 52, 71)),
      _corHover(sf::Color(72, 84, 114)),
      _corAtivo(sf::Color(25, 30, 42)),
      _isHover(false),
      _selecionado(false) {

    _forma.setPosition(x, y);
    _forma.setSize(sf::Vector2f(largura, altura));
    _forma.setFillColor(_corNormal);
    _forma.setOutlineThickness(2.0f);
    _forma.setOutlineColor(sf::Color(140, 160, 200));

    _texto.setFont(fonte);
    _texto.setString(texto);
    _texto.setCharacterSize(tamanhoFonte);
    _texto.setFillColor(sf::Color::White);

    // Centraliza o texto no botão
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    _texto.setPosition(x + largura / 2.0f, y + altura / 2.0f);
}

void Botao::setSelecionado(bool selecionado) {
    _selecionado = selecionado;
    if (_selecionado) {
        _forma.setFillColor(_corHover);
        _forma.setOutlineColor(sf::Color(255, 215, 0)); // Dourado
        _forma.setOutlineThickness(3.0f);
        _texto.setFillColor(sf::Color(255, 240, 180));
    } else {
        _forma.setFillColor(_corNormal);
        _forma.setOutlineColor(sf::Color(140, 160, 200));
        _forma.setOutlineThickness(2.0f);
        _texto.setFillColor(sf::Color::White);
    }
}

bool Botao::isSelecionado() const {
    return _selecionado;
}

void Botao::atualizar(const sf::Vector2f& posicaoMouse) {
    if (_forma.getGlobalBounds().contains(posicaoMouse)) {
        _isHover = true;
        _forma.setFillColor(_corHover);
        _forma.setOutlineColor(sf::Color(255, 215, 0)); // Dourado no hover
    } else {
        _isHover = false;
        _forma.setFillColor(_corNormal);
        _forma.setOutlineColor(sf::Color(140, 160, 200));
    }
}

bool Botao::foiClicado(const sf::Vector2f& posicaoMouse, const sf::Event& evento) {
    if (_forma.getGlobalBounds().contains(posicaoMouse)) {
        if (evento.type == sf::Event::MouseButtonReleased &&
            evento.mouseButton.button == sf::Mouse::Left) {
            return true;
        }
    }
    return false;
}

void Botao::renderizar(sf::RenderWindow& janela) {
    janela.draw(_forma);
    janela.draw(_texto);
}

void Botao::setPosicao(float x, float y) {
    _forma.setPosition(x, y);
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    _texto.setPosition(x + _forma.getSize().x / 2.0f, y + _forma.getSize().y / 2.0f);
}

void Botao::setTexto(const std::string& texto) {
    _texto.setString(texto);
    sf::FloatRect bounds = _texto.getLocalBounds();
    _texto.setOrigin(bounds.left + bounds.width / 2.0f, bounds.top + bounds.height / 2.0f);
    _texto.setPosition(_forma.getPosition().x + _forma.getSize().x / 2.0f,
                       _forma.getPosition().y + _forma.getSize().y / 2.0f);
}

void Botao::setCores(sf::Color normal, sf::Color hover, sf::Color ativo) {
    _corNormal = normal;
    _corHover = hover;
    _corAtivo = ativo;
    _forma.setFillColor(_corNormal);
}
