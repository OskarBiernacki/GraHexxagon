#include "../_Graphic/Scene.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "../_Graphic/AppGUI.h"
#include "../_Game/Game.h"
#include "../_Game/Board.h"
#include "../_Graphic/EventMenager.h"

#ifndef GRAHEXXAGON_PROJEKT_NEWGAMEMENU_H
#define GRAHEXXAGON_PROJEKT_NEWGAMEMENU_H

class NewGameMenu : public Scene{
private:
    sf::RenderWindow *window;
    Button* play_player_button;
    Button* play_ai_button;
    Button* back_button;
public:
    NewGameMenu(){
        play_player_button = new Button("Player vs Player");
        play_player_button->setPosition(50, 50);
        play_player_button->setOnClick([](){
            RenderWindow* rw = &AppGUI::activeAppGui->window;
            EventMenager::resetEvents();
            Game *g = new Game(*rw, new Board(), false);
            AppGUI::activeAppGui->changeScene(*g);
        });
        play_ai_button = new Button("Player vs AI");
        play_ai_button->setPosition(50, 110);
        play_ai_button->setOnClick([](){
            RenderWindow* rw = &AppGUI::activeAppGui->window;
            EventMenager::resetEvents();
            Game *g = new Game(*rw, new Board(), true);
            AppGUI::activeAppGui->changeScene(*g);
        });

        back_button = new Button("BACK");
        back_button->setPosition(600, 500);
        back_button->setOnClick([](){
            EventMenager::resetEvents();
            Menu *g = new Menu();
            AppGUI::activeAppGui->changeScene(*g);
        });
    }
    void tick(){
        play_player_button->printButton(AppGUI::activeAppGui->window);
        play_ai_button->printButton(AppGUI::activeAppGui->window);
        back_button->printButton(AppGUI::activeAppGui->window);
    }
};

#endif //GRAHEXXAGON_PROJEKT_NEWGAMEMENU_H
