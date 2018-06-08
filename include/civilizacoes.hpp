#ifndef CIVILIZACAO_HPP_INCLUDED
#define CIVILIZACAO_HPP_INCLUDED
#include <string>
#include <iostream>
#include <list>
#include "exercito.hpp"
#include "territorio.hpp"
class Civilizacao{
private:
	std::string nome;//nome da civilização. ex: romanos, persas e etc.
	std::string rei;// nome do rei(definido pelo jogador, username).
	std::list<Exercito> exercitos;//lista contendo os exercitos do jogador
	std::list<Territorio> Mapa;//lista contendo as infos dos territorios
public:
	Civilizacao(std::string nome,std::string userName);

};
#endif
