#include "../include/civilizacoes.hpp"


Civilizacao::Civilizacao(){
	ouro=300;
	soldadosLivres=0;
}
Civilizacao::Civilizacao(std::string userName){
	rei=userName;
	ouro=1000;
	soldadosLivres=0;
}
void Civilizacao::setRei(std::string rei){
	this->rei=rei;
}
std::string Civilizacao::getRei(){
	return rei;
}
void Civilizacao::setOuro(int gold){
	this->ouro=gold;
}
int Civilizacao::getOuro(){
	return ouro;
}
void Civilizacao::addOuro(int quantidade_de_ouro){
	ouro+=quantidade_de_ouro;
}
void Civilizacao::setId(int id){
	this->id=id;
}
int Civilizacao::getId(){
	return id;
}
int Civilizacao::getSoldadosLivres(){
	return soldadosLivres;
}
void Civilizacao::addSoldado(int qtd){
	soldadosLivres+=qtd;
}