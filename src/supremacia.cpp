#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/button.hpp"
#include <random>
#include <cmath>

int main(){
    int w_width = 800;
    int w_height = 600;
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
    //initializing event
    sf::Event event;
    //color
    sf::Color color(sf::Color::White);
    //button
    Button play("Jogar", sf::Vector2f(0 , w_height/2), 30, nullptr, sf::Color(50, 200, 50));
    play.move(w_width/2 - play.getRightX()/2, 0);

    const int nofRows = 10; //number of rows
    const int nofCols = 10; //number of columns
    const int distance = 50; //distance between dots
    const float offset = distance/2.f; //offset for odd rows
    const float height = std::sqrt(std::pow(distance,2.f) - std::pow(offset,2.f)); //height of triangles
    //matriz de botoes
    std::vector<std::vector<Button>> dot;
    //("O", sf::Vector2f(0 ,100), 30, nullptr, sf::Color(50, 200, 50));

    //music
    sf::Music music;
    if(!music.openFromFile("sound/sound.ogg"))
        return -1; // error
    music.play();

    while (renderWindow.isOpen()){
    // Check for all the events that occured since the last frame.
        while (renderWindow.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::EventType::Closed){
                music.stop();
                renderWindow.close();
            }
           
        }
        renderWindow.clear(color);
        renderWindow.draw(text);
       /* for (int i=0; i<nofRows; ++i){
            for (int j=0; j<nofCols; ++j){
                dot[i][j] = Button("O", sf::Vector2f(j*distance+offset ,i*height), 30, nullptr, sf::Color(50, 200, 50));
                //dot[i][j].setPosition(j*distance+offset, i*height); //odd rows
                dot[i][j].update(event);
                renderWindow.draw(dot[i][j]);
            }
        }*/
        renderWindow.display();
    }  
        
    return 0;
}

