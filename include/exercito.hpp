#ifndef EXERCITO_HPP_INCLUDED
#define EXERCITO_HPP_INCLUDED
#include <string>
#include "soldado.hpp"
#include <iostream>
#include <list>

class Exercito{
private:
	std::list<Soldado*> soldados;
	int posicao[2];
public:
	Exercito(int x,int y);
	int qtdDeSoldados();
	void adicionarSoldado(Soldado *newSoldado);
	void removerSoldado();
};

#endif
