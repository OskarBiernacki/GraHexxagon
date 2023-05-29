#include "Button.h"
#include "Menu.h"
#include "../_Graphic/AppGUI.h"
#include "../_Game/Game.h"
#include "../_Game/Board.h"
#include "../_Graphic/EventMenager.h"
#include "NewGameMenu.h"
#include "Scoreboard.h"
#include "LoadGame.h"

Button* new_game_button;
Button* load_game_button;
Button* scoreboard_button;

Menu::Menu() {
    new_game_button = new Button("NEW GAME");
    new_game_button->setPosition(50, 50);
    new_game_button->setOnClick([](){
        EventMenager::resetEvents();
        NewGameMenu *ngm = new NewGameMenu();
        AppGUI::activeAppGui->changeScene(*ngm);
    });

    load_game_button = new Button("LOAD GAME");
    load_game_button->setPosition(50, 110);
    load_game_button->setOnClick([](){
        try {
            EventMenager::resetEvents();
            LoadGame *lg = new LoadGame();
            AppGUI::activeAppGui->changeScene(*lg);
        }catch(int lError){
            std::cout<<"Error pamieci LOAD! (" << lError << ")\n";
            EventMenager::resetEvents();
            Menu *m = new Menu();
            AppGUI::activeAppGui->changeScene(*m);
        }
    });

    scoreboard_button = new Button("SCOREBOARD");
    scoreboard_button->setPosition(50, 170);
    scoreboard_button->setOnClick([](){
        EventMenager::resetEvents();
        Scoreboard *s = new Scoreboard();
        AppGUI::activeAppGui->changeScene(*s);
    });
}

void Menu::tick() {
    new_game_button     ->printButton(AppGUI::activeAppGui->window);
    load_game_button           ->printButton(AppGUI::activeAppGui->window);
    scoreboard_button   ->printButton(AppGUI::activeAppGui->window);
}
