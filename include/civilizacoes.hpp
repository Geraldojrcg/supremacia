#ifndef CIVILIZACAO_HPP_INCLUDED
#define CIVILIZACAO_HPP_INCLUDED
#include <string>
#include <iostream>
#include <list>
#include "exercito.hpp"
#include "territorio.hpp"
class Civilizacao{
private:
	std::string rei;// nome do rei(definido pelo jogador, username).
	std::list<Exercito*> exercitos;//lista contendo os exercitos do jogador
	std::list<Territorio*> Mapa;//lista contendo as infos dos territorios
	int ouro;//quantida de ouro da cavilizacao
	int soldadosLivres;
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
	//exercito
	void adicionarExercito(Exercito *newExercito);

};
#endif
