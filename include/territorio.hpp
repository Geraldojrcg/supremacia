#ifndef TERRITORIO_HPP_INCLUDED
#define TERRITORIO_HPP_INCLUDED
#include "civilizacoes.hpp"


class Territorio{
private:
	int qtd_de_ouro;
	int dono;
	bool ocupado=false;
	
	int posicao[2];
public:
	Exercito *endereco; 
	Territorio()=default;
	Exercito *getEndereco();
	void setPosicao(int x,int y);
	bool Ocupado();
	void setDono(int newDono);
	int getDono();
	void desocupar();
	void colocarExercito(Exercito *exercito,int id);
	void addExercito(Civilizacao *civil,int i,int j);
	void destruirExercito();
	~Territorio()=default;
};

#endif
