#include "Questao.hpp"
#include "Jogador.hpp"
#include "Excecoes.hpp"



Questao::Questao(std::string assunto, int dificuldade,
int vidaResolucao, std::string dica, int danoContraAtaque, std::string equacao):
  _assunto(assunto),
  _equacao(equacao),
  _nomeContraAtaque("Ataque da Questao"),
  _dificuldade(dificuldade),
  _vidaResolucao(vidaResolucao),
  _barraBonus(0),
  _resolvida(false),
  _dica(dica),
  _danoContraAtaque(danoContraAtaque),
  _habilidadesInimigo(),
  _etapaPreviaConcluida(false){
	if(_vidaResolucao <= 0){
		throw ParametroInvalidoException("A vida da questão não pode ser negativa");
	}

	if(_dificuldade <1 || _dificuldade > 3){
		throw ParametroInvalidoException("A dificuldade não pode ultrapassar os parâmetros estabelecidos");
	}

}

std::string Questao::getAssunto() const{
	return _assunto;
}

std::string Questao::getEquacao() const{
	return _equacao;
}

void Questao::setEquacao(const std::string& novaEquacao){
	_equacao = novaEquacao;
}

std::string Questao::getNomeContraAtaque() const{
	return _nomeContraAtaque;
}

std::string Questao::NomeContraAtaque() const{
	return getNomeContraAtaque();
}

 int Questao::getDificuldade() const{
	return _dificuldade;
}

int Questao::getVidaResolucao() const{
	return _vidaResolucao;

}

int Questao::getBarraBonus() const{
	return _barraBonus;
}

bool Questao::isResolvida() const{
	return _resolvida;
}

std::string Questao::fornecerDica() const{
	return _dica;
}

int Questao::getdanoContraAtaque() const{
	return _danoContraAtaque;
}

bool Questao::bonusCompleto() const{
	return _barraBonus >= 100;
}

const std::vector<Habilidade>& Questao::getHabilidadesInimigo() const {
    return _habilidadesInimigo;
}


//decrementa o dano da vida da questão e assegura que a questão não terá uma vida negativa
void Questao::receberDanoResolucao(int dano){
    if (dano < 0) {
        throw ParametroInvalidoException("O dano não pode ser um valor negativo");
    }
    if (_resolvida || dano == 0) {
        return;
    }
	if(dano >= _vidaResolucao){
		_vidaResolucao = 0;
		_resolvida = true;
	}
	else{
		_vidaResolucao = _vidaResolucao - dano;
	}
}

void Questao::incrementarBonus(int pontos){
	  _barraBonus = _barraBonus + pontos;
	//	por enquanto esta correta
}

int Questao::getPontuacao() const{
	switch(_dificuldade){
		case 1:
			return 50;
		case 2:
			return 75;
		case 3:
			return 100;
		default:
			return 0;
		//fornece a pontuação recebida pelo jogador baseando-se no nível de dificuldade da função
	}
}


void Questao::executarAcaoInimiga(Jogador* jogador){
	if (jogador == nullptr){
		throw ParametroInvalidoException("Jogador não está alocado de forma adequada");
		
	}
	if (_resolvida){
		return;
	}
	jogador -> alterarCansaco(_danoContraAtaque);
}

void Questao::adicionarHabilidadeInimiga(
    const Habilidade& habilidade) {

    _habilidadesInimigo.push_back(habilidade);
}

void Questao::concluirEtapaPrevia() {
    _etapaPreviaConcluida = true;
}

void Questao::ConcluirEtapaPrevia() {
    concluirEtapaPrevia();
}

bool Questao::tentarFinalizar(){
	if(_resolvida){
		
		throw QuestaoJaResolvidaException("A questão ja foi resolvida");
	}
	
	if(_etapaPreviaConcluida){
		_vidaResolucao = 0;
		_resolvida = true;
		return true;
	}
	return false;
}

bool Questao::isProntaParaFinalizar() const{
	return _etapaPreviaConcluida;
}
