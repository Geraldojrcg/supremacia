#ifndef WORLD
#define WORLD
#include <SFML/Graphics.hpp>
class world : public sf::Drawable, public sf::Transformable{
    public:
        world();
    private:
        int qtd_ouro;
        int id_dono;

};
#endif