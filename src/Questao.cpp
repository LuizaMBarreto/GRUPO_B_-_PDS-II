#include "Questao.hpp"
#include "Jogador.hpp"



Questao::Questao(std::string assunto, int dificuldade,
int vidaResolucao, std::string dica, int danoContraAtaque):
  _assunto(assunto),
  _nomeContraAtaque("Ataque da Questao"),
  _dificuldade(dificuldade),
  _vidaResolucao(vidaResolucao),
  _barraBonus(0),
  _resolvida(false),
  _dica(dica),
  _danoContraAtaque(danoContraAtaque),
  _habilidadesInimigo(),
  _etapaPreviaConcluida(false){

}

std::string Questao::getAssunto() const{
	return _assunto;
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
	  if (_resolvida || dano <= 0) {
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
		return;
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
		return false;
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
