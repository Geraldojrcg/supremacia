#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include <SFML/Graphics.hpp>
#include <iostream>
#define MAX_NUMBER_OF_ITENS 3
class Menu{
private:
	int selectionItemIndex;
	sf::Font font;
	sf::Text menu[MAX_NUMBER_OF_ITENS];
public:
	Menu(float widht,float height);
	~Menu()=default;
	int getSelectionItemIndex();
	void draw(sf::RenderWindow &window);
	void moveUp();
	void moveDown();
};

#endif
