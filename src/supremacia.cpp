#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/button.hpp"
#include <random>
#include <cmath>
#include <string>

sf::RenderWindow renderWindow;
sf::RenderWindow window_c_soldado;

bool game_window_open = false;

int qtd_soldados_comprados = 0;

void quit_game(){
    renderWindow.close();
    system("exit");
}

void exit_game(){
    int w_width = 300;
    int w_height = 200;
    sf::RenderWindow window_exit(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
    /*sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w_width,w_height));
    rectangle.setFillColor(sf::Color(250,250,250));
    rectangle.setPosition(0,0);*/
    Button sair("Sair", sf::Vector2f(w_height/2, w_height/2), 40, quit_game, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    
    //creating label
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(w_width/5, 10);
    text.setString("Deseja Realmente Sair?");

    while (window_exit.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (window_exit.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::EventType::Closed){
                window_exit.close();
            }
            sair.update(event);
        }
        window_exit.clear();
        //window_exit.draw(rectangle);
        window_exit.draw(text);
        window_exit.draw(sair);
        window_exit.display();
    }  
}
void comprar_soldado_window_exit(){
     window_c_soldado.close();
}
void comprar_soldado_window(){
    int w_width = 350;
    int w_height = 200;

    window_c_soldado.create(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
    /*sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w_width,w_height));
    rectangle.setFillColor(sf::Color(250,250,250));
    rectangle.setPosition(0,0);*/
    Button comprar("Comprar", sf::Vector2f(w_width/3, w_height/2), 30, comprar_soldado_window_exit, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    
    //creating label
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("Digite a quantidade de soldados :");

    //input
    sf::String playerInput;
    sf::Text qtd_soldado;
    qtd_soldado.setFont(font);
    qtd_soldado.setFillColor(sf::Color::White);
    qtd_soldado.setCharacterSize(20);
    qtd_soldado.setPosition(w_width/2, w_height/4);
    

    while (window_c_soldado.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (window_c_soldado.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::EventType::Closed){
                window_c_soldado.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == '\b' && playerInput.getSize()>0) { // handle backspace explicitly
                     playerInput.erase(playerInput.getSize() - 1, 1);
                } 
                else if(event.text.unicode > 47 && event.text.unicode < 58)
                    {
                        playerInput += static_cast<char>(event.text.unicode);
                        qtd_soldado.setString(playerInput);
                    }
            }
            window_c_soldado.clear();
            comprar.update(event);
        }

        window_c_soldado.clear();
        //window_c_soldado.draw(rectangle);
        window_c_soldado.draw(text);
        window_c_soldado.draw(qtd_soldado);
        window_c_soldado.draw(comprar);
        window_c_soldado.display();
    }  
    
    std::string s = qtd_soldado.getString();
    qtd_soldados_comprados = stoi(s);
    std::cout << s << std::endl;
}
void start_game(){
    game_window_open = true;
    int w_width = 800;
    int w_height = 620;
    //creating window
    renderWindow.create(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
    
    //loading fonts
    sf::Font font;
    font.loadFromFile("font/arial.ttf");
   
    //color
    sf::Color color(sf::Color::Black);
    
    //textura do territorio
    sf::Texture t1;
    t1.loadFromFile("sprites/territorio.png");
    //sprite do territorio
    sf::Sprite territorio(t1);
    territorio.setPosition(5, 10);

    //painel de acoes
    //painel
    sf::RectangleShape painel_acoes;
    painel_acoes.setSize(sf::Vector2f(395, 300));
    painel_acoes.setFillColor(sf::Color(150,0,0));
    painel_acoes.setPosition(10, 420);
    //botoes
    Button mover("Mover", sf::Vector2f(20, 440), 35, nullptr, sf::Color(10, 0, 0));
    //mover.move(20, 430);
    Button c_soldado("Comprar Soldados", sf::Vector2f(20, 490), 35, comprar_soldado_window, sf::Color(10, 0, 0));
    //c_soldado.move(20, 460);

    //painel de informações
    //painel
    sf::RectangleShape painel_info;
    painel_info.setSize(sf::Vector2f(370, 610));
    painel_info.setFillColor(sf::Color(100,0,0));
    painel_info.setPosition(420, 12);
    //labels
    sf::Text text_info;
    text_info.setFont(font);
    text_info.setFillColor(sf::Color::White);
    text_info.setCharacterSize(30);
    text_info.setPosition(440, 20);
    text_info.setString("Informacoes :");
    //civilização
    sf::Text text_civ_name;
    text_civ_name.setFont(font);
    text_civ_name.setFillColor(sf::Color::White);
    text_civ_name.setCharacterSize(20);
    text_civ_name.setPosition(440, 80);
    text_civ_name.setString("Civilizacao :");
    //rei
    sf::Text text_rei_name;
    text_rei_name.setFont(font);
    text_rei_name.setFillColor(sf::Color::White);
    text_rei_name.setCharacterSize(20);
    text_rei_name.setPosition(440, 120);
    text_rei_name.setString("Rei :");
    //QTD ouro
    sf::Text text_qtd_ouro;
    text_qtd_ouro.setFont(font);
    text_qtd_ouro.setFillColor(sf::Color::White);
    text_qtd_ouro.setCharacterSize(20);
    text_qtd_ouro.setPosition(440, 160);
    text_qtd_ouro.setString("Quantidade de ouro :");
    //QTD exercitos
    sf::Text text_qtd_exer;
    text_qtd_exer.setFont(font);
    text_qtd_exer.setFillColor(sf::Color::White);
    text_qtd_exer.setCharacterSize(20);
    text_qtd_exer.setPosition(440, 200);
    text_qtd_exer.setString("Quantidade de exercitos :");

    sf::Text text_qtd_exer_var;
    text_qtd_exer_var.setFont(font);
    text_qtd_exer_var.setFillColor(sf::Color::White);
    text_qtd_exer_var.setCharacterSize(20);
    text_qtd_exer_var.setPosition(700, 200);

    //botoes
    Button sair("Sair", sf::Vector2f(480, 580), 30, exit_game, sf::Color(200, 0, 0));

    //game window music music
    sf::Music music;
    if(!music.openFromFile("sound/sound.ogg"))
        std::_Exit(EXIT_FAILURE); // error
    //music.play();

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
            sair.update(event);
        }
        renderWindow.clear(color);
        //renderWindow.draw(text);
        // render territorio
        renderWindow.draw(territorio);
        // render painel acoes
        renderWindow.draw(painel_acoes);
        renderWindow.draw(mover);
        renderWindow.draw(c_soldado);
        // render painel info
        renderWindow.draw(painel_info);
        renderWindow.draw(text_info);
        renderWindow.draw(text_civ_name);
        renderWindow.draw(text_rei_name);
        renderWindow.draw(text_qtd_ouro);
        renderWindow.draw(text_qtd_exer);
        text_qtd_exer_var.setString(std::to_string((int)(qtd_soldados_comprados/10)));
        renderWindow.draw(text_qtd_exer_var);
        renderWindow.draw(sair);

        renderWindow.display();
    }  
        
    
}
int main(){
    start_game();
    /*int w_width = 370;
    int w_height = 200;
    sf::RenderWindow window_start(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
   
    Button start("Start", sf::Vector2f(w_height/2, w_height/2), 40, start_game, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    
    //creating label
    sf::Text text;
    text.setFont(font);
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("Supremacia - the game of stratege war");

    while (window_start.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (window_start.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::EventType::Closed){
                window_start.close();
            }
            start.update(event);
        }
        if(game_window_open)
            window_start.close();
        window_start.clear();
        //window_start.draw(rectangle);
        window_start.draw(text);
        window_start.draw(start);
        window_start.display();
    }*/
    return 0;
}

