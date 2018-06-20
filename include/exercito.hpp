#ifndef EXERCITO_HPP_INCLUDED
#define EXERCITO_HPP_INCLUDED
#include <string>
#include "soldado.hpp"
#include <iostream>
#include <list>

class Exercito{
public:
	int posicao[2];
	std::list<Soldado*> soldados;//deu ruim sendo private
	bool found;
	int iaExercito=0;
public:
	Exercito()=default;
	Exercito(int x,int y);
	~Exercito()=default;
	int qtdDeSoldados();
	int getForcaDoExercito();
	void adicionarSoldado(Soldado *newSoldado);
	void removerSoldado(Soldado* soldado);
	Soldado* SoldDead(int media);
};

#endif
