#include "SFML/Graphics.hpp"
#include "Board.h"
#include "../_Graphic/AppGUI.h"
#include <Windows.h>
#include "Game.h"
#include "../_Graphic/AppGUI.h"
#include "Field.h"
#include "iostream"
#include "../_AI/AI.h"
#include "../_Menu/Button.h"
#include "../_Menu/Menu.h"
#include "../_Graphic/EventMenager.h"
#include "../_Menu/Scoreboard.h"

using namespace sf;

Button* save_button;



Game* Game::active_game= nullptr;
Game & Game::getGame() {
    return *active_game;
}

std::string wybierzPlikZapisu() {
    sf::RenderWindow window(sf::VideoMode(350, 100), "Wybierz plik do zapisu", Style::Titlebar);
    sf::Event event;
    std::string nazwaPliku;
    Text t;
    Font f;
    f.loadFromFile("../_Game/Minecraft.ttf");
    t.setFont(f);
    t.setFillColor(Color::Yellow);
    t.setPosition(20,20);
    t.setCharacterSize(20);
    while (window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) {
                    char enteredChar = static_cast<char>(event.text.unicode);
                    if (enteredChar == '\b' && !nazwaPliku.empty()) {
                        nazwaPliku.pop_back();
                    }
                    else if (enteredChar == '\r') {
                        window.close();
                    }
                    else {
                        nazwaPliku += enteredChar;
                    }
                }
            }
        }

        window.clear();
        t.setString("Plik do zapisu: " +nazwaPliku);
        window.draw( t);
        window.display();
    }

    return nazwaPliku+".save";
}
Game::Game(RenderWindow &window, Board *board){
    active_game=this;
    this->board=board;
    this->window=&window;
    Field::setBoard(*board);
}
Game::Game(RenderWindow &window, Board *board, bool isEnabledAI) {
    this->isEnabledAI=isEnabledAI;
    if(isEnabledAI)
        this->ai=new AI(*board);
    active_game=this;
    this->board=board;
    this->window=&window;
    Field::setBoard(*board);

    save_button=new Button("SAVE");
    save_button->setPosition(600, 500);
    save_button->setOnClick([](){


        Game::getGame().board->saveBoardToFile(wybierzPlikZapisu());
        EventMenager::resetEvents();
        Menu* m = new Menu();
        AppGUI::activeAppGui->changeScene(*m);
    });
}

void Game::setFocusedField(Field &field) {
    if(!canMove)return;
    if ((field.getPlayerNumber() == 1 && player_move) || (field.getPlayerNumber() == 2 && !player_move)) {
        focusedField = &field;
        for(Field *f : Field::getFieldsBoard())
            if(f->highLighted)f->highLighted= false;
        for(Field *f : field.getOneLayersNext())
            f->highLighted=true;
        for(Field *f : field.getTwoLayersNext())
            f->highLighted=true;
    }

    if(focusedField!=nullptr && field.getPlayerNumber()==0)
        if(this->moveFromTo(*focusedField,field)){
            for(Field *f : Field::getFieldsBoard())
                if(f->highLighted)f->highLighted= false;
            focusedField=nullptr;
            player_move=!player_move;
            checkNextMoveAvalable();

            if(isEnabledAI && canMove){
                std::pair<Field*, Field*> move = ai->findNextMove(player_move?board->player_one:board->player_two);
                this->moveFromTo(*move.first, *move.second);
                player_move=!player_move;
                checkNextMoveAvalable();
            }
        }
}
bool Game::moveFromTo(Field& toMove, Field& moveOn){
    bool inRnage=false;
    bool clearToMove= false;
    for(Field *f : toMove.getOneLayersNext())
        if(f->xPoz==moveOn.xPoz && f->yPoz==moveOn.yPoz)
            inRnage=true;
    if(inRnage== false){
        for(Field *f : toMove.getTwoLayersNext())
            if(f->xPoz==moveOn.xPoz && f->yPoz==moveOn.yPoz)
                inRnage=true;
        clearToMove=inRnage;
    }
    if(!inRnage)return false;
    moveOn.changeCode(toMove.getPlayerNumber()==1?board->player_one:board->player_two);

    //Nadpisywanie
    for(Field *f : moveOn.getOneLayersNext())
        if(f->getCode()!=board->field_symbol&&f->getCode()!=toMove.getCode())
            f->changeCode(moveOn.getCode());
    if(clearToMove)
        toMove.changeCode(board->field_symbol);
    return true;
}
void Game::checkNextMoveAvalable(){
    bool scanToCanMove=false;
    for(Field* f : Field::getFieldsBoard())
        if(f->getCode()==(player_move?board->player_one:board->player_two)){
            for(Field* next : f->getOneLayersNext())
                if(next->getCode()==board->field_symbol)scanToCanMove=true;
            for(Field* next : f->getTwoLayersNext())
                if(next->getCode()==board->field_symbol)scanToCanMove=true;
        }
    if(!scanToCanMove)endScreenFlag=true;
}
void Game::endGame() {
    if(canMove)std::cout<<"Game End";
    canMove= false;

    printEndScreen();
}

