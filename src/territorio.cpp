#include "../include/territorio.hpp"


#include<iostream>
void  Territorio::SetQtdOuro(int ouro){
	qtd_de_ouro=ouro;
}
int Territorio::getQtdDeOuro(){
	int ouro=qtd_de_ouro;
	qtd_de_ouro=0;
	return ouro;
}
void Territorio::changeOuro(){//funcao que diz que o terreno nao possue mais ouro
	tem_ouro=false;
}
bool Territorio::HaveOuro(){
	if(qtd_de_ouro>0){
		return true;
	}else{
		return false;
	}
}
void Territorio::setDono(int newDono){
	dono=newDono;
}
int Territorio::getDono(){
	return dono;
}
bool Territorio::Ocupado(){
	if(ocupado){
		return true;
	}else{
		return false;
	}
}
//coloca um exercito ja existente
void Territorio::colocarExercito(Exercito *exercito,int id){
	this->endereco=exercito;
	this->ocupado=true;
	this->dono=id;
}
//adiciona um novo exercito
void Territorio::addExercito(Civilizacao *civil){
	Exercito *newExercito =new Exercito();
	this->endereco=newExercito;
	this->ocupado=true;
	this->dono=civil->getId();
}
void Territorio::destruirExercito(){
	delete endereco;
}
//metodo que tira a referencia ao exercito e deixa o territorio livre
void Territorio::desocupar(){
	endereco=nullptr;
	ocupado=false;
}
Exercito *Territorio::getEndereco(){
	return endereco;
}