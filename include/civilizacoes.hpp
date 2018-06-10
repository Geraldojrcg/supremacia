#ifndef CIVILIZACAO_HPP_INCLUDED
#define CIVILIZACAO_HPP_INCLUDED
#include <string>
#include <iostream>
#include <list>
#include "exercito.hpp"
class Civilizacao{
private:
	std::string rei;// nome do rei(definido pelo jogador, username).
	std::list<Exercito*> exercitos;//lista contendo os exercitos do jogador
	int ouro;//quantida de ouro da cavilizacao
	int soldadosLivres;
	int id=0;//1 for player,other for cpu, zero for void
public:
	Civilizacao();
	Civilizacao(std::string userName);
	~Civilizacao()=default;
	void setRei(std::string rei);
	std::string getRei();
	int getOuro();
	void addOuro(int quantidade_de_ouro);
	int getSoldadosLivres();
	void addSoldado(int qtd);
	void setId(int id);
	int getId();
	//exercito
	void adicionarExercito(Exercito *newExercito);
	void removerExercito(Exercito *exercito);

};
#endif
