#include "../include/exercito.hpp"


Exercito::Exercito(int x,int y){
	posicao[0]=x;
	posicao[1]=y;
	Soldado *s=new Soldado;
	adicionarSoldado(s);
}
int Exercito::qtdDeSoldados(){
	return soldados.size();//TODO: isso ta dando segmatation fault nao sei pq
	//return 1;
}
void Exercito::adicionarSoldado(Soldado *newSoldado){
	soldados.push_back(newSoldado);
}
void Exercito::removerSoldado(){
	soldados.pop_back();
}