Button *but= nullptr;
void Game::printEndScreen() {
    int playerOne=0;
    int playerTwo=0;
    for(Field* f : Field::getFieldsBoard()){
        if(f->getCode()==board->player_one)playerOne++;
        if(f->getCode()==board->player_two)playerTwo++;
    }

    Vector2<float> barPoz=Vector2f(window->getSize().x/2, window->getSize().y/2);

    RectangleShape endBarBackground;
    endBarBackground.setSize(Vector2f(400,300));
    endBarBackground.setFillColor(Color::Black);
    endBarBackground.setPosition(Vector2f(barPoz.x-endBarBackground.getSize().x/2, barPoz.y-endBarBackground.getSize().y/2));
    endBarBackground.setOutlineColor(Color::Yellow);
    endBarBackground.setOutlineThickness(10);

    Text textbox;
    Font font;
    font.loadFromFile("../_Game/Minecraft.ttf");
    textbox.setFont(font);
    textbox.setCharacterSize(35);
    textbox.setFillColor(Color::Yellow);
    textbox.setPosition(endBarBackground.getPosition() + Vector2f(100,30));
    textbox.setString("KONIEC GRY");

    Text wynik = textbox;
    wynik.setCharacterSize(25);
    wynik.setPosition(endBarBackground.getPosition() + Vector2f(150,80));
    wynik.setFillColor(Color::Blue);
    wynik.setString("Blue: " + std::to_string(playerOne));
    Text wynik2 = wynik;
    wynik2.setFillColor(Color::Red);
    wynik2.setPosition(endBarBackground.getPosition() + Vector2f(150,110));
    wynik2.setString("Red: " + std::to_string(playerTwo));



    this->window->draw(endBarBackground);
    this->window->draw(textbox);
    this->window->draw(wynik);
    this->window->draw(wynik2);

    if(but== nullptr) {
        Scoreboard::saveScore(playerOne,playerTwo);
        but = new Button("Menu");
        but->setOnClick([](){
            EventMenager::resetEvents();
            Menu* m = new Menu();
            AppGUI::activeAppGui->changeScene(*m);
            but= nullptr;
        });
    }
    but->setPosition(340,300);
    but->printButton(*this->window);

}

Text textbox;
Text textbox2;
Font font;
void Game::printScore() {
    int playerOne=0;
    int playerTwo=0;
    for(Field* f : Field::getFieldsBoard()){
        if(f->getCode()==board->player_one)playerOne++;
        if(f->getCode()==board->player_two)playerTwo++;
    }
    font.loadFromFile("../_Game/Minecraft.ttf");
    textbox.setFont(font);
    textbox.setCharacterSize(25);
    textbox.setFillColor(Color::Blue);
    textbox.setPosition(600,100);
    textbox.setString("Blue:\t"+ std::to_string(playerOne));
    Text textbox2 = textbox;
    textbox2.setFillColor(Color::Red);
    textbox2.setPosition(600,140);
    textbox2.setString("Red:\t"+ std::to_string(playerTwo));

    AppGUI::activeAppGui->window.draw(textbox);
    AppGUI::activeAppGui->window.draw(textbox2);
}
void Game::tick() {
    this->printScore();
    save_button->printButton(*window);
    Field::drawFiledBoard(*window);
    if(endScreenFlag)endGame();
}