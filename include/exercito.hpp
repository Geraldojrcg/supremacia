#ifndef EXERCITO_HPP_INCLUDED
#define EXERCITO_HPP_INCLUDED
#include <string>
#include "soldado.hpp"
#include <iostream>
#include <list>

class Exercito{
private:
	
	int posicao[2];
public:
	std::list<Soldado*> soldados;//deu ruim sendo public
public:
	Exercito()=default;
	Exercito(int x,int y);
	~Exercito()=default;
	int qtdDeSoldados();
	int getForcaDoExercito();
	void adicionarSoldado(Soldado *newSoldado);
	void removerSoldado(Soldado *soldado);
};

#endif
