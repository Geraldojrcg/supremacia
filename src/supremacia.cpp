#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/button.hpp"
#include <random>
#include <cmath>

int main(){
    int w_width = 800;
    int w_height = 620;
    //creating window
    sf::RenderWindow renderWindow(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
    
    //loading fonts
    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    
    //creating label
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::Black);
    text.setCharacterSize(20);
    text.setPosition(300, 10);
    text.setString("Supremacia the game");
   
    //color
    sf::Color color(sf::Color::Black);
    
    //textura do territorio/acoes
    sf::Texture t1, t2;
    t1.loadFromFile("sprites/territorio.png");
    t2.loadFromFile("sprites/painel_acoes.png");
    //sprite do territorio/acoes
    sf::Sprite territorio(t1);
    territorio.setPosition(10, 10);
    sf::Sprite p_acoes(t2);
    p_acoes.setPosition(10, 420);

    //music
    sf::Music music;
    if(!music.openFromFile("sound/sound.ogg"))
        return -1; // error
    music.play();

    //button
    Button mover("Mover", sf::Vector2f(20, 430), 35, nullptr, sf::Color(0, 0, 200));
    //mover.move(20, 430);
    Button c_soldado("Comprar Soldados", sf::Vector2f(20, 480), 35, nullptr, sf::Color(0, 0, 200));
    //c_soldado.move(20, 460);

    while (renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (renderWindow.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::EventType::Closed){
                music.stop();
                renderWindow.close();
            }
            mover.update(event);
            c_soldado.update(event);
        }
        renderWindow.clear(color);
        renderWindow.draw(text);
        renderWindow.draw(territorio);
        renderWindow.draw(p_acoes);
        renderWindow.draw(mover);
        renderWindow.draw(c_soldado);
        renderWindow.display();
    }  
        
    return 0;
}

