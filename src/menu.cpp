
#include "../include/menu.hpp"
Menu::Menu(float width,float height){
	if(!font.loadFromFile("font/Berry Rotunda.ttf")){
		std::cout<<"falha a carregar fonte"<<std::endl;
	}
	menu[0].setFont(font);
	menu[0].setColor(sf::Color::Red);
	menu[0].setString("INICIAR PARTIDA");
	menu[0].setPosition(sf::Vector2f(width/4,height/(MAX_NUMBER_OF_ITENS +1) *1));

	menu[1].setFont(font);
	menu[1].setColor(sf::Color::White);
	menu[1].setString("CONTINUAR PARTIDA");
	menu[1].setPosition(sf::Vector2f(width/4,height/(MAX_NUMBER_OF_ITENS +1) *2));

	menu[2].setFont(font);
	menu[2].setColor(sf::Color::White);
	menu[2].setString("SAIR ");
	menu[2].setPosition(sf::Vector2f(width/4,height/(MAX_NUMBER_OF_ITENS +1) *3));

	selectionItemIndex=0;
}
int Menu::getSelectionItemIndex(){
    return selectionItemIndex;
}
void Menu::draw(sf::RenderWindow &window){
	for(int i=0;i<MAX_NUMBER_OF_ITENS;i++){
		window.draw(menu[i]);
	}
}
void Menu::moveUp(){
	if(selectionItemIndex-1>=0){
		menu[selectionItemIndex].setColor(sf::Color::White);
		selectionItemIndex--;
		menu[selectionItemIndex].setColor(sf::Color::Red);
	}
}
void Menu::moveDown(){
	if(selectionItemIndex<2){
		menu[selectionItemIndex].setColor(sf::Color::White);
		selectionItemIndex++;
		menu[selectionItemIndex].setColor(sf::Color::Red);
	}
}
