#include "../include/exercito.hpp"


Exercito::Exercito(int x,int y){
	posicao[0]=x;
	posicao[1]=y;
	Soldado *s=new Soldado;
	adicionarSoldado(s);
}
int Exercito::qtdDeSoldados(){
	return soldados.size();
}
void Exercito::adicionarSoldado(Soldado *newSoldado){
	soldados.push_back(newSoldado);
}
void Exercito::removerSoldado(Soldado* soldado){
	soldados.remove(soldado);
}
int Exercito::getForcaDoExercito(){
	int strMax=0;
	for(Soldado* aux : soldados){
		strMax+=aux->getForca();
	}
	return strMax;
}
Soldado* Exercito::SoldDead(int media){
	found =false;
	Soldado *aux;
	for(Soldado* s: soldados){
		if(s->getForca()<media){
			found = true;
			return s;
		}
	}
	return aux;
}