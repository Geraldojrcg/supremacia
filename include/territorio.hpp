#ifndef TERRITORIO_HPP_INCLUDED
#define TERRITORIO_HPP_INCLUDED



class Territorio{
private:
	int qtd_de_ouro;
	int dono;
	int posicao[2];
public:
	Territorio()=default;
	void setPosicao(int x,int y);
	void setDono(int newDono);
	int getDono();
	~Territorio()=default;
};

#endif
