
#include"territorio.hpp"



Territorio **mapa;


//variaveis globais da IA
int warnning[8][8];//matriz onde estao os inimigos proximos(IA CODE)

int direcao[4];// se 0 bloco na direção esta vazio se 1 esta cheio,legenda >> 0 = direita.1 = esquerda,2 = cima,3 = baixo;
int numeroDeInimigos[4];// legenda >> 0 = direita.1 = esquerda,2 = cima,3 = baixo;


