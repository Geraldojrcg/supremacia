#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/button.hpp"
#include "../include/menu.hpp"
#include <random>
#include <cmath>
#include <string>

#include"civilizacoes.hpp"
#include"global.hpp"

sf::RenderWindow renderWindow;
sf::RenderWindow window_c_soldado;
sf::RenderWindow window;
sf::RenderWindow infos;
sf::RenderWindow Exercito_options;

//matriz de botoes

Button terras[8][8];
//initiaze civilization
Civilizacao CivilPlayer;

bool game_window_open = false;

int qtd_soldados_comprados = 0;

    //load music theme menu
sf::Music music;


void start_game();
void initializing_player_infos();
void initializing_player_infos_exit();

void quit_game(){
    renderWindow.close();
    std::_Exit(EXIT_FAILURE);
}
void continue_game(){
    
}
void initiaze_game(){
    window.close();
    music.stop();
    initializing_player_infos(); 
}
void comprou_soldado(){
    if(CivilPlayer.getOuro()>=10){
        CivilPlayer.addSoldado(1);
        CivilPlayer.addOuro(-10);
    }else{
        //TODO:msn se nao conseguir comprar
    }
    
}
void exit_game(){
    int w_width = 300;
    int w_height = 200;
    sf::RenderWindow window_exit(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
    Button sair("Sair", sf::Vector2f(w_height/2, w_height/2), 40, quit_game, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(w_width/5, 10);
    text.setString("Deseja Realmente Sair?");

    while (window_exit.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (window_exit.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
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
    //se ouro < nao pode comprar
     window_c_soldado.close();
}
void comprar_soldado_window(){
    int w_width = 350;
    int w_height = 200;

    window_c_soldado.create(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);

    //botoes
    std::string test;
    test=std::to_string(qtd_soldados_comprados);
    Button comprar("+", sf::Vector2f(140, 10), 30, comprou_soldado, sf::Color(200, 0, 0));
    Button fechar("voltar", sf::Vector2f(100, w_height/2), 30, comprar_soldado_window_exit, sf::Color(200, 0, 0));


    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("SOLDADOS (0)");
    //infos de custo de soldados
    sf::Text text2;
    text2.setFont(font);
    text2.setColor(sf::Color::White);
    text2.setCharacterSize(20);
    text2.setPosition(10, 40);
    text2.setString("custo por soldado : 10 ouros");
    //qtd de ouro
    sf::Text text3;
    text3.setFont(font);
    text3.setColor(sf::Color::White);
    text3.setCharacterSize(20);
    text3.setPosition(10, 70);
    std::string ouro;
    ouro=std::to_string(CivilPlayer.getOuro());
    text3.setString("Quantidade de ouro : "+ouro);

    //input
    sf::String playerInput;
    sf::Text qtd_soldado;
    qtd_soldado.setFont(font);
    qtd_soldado.setColor(sf::Color::White);
    qtd_soldado.setCharacterSize(20);
    qtd_soldado.setPosition(w_width/2, w_height/4);


    while (window_c_soldado.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (window_c_soldado.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                window_c_soldado.close();
            }
            window_c_soldado.clear();
            comprar.update(event);
            fechar.update(event);
        }

        window_c_soldado.clear();
        //window_c_soldado.draw(rectangle);
        window_c_soldado.draw(text);
        window_c_soldado.draw(text2);
        window_c_soldado.draw(text3);
        window_c_soldado.draw(qtd_soldado);
        window_c_soldado.draw(comprar);
        window_c_soldado.draw(fechar);
        window_c_soldado.display();
        //atualizando os textos 
        ouro=std::to_string(CivilPlayer.getOuro());
        text3.setString("Quantidade de ouro : "+ouro);
        std::string test2;
        test2=std::to_string(CivilPlayer.getSoldadosLivres());
        test2="soldados ("+test2+")";
        text.setString(test2);
    }
}
void add_exercito(int i,int j){
    if((i==0 && j == 6)||(i==1 && j == 6)||(i==1 && j == 7)){
        terras[i][j].changeColor(sf::Color(0, 0, 255));
    }else{
        //TODO:avisar que nao pode adicionar
    }
}
void terras_options(int i,int j){
    int w_width = 350;
    int w_height = 200;

    Exercito_options.create(sf::VideoMode(w_width, w_height), "terreno", sf::Style::Titlebar + sf::Style::Close);

    //botoes
    std::string test;
    test=std::to_string(qtd_soldados_comprados);
    Button adicionar("adicionar", sf::Vector2f(50, 50), 30, add_exercito,i,j, sf::Color(200, 0, 0));
    Button voltar("voltar", sf::Vector2f(50, w_height/2), 30, comprar_soldado_window_exit, sf::Color(200, 0, 0));



    sf::Font font;
    font.loadFromFile("font/arial.ttf");


    while (Exercito_options.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (Exercito_options.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                Exercito_options.close();
            }
            Exercito_options.clear();
            voltar.update(event);
            adicionar.update(event);
        }

        Exercito_options.clear();
        Exercito_options.draw(voltar);
        Exercito_options.draw(adicionar);
        Exercito_options.display();

    }
}
void Move(){
    int w_width = 400;
    int w_height = 400;

    infos.create(sf::VideoMode(w_width, w_height), "Exercito", sf::Style::Titlebar + sf::Style::Close);
    /*sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w_width,w_height));
    rectangle.setFillColor(sf::Color(250,250,250));
    rectangle.setPosition(0,0);*/

    //botoes
    Button fechar("CONFIRMAR", sf::Vector2f(100, w_height/2), 30, initializing_player_infos_exit, sf::Color(200, 0, 0));


    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("digite o seu nome : ");

    //input
    sf::String playerInput;
    sf::Text qtd_soldado;
    qtd_soldado.setFont(font);
    qtd_soldado.setColor(sf::Color::White);
    qtd_soldado.setCharacterSize(20);
    qtd_soldado.setPosition(w_width/2, w_height/4);


    while (infos.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (infos.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                infos.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == '\b' && playerInput.getSize()>0) { // handle backspace explicitly
                     playerInput.erase(playerInput.getSize() - 1, 1);
                }
                else{
                        playerInput += static_cast<char>(event.text.unicode);
                        qtd_soldado.setString(playerInput);
                    }
            }
            infos.clear();
            fechar.update(event);
        }

        infos.clear();
        //window_c_soldado.draw(rectangle);
        infos.draw(text);
        infos.draw(qtd_soldado);
        infos.draw(fechar);
        infos.display();

    }

    std::string s = qtd_soldado.getString();
    CivilPlayer.setRei(s);
    infos.close();
    start_game();
}
void teste(){
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
    text_info.setColor(sf::Color::White);
    text_info.setCharacterSize(30);
    text_info.setPosition(440, 20);
    text_info.setString("Informacoes");

    //rei
    sf::Text text_rei_name;
    text_rei_name.setFont(font);
    text_rei_name.setColor(sf::Color::White);
    text_rei_name.setCharacterSize(20);
    text_rei_name.setPosition(440, 80);
    text_rei_name.setString("Rei : "+CivilPlayer.getRei());
    //QTD ouro
    sf::Text text_qtd_ouro;
    text_qtd_ouro.setFont(font);
    text_qtd_ouro.setColor(sf::Color::White);
    text_qtd_ouro.setCharacterSize(20);
    text_qtd_ouro.setPosition(440, 120);
    std::string ouro;
    ouro=std::to_string(CivilPlayer.getOuro());
    text_qtd_ouro.setString("Quantidade de ouro : "+ouro);
    //quantidade de soldados em tropa e livres
    sf::Text text_sol_livre;
    text_sol_livre.setFont(font);
    text_sol_livre.setColor(sf::Color::White);
    text_sol_livre.setCharacterSize(20);
    text_sol_livre.setPosition(440, 160);
    std::string sol;
    sol=std::to_string(CivilPlayer.getSoldadosLivres());
    text_sol_livre.setString("Soldados fora de combate  : "+sol);
    //botoes
    Button sair("Sair", sf::Vector2f(480, 580), 30, exit_game, sf::Color(200, 0, 0));

    //teste de tamanho de botao
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(mapa[i][j].getDono()==1){
                terras[i][j].startTerrasBotton(sf::Vector2f(6+i*50, 11+j*50), 47, terras_options,i,j, sf::Color(0, 0, 255));
            }
            else if(mapa[i][j].getDono()==2){
                terras[i][j].startTerrasBotton(sf::Vector2f(6+i*50, 11+j*50), 47, terras_options,i,j, sf::Color(255, 0, 0));
            }else{
                terras[i][j].startTerrasBotton(sf::Vector2f(6+i*50, 11+j*50), 47, terras_options,i,j, sf::Color(107, 142, 35));
            }
        }
    }
    //game window music music
    sf::Music music;
    music.setLoop(true);
    if(!music.openFromFile("sound/Fantascape.ogg"))
        std::_Exit(EXIT_FAILURE); // error
    music.play();

    while (renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (renderWindow.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                music.stop();
                renderWindow.close();
            }
            mover.update(event);
            c_soldado.update(event);
            sair.update(event);
            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    terras[i][j].update(event);
                }
            }
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
        renderWindow.draw(text_rei_name);
        renderWindow.draw(text_qtd_ouro);
        renderWindow.draw(text_sol_livre);
        renderWindow.draw(sair);
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                renderWindow.draw(terras[i][j]);
            }
        }
        //atualizando valores na tela
        ouro=std::to_string(CivilPlayer.getOuro());
        text_qtd_ouro.setString("Quantidade de ouro : "+ouro);
        sol=std::to_string(CivilPlayer.getSoldadosLivres());
        text_sol_livre.setString("Soldados fora de combate  : "+sol);
        renderWindow.display();

    }


}
void menu(){
    window.create(sf::VideoMode(800, 600), "joguinho!");
    Menu menu(window.getSize().x,window.getSize().y);
    //load background
    sf::Texture texture;
    if (!texture.loadFromFile("sprites/bg.png")){
    }
    sf::Sprite background(texture);
    //music
    music.openFromFile("sound/sound.ogg");

    //botoes
    Button iniciar(" INICIAR ", sf::Vector2f(50, 400), 50, initiaze_game, sf::Color(200, 0, 0));
    Button continuar("CONTINUAR", sf::Vector2f(250, 450), 50, continue_game, sf::Color(200, 0, 0));
    Button sair("  SAIR   ", sf::Vector2f(515, 500), 50, quit_game, sf::Color(200, 0, 0));

    music.play();
    music.setLoop(true);
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
            iniciar.update(event);
            continuar.update(event);
            sair.update(event);
        }
        window.clear();
        window.draw(background);
        window.draw(iniciar);
        window.draw(sair);
        window.draw(continuar);
        //menu.draw(window);
        window.display();
    }
}
void initializing_player_infos_exit(){
    infos.close();
}
void initializing_player_infos(){
    int w_width = 350;
    int w_height = 200;

    infos.create(sf::VideoMode(w_width, w_height), "Supremacia Demo", sf::Style::Titlebar + sf::Style::Close);
    /*sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w_width,w_height));
    rectangle.setFillColor(sf::Color(250,250,250));
    rectangle.setPosition(0,0);*/

    //botoes
    Button fechar("CONFIRMAR", sf::Vector2f(100, w_height/2), 30, initializing_player_infos_exit, sf::Color(200, 0, 0));


    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("digite o seu nome : ");

    //input
    sf::String playerInput;
    sf::Text qtd_soldado;
    qtd_soldado.setFont(font);
    qtd_soldado.setColor(sf::Color::White);
    qtd_soldado.setCharacterSize(20);
    qtd_soldado.setPosition(w_width/2, w_height/4);


    while (infos.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (infos.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                infos.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                if(event.text.unicode == '\b' && playerInput.getSize()>0) { // handle backspace explicitly
                     playerInput.erase(playerInput.getSize() - 1, 1);
                }
                else{
                        playerInput += static_cast<char>(event.text.unicode);
                        qtd_soldado.setString(playerInput);
                    }
            }
            infos.clear();
            fechar.update(event);
        }

        infos.clear();
        //window_c_soldado.draw(rectangle);
        infos.draw(text);
        infos.draw(qtd_soldado);
        infos.draw(fechar);
        infos.display();

    }

    std::string s = qtd_soldado.getString();
    CivilPlayer.setRei(s);
    infos.close();
    start_game();
}
void Setposicoes(){//setando as posiçoes
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            mapa[i][j].setPosicao(i,j);
        }
    }
}
int main(){

    //logica dos territorios s
    //alocando a matriz mapa
    mapa=new Territorio*[8];
    for(int i=0;i<8;i++){
        mapa[i]=new Territorio[8];
    }
    Setposicoes();
    //definindo player como dono da posicao (0,7) obs player=1, cpu =2
    mapa[0][7].setDono(1);

    menu();
    //start_game();
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

