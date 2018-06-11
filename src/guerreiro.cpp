#include "../include/guerreiro.hpp"

#include<stdlib.h>
#include <time.h>

Guerreiro::Guerreiro(){
	srand(time(nullptr));
	forca=15;
	preco=10;
}
