#include "../include/territorio.hpp"



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
