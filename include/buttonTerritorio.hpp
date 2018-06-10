#ifndef BUTTONTERRITORIO_HPP_INCLUDED
#define BUTTONTERRITORIO_HPP_INCLUDED
//classe criada para direncia o tipo do botao e as chamadas de ponteros de funcoes
class ButtonTerritorio{
private:
    int positionX;
    int positionY;
    int pressOn;
public:
	int type=0;
	int getPressOn();
	void setPressOn(int press);
	int getPositionX();
	void setPositionX(int i);
	int getPositionY();
	void setPositionY(int j);
};


#endif