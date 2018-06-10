#include "../include/territorio.hpp"


#include<iostream>
void  Territorio::setPosicao(int x,int y){
	posicao[0]=x;
	posicao[1]=y;
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
void Territorio::addExercito(Civilizacao & civil,int i,int j){
	Exercito *newExercito=new Exercito(i,j);
	civil.adicionarExercito(newExercito);
	this->ocupado=true;
	this->dono=civil.getId();
}
void Territorio::destruirExercito(Civilizacao & civil){
	civil.removerExercito(endereco);
}
//metodo que tira a referencia ao exercito e deixa o territorio livre
void Territorio::desocupar(){
	endereco=nullptr;
	ocupado=false;
}
Exercito *Territorio::getEndereco(){
	return endereco;
}