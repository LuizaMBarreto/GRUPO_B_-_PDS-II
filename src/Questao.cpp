#include "Questao.hpp"
#include "Jogador.hpp"
#include <iostream>


Questao::Questao(std:: string assunto, int dificuldade,
int vidaResolucao, std::string dica):
  _assunto(assunto),
  _dificuldade(dificuldade),
  _vidaResolucao(vidaResolucao),
  _barraBonus(0),
  _resolvida(false),
  _dica (dica),
  _etapaPreviaConcluida(false){

}

std::string Questao::getAssunto() const{
	return _assunto;
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

//decrementa o dano da vida da questão e assegura que a questão não terá uma vida negativa
void Questao::receberDanoResolucao(int dano){
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

void Questao::executarAcaoInimiga(Jogador* jogador){
	//stub: Implementar após definir o comportamento com o grupo.
  (void)jogador;
}

bool Questao::tentarFinalizar(){
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
