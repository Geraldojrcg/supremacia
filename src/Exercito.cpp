#include "../include/exercito.hpp"


Exercito::Exercito(int x,int y){
	posicao[0]=x;
	posicao[1]=y;
}
int Exercito::qtdDeSoldados(){
	return soldados.size();
}
void Exercito::adicionarSoldado(Soldado *newSoldado){
	soldados.push_back(newSoldado);
}
void Exercito::removerSoldado(){
	soldados.pop_back();
}