#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../include/button.hpp"
#include <random>
#include <cmath>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include<unistd.h> 
#include<stdio.h> 

#include"civilizacoes.hpp"
#include"global.hpp"
///GLOBAL DEACLARATIONS  
sf::RenderWindow renderWindow;
sf::RenderWindow window_c_soldado;
sf::RenderWindow window;
sf::RenderWindow infos;
sf::RenderWindow Exercito_options;
sf::RenderWindow Terras_options;
sf::RenderWindow alert;
sf::RenderWindow Alert_bool;

//matriz de botoes
Exercito *lastReferencia;
Button terras[8][8];
//initiaze civilization
Civilizacao CivilPlayer;
Civilizacao CivilIa;

bool game_window_open = false;

int qtd_soldados_comprados = 0;

//variavel bool alert sim ou nao
bool alertB=false;
//variavel que conta os movimentos do jogador
int mana;
    //load music theme menu
sf::Music music;
///iniciando itens referentes a IA
int exercitosDaIa[64][2];//matriz onde fica as informaçoes de quantos exercitos a ia possui e sua localizaoes
std::list<Exercito*> exercitosIa;
//endereços dos exercitos da ia
//1 
Exercito *ia1;
//2 
Exercito *ia2;
//3 
Exercito *ia3;
//3 
Exercito *ia4;

void start_game();
void initializing_player_infos();
void initializing_player_infos_exit();
void Mover(int i,int j);
void Mover_quit();
void exercito_options_quit();
void terras_options_quit();
void alert_window(int codigo);
void alert_quit();
void mover_ia(int i,int j);
void decisoes_ia();
void imprimir_matriz();
void menu();
void load_game();
void save_game();

