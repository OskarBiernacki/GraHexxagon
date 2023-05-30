#include "Scoreboard.h"
#include "../_Graphic/Scene.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "../_Graphic/AppGUI.h"
#include "../_Game/Game.h"
#include "../_Game/Board.h"
#include "../_Graphic/EventMenager.h"
#include "queue"
#include "LoadGame.h"
#include <dirent.h>
#include <cstring>
#include "iostream"
#include "vector"

using std::vector;

LoadGame* LoadGame::activeLoadGame;

vector<string> getSaves(){
    vector<string> saves;
    std::string folder = ".";
    std::string rozszerzenie = ".save";
    DIR* dir;
    struct dirent* entry;
    if ((dir = opendir(folder.c_str())) != nullptr) {
        while ((entry = readdir(dir)) != nullptr)
            if (std::strstr(entry->d_name, rozszerzenie.c_str()) != nullptr)
                saves.push_back(entry->d_name);
        closedir(dir);
    }
    return saves;
}

LoadGame::LoadGame() {
    LoadGame::activeLoadGame=this;
    load_font.loadFromFile("../_Menu/Minecraft.ttf");
    load_textbox.setFont(load_font);
    load_textbox.setCharacterSize(40);
    load_textbox.setPosition(50,100);
    load_textbox.setFillColor(Color::Yellow);

    try {
        fileNames = getSaves();
    }catch(int error){
        std::cout<<"Brak dostepu do plikow w folderze!\n";
        RenderWindow* rw = &AppGUI::activeAppGui->window;
        EventMenager::resetEvents();
        Menu *m = new Menu();
        AppGUI::activeAppGui->changeScene(*m);
    }


    for(int i=0;i<6;i++){
        load_files_buttons[i]=new Button("-- empty -- ");
        load_files_buttons[i]->setPosition(50, (float) 170 + (float) 60 * i);
    }

    int index=0;
    for(const auto& s : fileNames)
        if(index<6) {
            load_files_buttons[index]->setText(s);
            index++;
        }

    load_files_buttons[0]->setOnClick([](){    if(LoadGame::activeLoadGame!= nullptr)LoadGame::activeLoadGame->loadOnIndex(0);    });
    load_files_buttons[1]->setOnClick([](){    if(LoadGame::activeLoadGame!= nullptr)LoadGame::activeLoadGame->loadOnIndex(1);    });
    load_files_buttons[2]->setOnClick([](){    if(LoadGame::activeLoadGame!= nullptr)LoadGame::activeLoadGame->loadOnIndex(2);    });
    load_files_buttons[3]->setOnClick([](){    if(LoadGame::activeLoadGame!= nullptr)LoadGame::activeLoadGame->loadOnIndex(3);    });
    load_files_buttons[4]->setOnClick([](){    if(LoadGame::activeLoadGame!= nullptr)LoadGame::activeLoadGame->loadOnIndex(4);    });
    load_files_buttons[5]->setOnClick([](){    if(LoadGame::activeLoadGame!= nullptr)LoadGame::activeLoadGame->loadOnIndex(5);    });


    upButton = new Button("<--  p");
    upButton->setPosition(340, 550);
    upButton->setOnClick([](){
        if(LoadGame::activeLoadGame->visualMove>0) {
            LoadGame::activeLoadGame->visualMove--;
            LoadGame::activeLoadGame->updateButtonsNames();
        }
    });


   downButton = new Button("p  -->");
   downButton->setPosition(450, 550);
   downButton->setOnClick([](){
       if(LoadGame::activeLoadGame->visualMove+6<LoadGame::activeLoadGame->fileNames.size()) {
           LoadGame::activeLoadGame->visualMove++;
           LoadGame::activeLoadGame->updateButtonsNames();
       }
   });

    load_textbox.setString("Zapisy:");

    _backButton = new Button("BACK");
    _backButton->setPosition(600, 500);
    _backButton->setOnClick([](){
        EventMenager::resetEvents();
        Menu *g = new Menu();
        AppGUI::activeAppGui->changeScene(*g);
    });

    //if(fileNames.size()>6)this->updateButtonsNames();
}

void LoadGame::tick() {
    for(auto & load_files_button : load_files_buttons)
        load_files_button->printButton(AppGUI::activeAppGui->window);

    AppGUI::activeAppGui->window.draw(load_textbox);
    _backButton->printButton(AppGUI::activeAppGui->window);
    upButton->printButton(AppGUI::activeAppGui->window);
    downButton->printButton(AppGUI::activeAppGui->window);
}

void LoadGame::loadOnIndex(int i) {
    int localIndex=i+this->visualMove;
    if(localIndex >= fileNames.size())return;
    Board *b = Board::loadBoardFromFile(fileNames.at(localIndex));

    RenderWindow* rw = &AppGUI::activeAppGui->window;
    EventMenager::resetEvents();
    Game *g = new Game(*rw, b, true);
    AppGUI::activeAppGui->changeScene(*g);
}

void LoadGame::updateButtonsNames() {
    for(int i=0;i<6;i++)
        load_files_buttons[i]->setText(fileNames.at(i+visualMove));
}
