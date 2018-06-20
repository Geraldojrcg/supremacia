#ifndef TERRITORIO_HPP_INCLUDED
#define TERRITORIO_HPP_INCLUDED
#include "civilizacoes.hpp"


class Territorio{
private:
	int qtd_de_ouro;
	bool tem_ouro=true;
	int dono;
	bool ocupado=false;
public:
	Exercito *endereco; 
public:
	Territorio()=default;
	Exercito *getEndereco();
	void SetQtdOuro(int ouro);
	void setDono(int newDono);
	int getDono();
	int getQtdDeOuro();
	void changeOuro();
	bool HaveOuro();
	int getOuro();
	//opcoes de exercito
	void desocupar();
	bool Ocupado();
	void colocarExercito(Exercito *exercito,int id);
	void addExercito(Civilizacao *civil);
	void addExercitoIa(Civilizacao *civil,int i,int j);
	void destruirExercito();
	~Territorio()=default;
};

#endif