void quit_game(){
    renderWindow.close();
    std::_Exit(EXIT_FAILURE);
    
}
void continue_game(){
    load_game();
    window.close();
    music.stop();
    mapa[7][7].setDono(2);
    mapa[0][0].setDono(1);
    start_game();
    
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
    //load background
    sf::Texture texture;
    if (!texture.loadFromFile("sprites/loja.png")){
    }
    sf::Sprite background(texture);
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
        window_exit.draw(background);
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

    window_c_soldado.create(sf::VideoMode(w_width, w_height), "Comprar soldados", sf::Style::Titlebar + sf::Style::Close);

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
void alert_bool_yes(){
    if(CivilPlayer.getOuro()>=100){
        CivilPlayer.addOuro(-100);
        alertB=true;
    }else{
        alert_window(1);//codigo 1 de decisao falha ao comprar exercito
        alertB=false;
    }
    Alert_bool.close();
}
void alert_bool_no(){
    alertB=false;
    Alert_bool.close();
}
void alert_bool(int codigo){//window of alert with decision
    //codigo é referente ao qual foi o porque do alerte, abaixo o tipos
    /*
    0 = adicionar exercito com o custo de 100 ouros
    */
    int w_width = 300;
    int w_height = 200;
    //botoes
    Alert_bool.create(sf::VideoMode(w_width, w_height), "ALERT", sf::Style::Titlebar + sf::Style::Close);
    Button sim("SIM", sf::Vector2f(10, w_height/2), 40, alert_bool_yes, sf::Color(200, 0, 0));
    Button nao("NAO", sf::Vector2f(190, w_height/2), 40, alert_bool_no, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    switch(codigo){
        case 0:
            text.setString("deseja adicionar \n exercito por \n 100 OUROS ?");
            break;
    }

    while (Alert_bool.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (Alert_bool.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                alertB=false;
                Alert_bool.close();
            }
            sim.update(event);
            nao.update(event);
        }
        Alert_bool.clear();
        Alert_bool.draw(text);
        Alert_bool.draw(sim);
        Alert_bool.draw(nao);
        Alert_bool.display();
    }
}
void add_exercito(int i,int j){//adiciona um novo exercito ao terreno
    alert_bool(0);
    if(alertB){
        mapa[i][j].addExercito(&CivilPlayer);
        terras[i][j].changeColor(sf::Color(0, 0, 255));
    }
    terras_options_quit();
}
void add_soldado(int i,int j){
    srand(time(nullptr));
    if(CivilPlayer.getSoldadosLivres()>0){
        Soldado *s=new Soldado();
        s->forca=(rand()%10)+3;
        mapa[i][j].endereco->adicionarSoldado(s);
        CivilPlayer.addSoldado(-1);
    }else{
        alert_window(0);//chamando a janela de alert pelo codigo 0
    }
    Exercito_options.close();
}
void coletar_ouro(int i,int j){
    if(mapa[i][j].HaveOuro()){
        mana--;
        CivilPlayer.addOuro(mapa[i][j].getQtdDeOuro());
    }else{
        alert_window(3);//informar que nao possui mais ouro ali
    }
    
    Exercito_options.close();
}
void exercito_options(int i,int j){
    int w_width = 350;
    int w_height = 400;
    Exercito_options.create(sf::VideoMode(w_width, w_height), "Exercito", sf::Style::Titlebar + sf::Style::Close);

    //botoes
    std::string test;
    test=std::to_string(qtd_soldados_comprados);
    Button coletar("coletar ouro", sf::Vector2f(50, 200), 30, coletar_ouro,i,j, sf::Color(200, 0, 0));
    Button adicionar("adicionar soldado", sf::Vector2f(50, 250), 30, add_soldado,i,j, sf::Color(200, 0, 0));
    Button mover("mover exercito", sf::Vector2f(50, 300), 30, Mover,i,j, sf::Color(200, 0, 0));
    Button voltar("voltar", sf::Vector2f(50, 350), 30, exercito_options_quit, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");

     //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("Numero de soldados : ");
    std::string numSold;


    sf::Text text2;
    text2.setFont(font);
    text2.setColor(sf::Color::White);
    text2.setCharacterSize(20);
    text2.setPosition(10, 40);
    std::string ouro;
    if(mapa[i][j].HaveOuro()){
        ouro="NAO";
    }else{
        ouro="SIM";
    }
    text2.setString("Ouro coletado : "+ouro);

    
    

    while (Exercito_options.isOpen() && renderWindow.isOpen()){

        numSold=std::to_string(mapa[i][j].endereco->qtdDeSoldados());
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (Exercito_options.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                Exercito_options.close();
            }
            Exercito_options.clear();
            mover.update(event);
            coletar.update(event);
            adicionar.update(event);
            voltar.update(event);
        }

        Exercito_options.clear();
        Exercito_options.draw(mover);
        Exercito_options.draw(coletar);
        Exercito_options.draw(adicionar);
        Exercito_options.draw(voltar);
        text.setString("Numero de soldados : "+numSold);
        Exercito_options.draw(text);
        //checa de a opcao ouro coletado mudou e atualiza
        if(mapa[i][j].HaveOuro()){
            ouro="NAO";
        }else{
            ouro="SIM";
        }
        text2.setString("Ouro coletado : "+ouro);
        Exercito_options.draw(text2);
        Exercito_options.display();

    }
}
void exercito_options_quit(){
    Exercito_options.close();
}
void terras_options_quit(){
    Terras_options.close();
}
void terras_options(int i,int j){
    int w_width = 350;
    int w_height = 200;
    if(mapa[i][j].Ocupado()){
        if(mapa[i][j].getDono()!=1){
            alert_window(4);///codigo 4 avisa que um inimigo esta ali
            return;
        }else{
            exercito_options(i,j);
            return;
        }
    }
    Terras_options.create(sf::VideoMode(w_width, w_height), "terreno", sf::Style::Titlebar + sf::Style::Close);

    //botoes
    std::string test;
    test=std::to_string(qtd_soldados_comprados);
    

    Button adicionar("Colocar exercito", sf::Vector2f(50, 50), 30, add_exercito,i,j, sf::Color(200, 0, 0));
    
    Button voltar("voltar", sf::Vector2f(50, w_height/2), 30, terras_options_quit, sf::Color(200, 0, 0));



    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    //label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(10, 10);
    text.setString("Ouro coletado : ");
    std::string ouro;
    if(mapa[i][j].HaveOuro()){
        ouro="NAO";
    }else{
        ouro="SIM";
    }
    text.setString("Ouro coletado : "+ouro);


    while (Terras_options.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (Terras_options.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                Terras_options.close();
            }
            Terras_options.clear();
            voltar.update(event);
            //VERIFICA SE A POSIÇAO É PROPICA PARA COLOCAR EXERCITO, SOMENTE POSICOES PROXIMAS AO CASTELO PODEM SER ADICIONADAS EXERCITOS
            if((i==0 && j == 1)||(i==1 && j == 1)||(i==1 && j == 0)){
                adicionar.update(event);
            }   
            
        }

        Terras_options.clear();
        Terras_options.draw(voltar);
        //VERIFICA SE A POSIÇAO É PROPICA PARA COLOCAR EXERCITO, SOMENTE POSICOES PROXIMAS AO CASTELO PODEM SER ADICIONADAS EXERCITOS
        if((i==0 && j == 1)||(i==1 && j == 1)||(i==1 && j == 0)){
            Terras_options.draw(adicionar);
        }//atualiza se terreno tem ou nao ouro
        if(mapa[i][j].HaveOuro()){
            ouro="NAO";
        }else{
            ouro="SIM";
        }
        text.setString("Ouro coletado : "+ouro);
        Terras_options.draw(text);
        Terras_options.display();

    }
}
void deslocarExercito(int i,int j){//battle 
    if(!mapa[i][j].Ocupado()){
       mapa[i][j].colocarExercito(lastReferencia,1);
       terras[i][j].changeColor(sf::Color(0, 0, 255));
    }else{
        //batalha
        /**/
        //verificar se o jogador é mais forte
        if(lastReferencia->getForcaDoExercito()>mapa[i][j].endereco->getForcaDoExercito()){
            //calcula a media de poder
            int media;
            media=lastReferencia->getForcaDoExercito()/lastReferencia->qtdDeSoldados();
            for(int p=0;p<lastReferencia->qtdDeSoldados();p++){
                Soldado* aux=lastReferencia->SoldDead(media);
                if(lastReferencia->found){
                    lastReferencia->removerSoldado(aux);
                }
            }
            //exercitosIa.remove(mapa[i][j].endereco);
            switch( mapa[i][j].endereco->iaExercito){
                case 1:
                    ia1=nullptr;
                    break;
                case 2:
                    ia2=nullptr;
                    break;
                case 3:
                    ia3=nullptr;
                    break;
                case 4:
                    ia4=nullptr;
                    break;
            }
            mapa[i][j].endereco=nullptr;
            mapa[i][j].colocarExercito(lastReferencia,1);//set o territorio com seu exercito
            terras[i][j].changeColor(sf::Color(0, 0, 255));//muda a cor do campo
            alert_window(5);//5 avisa se o player ganhou ou nao a batalha.

        }
        else if(lastReferencia->getForcaDoExercito()<mapa[i][j].endereco->getForcaDoExercito()){
            //calcula a media de poder
            int media2;
            media2=mapa[i][j].endereco->getForcaDoExercito()/mapa[i][j].endereco->qtdDeSoldados();
            for(int p=0;p<mapa[i][j].endereco->qtdDeSoldados();p++){
                Soldado* aux=mapa[i][j].endereco->SoldDead(media2);
                if(mapa[i][j].endereco->found){
                    mapa[i][j].endereco->removerSoldado(aux);
                }
            }
            delete lastReferencia;//destroi o exercito do player
            alert_window(6);//6 avisa se a ia ganhou ou nao a batalha.

        }

    }
    Mover_quit();
    exercito_options_quit();
}
void Mover(int i,int j){
    int w_width = 306;
    int w_height = 306;
    lastReferencia=mapa[i][j].getEndereco();
    terras[i][j].changeColor(sf::Color(0, 128, 128));
    mapa[i][j].desocupar();
    mana--;
    infos.create(sf::VideoMode(w_width, w_height), "MOVER", sf::Style::Titlebar + sf::Style::Close);
    /*sf::RectangleShape rectangle;
    rectangle.setSize(sf::Vector2f(w_width,w_height));
    rectangle.setFillColor(sf::Color(250,250,250));
    rectangle.setPosition(0,0);*/
    //load background
    sf::Texture texture;
    if (!texture.loadFromFile("sprites/MOVE.png")){
    }
    sf::Sprite background(texture);
    //botoes
    Button move[8];
    if(((j-1)>-1 && (j-1)<8)&&((i-1)>-1 && (i-1) <8)){
        move[0].startTerrasBotton(sf::Vector2f(0, 0), 100, deslocarExercito,i-1,j-1, sf::Color(0, 0, 0));
    }
    if(((i-1)>-1 && (i-1)<8)&&(j>-1 && j <8)){
        move[1].startTerrasBotton(sf::Vector2f(100, 0), 100, deslocarExercito,i-1,j, sf::Color(0, 0, 0));
    }
    if(((i-1)>-1 && (i-1)<8)&&((j+1)>-1 && (j+1) <8)){
        move[2].startTerrasBotton(sf::Vector2f(200, 0), 100, deslocarExercito,i-1,j+1, sf::Color(0, 0, 0));
    }
    if(((i)>-1 && (i)<8)&&((j-1)>-1 && (j-1) <8)){
        move[3].startTerrasBotton(sf::Vector2f(0, 101), 100, deslocarExercito,i,j-1, sf::Color(0, 0, 0));
    }
    if(((i)>-1 && (i)<8)&&((j+1)>-1 && (j+1) <8)){
        move[4].startTerrasBotton(sf::Vector2f(200, 101), 100, deslocarExercito,i,j+1, sf::Color(0, 0, 0));
    }
    if(((i+1)>-1 && (i+1)<8)&&((j-1)>-1 && (j-1) <8)){
        move[5].startTerrasBotton(sf::Vector2f(0, 201), 100, deslocarExercito,(i+1),(j-1), sf::Color(0, 0, 0));
    }
    if(((i+1)>-1 && (i+1)<8)&&((j)>-1 && (j) <8)){
        move[6].startTerrasBotton(sf::Vector2f(100, 202), 100, deslocarExercito,(i+1),(j), sf::Color(0, 0, 0));
    }
    if(((i+1)>-1 && (i+1)<8)&&((j+1)>-1 && (j+1) <8)){
        move[7].startTerrasBotton(sf::Vector2f(200, 202), 100, deslocarExercito,(i+1),(j+1), sf::Color(0, 0, 0));
    }
    
    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    while (infos.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (infos.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                alert_window(2);//codigo 2 para falar que nao pode desistir de um movimento
            }
            //infos.clear();
            for(int k=0;k<8;k++){
                move[k].update(event);
            }
        }

        infos.clear();
        infos.draw(background);
        for(int k=0;k<8;k++){
            infos.draw(move[k]);
        }
        
        infos.display();

    }
}
void Mover_quit(){
    infos.close();
}
void alert_quit(){
    alert.close();
}
void alert_window(int codigo){
    //codigo é referente ao qual foi o porque do alerte, abaixo o tipos
    /*
    0 = soldados livres insuficiente para adicionar ao exercito
    1 = decisao falha ao comprar exercito
    2 =  para falar que nao pode desistir de um movimento
    3 = informar que nao possui mais ouro ali
    4 = avisa que um inimigo esta ali
    5 = avisa se o player ganhou ou nao a batalha.
    6 = avisa a ia ganhou ou nao a batalha.
    7 = cercou seu castelo e venceu
    8 = inicio turno da ia
    9 = fim turno da ia
    10 = player win por supremacia
    11 = ia win por supremacia
    12 = player cercou ia
    13 = save game
    14 = player nao possui exec nem ouro
    */
    int falha=0;//variavel que diz se a mensagem de falha na operação vai ou nao aparecer
    int w_width = 300;
    int w_height = 200;
    alert.create(sf::VideoMode(w_width, w_height), "ALERT", sf::Style::Titlebar + sf::Style::Close);
    Button sair(" OK ", sf::Vector2f(w_height/2, w_height/2), 40, alert_quit, sf::Color(200, 0, 0));

    sf::Font font;
    font.loadFromFile("font/arial.ttf");

    //creating label
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setPosition(1, 10);
    switch(codigo){
        case 0:
            text.setString("nenhum homem livre");
            break;
        case 1:
            text.setString("ouro insuficiente!!!");
            break;
        case 2:
            text.setString("Nao pode cancelar movimento");
            break;
        case 3:
            text.setString("Nao possui ouro nesse terreno");
            break;
        case 4:
            text.setString("terreno dominado por inimigo");
            falha=1;
            break;
        case 5:
            text.setString("Voce venceu a batalha");
            falha=1;
            break;
        case 6:
            text.setString("Voce perdeu a batalha");
            falha=1;
            break;
        case 7:
            text.setString("Voce foi cercado! GAME OVER!!!");
            falha=1;
            break;
        case 8:
            text.setString("Turno da IA");
            falha=1;
            break;
        case 9:
            text.setString("Seu Turno");
            falha=1;
            break;
        case 10:
            text.setString("!!! YOU WIN !!!\n conquistou mais de 50% \n do territorio");
            falha=1;
            break;
        case 11:
            text.setString("!!! GAME OVER !!!\n inimigo conquistou mais \nde 50% do territorio");
            falha=1;
            break;
        case 12:
            text.setString("!!! YOU WIN !!!\n     voce cercou o     \n      inimigo     ");
            falha=1;
            break;
        case 13:
            text.setString("   jogo salvo  ");
            falha=1;
            break;
        case 14:
            text.setString("!!! GAME OVER !!!\n Voce NAO possui  \nrecursos para lutar");
            falha=1;
            break;
    }
    sf::Text text2;
    text2.setFont(font);
    text2.setColor(sf::Color::White);
    text2.setCharacterSize(20);
    text2.setPosition(w_width/5, 35);
    if(falha==0){
        text2.setString("OPERACAO FALHOU");
    }else{
        text2.setString(" ");
    }
    while (alert.isOpen() && renderWindow.isOpen()){
        //initializing event
        sf::Event event;
        // Check for all the events that occured since the last frame.
        while (alert.pollEvent(event)){
            //Handle events here
            if (event.type == sf::Event::Closed){
                alert.close();
            }
            sair.update(event);
        }
        alert.clear();
        alert.draw(text);
        alert.draw(text2);
        alert.draw(sair);
        alert.display();
    }
}
bool verificar_porcetagem_de_conquista(){
    int player=0,ia=0;
    int playerExe=0;
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(mapa[i][j].Ocupado() && mapa[i][j].getDono()==1){
                playerExe++;
            }
            if(mapa[i][j].getDono()==1){
                player++;
            }else if(mapa[i][j].getDono()==2){
                ia++;
            }
        }
    }
    if(player>24){
        alert_window(10);//player win
        return true;
    }else if(ia>24){
        alert_window(11);//player ia
        return true;
    }else if(playerExe<1 && CivilPlayer.getOuro()<100){
        alert_window(14);//player nao possui exec nem ouro
        return true;
    }else{
        return false;
    }
}
void start_game(){
    game_window_open = true;
    int w_width = 800;
    int w_height = 620;
    int cout=0,msn=0;
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
    //mover.move(20, 430);
    Button c_soldado("Comprar Soldados", sf::Vector2f(20, 490), 35, comprar_soldado_window, sf::Color(10, 0, 0));
    Button salvar("Salvar", sf::Vector2f(20, 550), 35, save_game, sf::Color(10, 0, 0));
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
     //quantidade de movimentos restantes
    sf::Text text_move;
    text_move.setFont(font);
    text_move.setColor(sf::Color::White);
    text_move.setCharacterSize(20);
    text_move.setPosition(440, 200);
    std::string move;
    move=std::to_string(mana);
    text_move.setString("movimentos restantes  : "+move);
    //botoes
    Button sair("Sair", sf::Vector2f(480, 580), 30, exit_game, sf::Color(200, 0, 0));

    //teste de tamanho de botao
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            if(mapa[i][j].getDono()==1 && mapa[i][j].Ocupado()){
                terras[i][j].startTerrasBotton(sf::Vector2f(6+j*50, 11+i*50), 47, terras_options,i,j, sf::Color(0, 0, 255));
            }
            else if(mapa[i][j].getDono()==2 && mapa[i][j].Ocupado()){
                terras[i][j].startTerrasBotton(sf::Vector2f(6+j*50, 11+i*50), 47, terras_options,i,j, sf::Color(255, 0, 0));
            }
            else if(mapa[i][j].getDono()==1){
                terras[i][j].startTerrasBotton(sf::Vector2f(6+j*50, 11+i*50), 47, terras_options,i,j, sf::Color(0, 128, 128));
            }
            else if(mapa[i][j].getDono()==2){
                terras[i][j].startTerrasBotton(sf::Vector2f(6+j*50, 11+i*50), 47, terras_options,i,j, sf::Color(128, 70, 0));
            }else{
                terras[i][j].startTerrasBotton(sf::Vector2f(6+j*50, 11+i*50), 47, terras_options,i,j, sf::Color(107, 142, 35));
            }
        }
    }
    //verificador de cerco
    bool cerco=false;
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
                quit_game();
            }
            c_soldado.update(event);
            salvar.update(event);
            sair.update(event);
            for(int i=0;i<8;i++){
                for(int j=0;j<8;j++){
                    terras[i][j].update(event);
                }
            }
        }
        //verificação da mana do jogador para entrar no turno da ia
        if(mana==0){
            //entra no turno da ia
        }
        if(cerco){
            music.stop();
            renderWindow.close();
        }
        renderWindow.clear(color);
        renderWindow.draw(territorio);
        renderWindow.draw(painel_acoes);
        renderWindow.draw(c_soldado);
        renderWindow.draw(painel_info);
        renderWindow.draw(text_info);
        renderWindow.draw(text_rei_name);
        renderWindow.draw(text_qtd_ouro);
        renderWindow.draw(text_sol_livre);
        renderWindow.draw(text_move);
        renderWindow.draw(sair);
        renderWindow.draw(salvar);
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
        move=std::to_string(mana);
        text_move.setString("movimentos restantes : "+move);
        //verificar turno
        if(mana<=0){
            if(msn==0){
                alert_window(8);//8 avisar turno da IA
                msn=1;
            }
            sleep(1);
            decisoes_ia();
            cout++;
            if(cout==5){
                mana=3;
                cout=0;
                msn=0;
                alert_window(9);//9 avisar turno da acabou
            } 
        }
        if(mapa[1][0].Ocupado()&&mapa[1][1].Ocupado()&&mapa[0][1].Ocupado()){
            if((mapa[1][0].getDono()==mapa[1][1].getDono())&&(mapa[0][1].getDono()==2)){
                alert_window(7);//7 cercou seu castelo e venceu
                cerco=true;
            }
        }
        if(mapa[6][6].Ocupado()&&mapa[6][7].Ocupado()&&mapa[7][6].Ocupado()){
            if((mapa[6][6].getDono()==mapa[6][7].getDono())&&(mapa[7][6].getDono()==1)){
                alert_window(12);//7 cercou seu castelo e venceu
                cerco=true;
            }
        }
        if(verificar_porcetagem_de_conquista()){
            music.stop();
            quit_game();
        }
    }
}
void menu(){
    window.create(sf::VideoMode(800, 600), "joguinho!");
    //load background
    sf::Texture texture;
    if (!texture.loadFromFile("sprites/bg.png")){
    }
    sf::Sprite background(texture);
    //loading fonts
    sf::Font font;
    font.loadFromFile("font/arial.ttf");
    //music
    music.openFromFile("sound/sound.ogg");
    //credits music
    sf::Text text;
    text.setFont(font);
    text.setColor(sf::Color::White);
    text.setCharacterSize(18);
    text.setPosition(20, 580);
    text.setString("Music by Eric Matyas\nwww.soundimage.org");

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
        window.draw(text);
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
    //gerando o ouro de cada terreno
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            mapa[i][j].SetQtdOuro(1+(rand()%100));
        }
    }
    
    //deixando todos os terrenos sem dono
    for(int i=0;i<8;i++){
        for(int j=0;j<8;j++){
            mapa[i][j].setDono(0);
        }
    }
    mapa[7][7].setDono(2);
    mapa[0][0].setDono(1);
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
    //load_game();
    infos.close();
    start_game();
}

///FUNCTIONS OF I.A

void imprimir_matriz(){//imprimindo a matriz
    for(int i=-1;i<=8;i++){
        for(int j=-1;j<=8;j++){
            if(i>=0&&j>=0&&i<8&&j<8){
                if(mapa[i][j].getDono()==1){
                    std::cout<<"# ";
                }
                else if(mapa[i][j].getDono()==0){
                    std::cout<<"  ";
                }else{
                    std::cout<<"* ";
                }
            }else{
                std::cout<<"@ ";
            }
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}
void localizar_inimigos(){
    for(int i=0;i<8;i++){//zera a matriz
        for(int j=0;j<8;j++){
            warnning[i][j]=0;
        }
    }
    for(int i=0;i<8;i++){//define as posiçoes que possuem inimigos
        for(int j=0;j<8;j++){
            if(mapa[i][j].getDono() == 1 && mapa[i][j].getDono()==1){
                warnning[i][j]=1;
            }
        }
    }
}
void verificar_vizinhos(int i,int j){//verifica se as posicoes vizinhas daquele territorio esta vazia ou ocupada
    //verificar qual a direção mais propriça;
    int x=i;
    int y=j;
    
    //verifcar se vizinhos estao livres, se livre 0, se ocupado 1;s
    //esquerda
    if(warnning[x][y-1]==1){
        direcao[0]=1;
    }
    //direita
    if(warnning[x][y+1]==1){
        direcao[1]=1;
    }
    //cima
    if(warnning[x-1][y]==1){
        direcao[2]=1;
    }
    //baixo
    if(warnning[x+1][y]==1){
        direcao[3]=1;
    }
}
void numero_de_inimigos_direcao(int i,int j){
    //numeros de inimigos em direção cada direção livre
    for(int a=0;a<4;a++){
        switch(a){
            case 0:
                //esquerda
                for(int x=i-1;x<=i+1;x++){
                    for(int y=j-3;y<=j-1;y++){
                        if(x>-1 && x<8 && y>-1 && y<8 && warnning[x][y]==1){
                            numeroDeInimigos[a]++;
                        }
                    }
                }
                break;
            case 1:
                //direita
                for(int x=i-1;x<=i+1;x++){
                    for(int y=j+1;y<=i+3;y++){
                        if(x>-1 && x<8 && y>-1 && y<8 && warnning[x][y]==1){
                            numeroDeInimigos[a]++;
                        }
                    }
                }
                break;
            case 2:
                //cima
                for(int x=i-3;x<=i-1;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(x>-1 && x<8 && y>-1 && y<8 && warnning[x][y]==1){
                            numeroDeInimigos[a]++;
                        }
                    }
                }
                break;
            case 3:
                //baixo
                for(int x=i+1;x<=i+3;x++){
                    for(int y=j-1;y<=j+1;y++){
                        if(x>-1 && x<8 && y>-1 && y<8 && warnning[x][y]==1){
                            numeroDeInimigos[a]++;
                        }
                    }
                }
                break;
        }
        
    }
}
void mover_ia(int i,int j){//funcao de IA
    if((i==0&&j==1)||(i==1&&j==0)||(i==1&&j==1)){
        return;
    }
    //desoculpar terro antigo
    lastReferencia=mapa[i][j].getEndereco();
    terras[i][j].changeColor(sf::Color(128, 70, 0));
    mapa[i][j].desocupar();

    int x1,y1;
    int x=i;
    int y=j;   
    //decidir para onde se mover
    int melhorDirecao=4;
    for(int i=0;i<4;i++){//zera o numero de inimigos da posiçao antiga
        numeroDeInimigos[i]=0;
    }
    //random para movimentar(FIXME:deve ser feito algo para nao ser randomico)
    srand((unsigned)time(0));

    //priorizando esquerda e cima pois é onde o jogador inicia
    //movimento diagonal
    int teste=0;
    if(((x-1)>-1 && (x-1)<8 && (y-1)>-1 && (y-1)<8) && !mapa[x-1][y-1].Ocupado()){
        x1=x-1;
        y1=y-1;
        teste=1;
    }//movimento esquerda
    if((x)>-1 && (x)<8 && (y-1)>-1 && (y-1)<8 ){
        if(teste==0){
            if(!mapa[x][y-1].Ocupado()){
                x1=x;
                y1=y-1;
                teste=1;
            }
        }
    }//movimento cima
    if( (x-1)>-1 && (x-1)<8 && (y)>-1 && (y)<8 ){
        if(teste==0){
            if(!mapa[x-1][y].Ocupado()){
                x1=x-1;
                y1=y;
                teste=1;
            }
        }
    }
    if(teste==0){
        //movimentar
        melhorDirecao=rand()%2;
        if(melhorDirecao==0){
            if((x>-1 && x<8 && (y+1)>-1 && (y+1)<8)  && !mapa[x][y+1].Ocupado()){
                x1=x;
                y1=y+1;
            }
            else{
                x1=x;
                y1=y;
            }
        }
        else if(melhorDirecao==1){
            if(((x+1)>-1 && (x+1)<8 && (y)>-1 && (y)<8 ) && !mapa[x+1][y].Ocupado()){
                x1=x+1;
                y1=y;
            }
            else{
                x1=x;
                y1=y;
            }
        }
        else{
            x1=x;
            y1=y;
        }       
    }
    mapa[x1][y1].colocarExercito(lastReferencia,2);
    mapa[x1][y1].endereco->posicao[0]=x1;
    mapa[x1][y1].endereco->posicao[1]=y1;
    terras[x1][y1].changeColor(sf::Color(255, 0, 0));
    //mapa[x1][y1].setDono(civ[0]);
}
void mover_ia2(int i,int j){//funcao de IA
    if((i==0&&j==1)||(i==1&&j==0)||(i==1&&j==1)){
        return;
    }
    //desoculpar terro antigo
    lastReferencia=mapa[i][j].getEndereco();
    terras[i][j].changeColor(sf::Color(128, 70, 0));
    mapa[i][j].desocupar();

    int x1,y1;
    int x=i;
    int y=j;   
    //decidir para onde se mover
    int melhorDirecao=4;
    for(int i=0;i<4;i++){//zera o numero de inimigos da posiçao antiga
        numeroDeInimigos[i]=0;
    }
    //random para movimentar(FIXME:deve ser feito algo para nao ser randomico)
    srand((unsigned)time(0));
    melhorDirecao=rand()%4;
    if(melhorDirecao==0){
        if((x>-1 && x<8 && (y+1)>-1 && (y+1)<8)  && !mapa[x][y+1].Ocupado()){
            x1=x;
            y1=y+1;
        }
        else{
            x1=x;
            y1=y;
        }
    }
    else if(melhorDirecao==1){
        if(((x+1)>-1 && (x+1)<8 && (y)>-1 && (y)<8 ) && !mapa[x+1][y].Ocupado()){
            x1=x+1;
            y1=y;
        }
        else{
            x1=x;
            y1=y;
        }
    }
    else if(melhorDirecao==2){
        if(((x-1)>-1 && (x-1)<8 && (y)>-1 && (y)<8 ) && !mapa[x-1][y].Ocupado()){
            x1=x-1;
            y1=y;
        }
        else{
            x1=x;
            y1=y;
        }
    }else if(melhorDirecao==3){
        if(((x)>-1 && (x)<8 && (y-1)>-1 && (y-1)<8 ) && !mapa[x][y-1].Ocupado()){
            x1=x;
            y1=y-1;
        }
        else{
            x1=x;
            y1=y;
        }
    }
    else{
        x1=x;
        y1=y;
    }       
    mapa[x1][y1].colocarExercito(lastReferencia,2);
    mapa[x1][y1].endereco->posicao[0]=x1;
    mapa[x1][y1].endereco->posicao[1]=y1;
    terras[x1][y1].changeColor(sf::Color(255, 0, 0));
}
void novo_exercito(){
    if(!ia1){
        mapa[6][7].addExercitoIa(&CivilIa,6,7);
        ia1=mapa[6][7].getEndereco();
        ia1->iaExercito=1;    
    }
    if(!ia2){
        mapa[6][6].addExercitoIa(&CivilIa,6,6);
        ia2=mapa[6][6].getEndereco();
        ia2->iaExercito=2;
    }
    if(!ia3){
        mapa[7][6].addExercitoIa(&CivilIa,7,6);
        ia3=mapa[7][6].getEndereco();
        ia3->iaExercito=3;
    }
    if(!ia4){
        mapa[5][7].addExercitoIa(&CivilIa,5,7);
        ia4=mapa[5][7].getEndereco();
        ia4->iaExercito=4;
    }
}
void add_soldado_ia(){
    srand(time(nullptr));
    int decisao=rand()%3;
    Soldado *s =new Soldado();
    s->forca=5+(rand()%10);
    switch(decisao){
        case 0:
            ia1->adicionarSoldado(s);
            break;
        case 1:
            ia2->adicionarSoldado(s);
            break;
        case 2:
            ia3->adicionarSoldado(s);
            break;
    }
}
void decisoes_ia(){
    srand(time(nullptr));
    int decisao=rand()%2;
    switch(decisao){
        //mover
        case 0:
            novo_exercito();
            decisao=rand()%3;
            switch(decisao){
                case 0:
                    mover_ia(ia1->posicao[0],ia1->posicao[1]);
                    break;
                case 1:
                    mover_ia(ia2->posicao[0],ia2->posicao[1]);
                    break;
                case 2:
                    mover_ia(ia3->posicao[0],ia3->posicao[1]);
                    break;
            }
            break;
        case 1:
            //pegar ouro
            decisao=rand()%3;
            switch(decisao){
                case 0:
                    mapa[ia1->posicao[0]][ia1->posicao[1]].getQtdDeOuro();
                    break;
                case 1:
                    mapa[ia2->posicao[0]][ia2->posicao[1]].getQtdDeOuro();
                    break;
                case 2:
                    mapa[ia3->posicao[0]][ia3->posicao[1]].getQtdDeOuro();
                    break;
            }
            break;
    }
    //adicionar soldado
    add_soldado_ia();
    novo_exercito();
    mover_ia2(ia4->posicao[0],ia4->posicao[1]);
    //comprar soldado
    //atacar
}
void save_game(){
    /*arquivo dados do player
    1=NOME DO REI
    2=OURO
    */
    std::string aux;
    std::ofstream save0 ("save/saveData0.txt");
    if(save0.is_open()){
        //infos do player
        save0 <<CivilPlayer.getRei()+ "\n";
        aux=std::to_string(CivilPlayer.getOuro());
        save0 <<aux+ "\n";
        save0.close();
    }else{
        std::cerr <<"arquivo nao aberto"<<std::endl;
    }
    /*arquivo dados dos exercitos
    */
    //exercitos
    std::ofstream save1 ("save/saveData1.txt");
    std::string I,J;
    if(save1.is_open()){
        //infos dos exercitos
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(mapa[i][j].Ocupado()&&mapa[i][j].getDono()==1){
                    aux=std::to_string(mapa[i][j].endereco->qtdDeSoldados());
                    I=std::to_string(i);
                    J=std::to_string(j);
                    save1<<I+"\n";
                    save1<<J+"\n";
                    save1<<aux+"\n";
                }
            }
        }
        save1.close();
    }else{
        std::cerr <<"arquivo nao aberto"<<std::endl;
    }
    /*arquivo dados dos terrenos
    1-64 cada linha referente a um terreno, contem o outro 
    */
    std::ofstream save2 ("save/saveData2.txt");
    if(save2.is_open()){
        //infos dos exercitos
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                aux=std::to_string(mapa[i][j].getOuro());
                save2<<aux+"\n";
            }
        }
        save2.close();
    }else{
        std::cerr <<"arquivo nao aberto"<<std::endl;
    }
    /*DONOS
    1-64 cada linha referente a um terreno, contem o outro 
    */
    std::ofstream save3 ("save/saveData3.txt");
    if(save3.is_open()){
        //infos dos exercitos
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                aux=std::to_string(mapa[i][j].getDono());
                save3<<aux+"\n";
            }
        }
        save3.close();
    }else{
        std::cerr <<"arquivo nao aberto"<<std::endl;
    }
    /*arquivo dados dos exercitos da ia
    */
    //exercitos
    std::ofstream save4 ("save/saveData4.txt");
    if(save4.is_open()){
        //infos dos exercitos
        for(int i=0;i<8;i++){
            for(int j=0;j<8;j++){
                if(mapa[i][j].Ocupado()&&mapa[i][j].getDono()==2){
                    aux=std::to_string(mapa[i][j].endereco->qtdDeSoldados());
                    I=std::to_string(i);
                    J=std::to_string(j);
                    save4<<I+"\n";
                    save4<<J+"\n";
                    save4<<aux+"\n";
                }
            }
        }
        save4.close();
    }else{
        std::cerr <<"arquivo nao aberto"<<std::endl;
    }
    alert_window(13);//13 save game
}
void add_soldado1(int i,int j){
    Soldado *s=new Soldado();
    s->forca=(rand()%10)+3;
    mapa[i][j].endereco->adicionarSoldado(s);
}
void load_game(){
    //INFOS DO PLAYER
    std::string line;
    std::ifstream data0;
    int linha=0;
    data0.open("save/saveData0.txt");
    if(data0.is_open()){
        while(data0>>line){
                if(linha==0){
                    linha++;
                    CivilPlayer.setRei(line);
                }else{
                    std::istringstream iss(line);
                    int g;
                    iss >> g;
                    CivilPlayer.setOuro(g);
                }
            
        }
        data0.close();
    }else{
        //TODO::JANELA DE LOAD FALHO
    }
    //INFOS DOS EXERCITOS
    std::ifstream data1;
    std::string line2;
    linha=0;
    int i,j,k=0;//numero que começa o exercito e i,j do exercito
    int aux;
    int countAux=1;
    data1.open("save/saveData1.txt");
    if(data1.is_open()){
        while(data1>>line){
            if(countAux%3==0){
                std::istringstream iss1(line);
                iss1 >> aux;
                k=aux;
                mapa[i][j].addExercito(&CivilPlayer);
                terras[i][j].changeColor(sf::Color(0, 0, 255));
                for(int p=0;p<k;p++){
                    add_soldado1(i,j);
                }
            }else if(countAux%2==0){
                std::istringstream iss1(line);
                iss1 >> aux;
                j=aux;
            }else{
                std::istringstream iss1(line);
                iss1 >> aux;
                i=aux;
            }
            countAux++;
        }
        data1.close();
    }else{
        //TODO::JANELA DE LOAD FALHO
    }

    std::ifstream data2;
    data2.open("save/saveData2.txt");
    int y=1;
    int u=0,w=0;
    int ouro;
    if(data2.is_open()){
        while(data2>>line){
            std::istringstream iss1(line);
            iss1 >> aux;
            ouro=aux;
            mapa[w][u].SetQtdOuro(ouro);
            if(y%8==0){
                w++;
                u=0;
            }else{
                u++;
            }
            y++;
        }
        data2.close();
    }else{
        //TODO::JANELA DE LOAD FALHO
    }

    std::ifstream data3;
    data3.open("save/saveData3.txt");
    y=1;
    u=0;
    w=0;
    if(data3.is_open()){
        while(data3>>line){
            std::istringstream iss1(line);
            iss1 >> aux;
            ouro=aux;
            mapa[w][u].setDono(ouro);
            if(y%8==0){
                w++;
                u=0;
            }else{
                u++;
            }
            y++;
        }
        data3.close();
    }else{
        //TODO::JANELA DE LOAD FALHO
    }

    //INFOS DOS EXERCITOS DA IA
    std::ifstream data4;
    linha=0;
    k=0;//numero que começa o exercito e i,j do exercito
    countAux=1;
    data4.open("save/saveData4.txt");
    if(data4.is_open()){
        while(data4>>line){
            if(countAux%3==0){
                std::istringstream iss1(line);
                iss1 >> aux;
                k=aux;
                mapa[i][j].addExercito(&CivilIa);
                terras[i][j].changeColor(sf::Color(255, 0, 0));
                for(int p=0;p<k;p++){
                    add_soldado1(i,j);
                }
            }else if(countAux%2==0){
                std::istringstream iss1(line);
                iss1 >> aux;
                j=aux;
            }else{
                std::istringstream iss1(line);
                iss1 >> aux;
                i=aux;
            }
            countAux++;
        }
        data4.close();
    }else{
        //TODO::JANELA DE LOAD FALHO
    }

}
int main(){
    
    srand(time(nullptr));
    //logica dos territorios s
    //alocando a matriz mapa
    mapa=new Territorio*[8];
    for(int i=0;i<8;i++){
        mapa[i]=new Territorio[8];
    }
    
    ///DEFINIÇOES DO PLAYER
    //mana inicial 
    mana=3;
    //definindo player como dono da posicao (0,0) obs: playerID=1, iaID =2
    CivilPlayer.setId(1);
    ///DEFINICOES DA IA
    CivilIa.setId(2);
    
    for(int i=0;i<64;i++){//zerando matriz exercitosDaIa
        for(int j=0;j<3;j++){
            exercitosDaIa[i][j]=0;
        }
    }
    ia1=nullptr;
    ia2=nullptr;
    ia3=nullptr;
    ia4=nullptr;
    novo_exercito();
    //save_game();
    ///iniciando o jogo
    menu();
    return 0;
}

