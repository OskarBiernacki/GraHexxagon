#include "Scoreboard.h"
#include "../_Graphic/Scene.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "Menu.h"
#include "../_Graphic/AppGUI.h"
#include "../_Game/Game.h"
#include "../_Game/Board.h"
#include "../_Graphic/EventMenager.h"
#include <fstream>
#include <sstream>
#include "queue"

using namespace std;

Scoreboard::Scoreboard() {
    back_button = new Button("BACK");
    back_button->setPosition(600, 500);
    back_button->setOnClick([](){
        EventMenager::resetEvents();
        Menu *g = new Menu();
        AppGUI::activeAppGui->changeScene(*g);
    });

    font2.loadFromFile("../_Menu/Minecraft.ttf");
    tt.setFont(font2);
    tt.setCharacterSize(25);
    tt.setPosition(100,100);
    tt.setFillColor(Color::Yellow);
    string napis = "Top 5 wynikow: \n\n";
    priority_queue<pair<int, int> > wyniki = this->loadScore();
    if(wyniki.empty())napis+"\t-- empty -- \n" ;
    int index=1;
    while(!wyniki.empty()){
        napis+=to_string(index++)+".\t Blue: "+ to_string(wyniki.top().first) + "\t\tRed: " + to_string(wyniki.top().second) + "\n";
        wyniki.pop();
        if(index>5)break;
    }
    tt.setString(napis);
}

void Scoreboard::tick() {
    back_button->printButton(AppGUI::activeAppGui->window);
    AppGUI::activeAppGui->window.draw(tt);
}

std::priority_queue<std::pair<int, int> > Scoreboard::loadScore() {
    std::ifstream plik(this->file_path);
    std::priority_queue<std::pair<int, int>> kolejka;

    if (plik.is_open()) {
        std::string linia;
        while (std::getline(plik, linia)) {
            istringstream iss(linia);
            int liczba1, liczba2;
            if (iss >> liczba1 >> liczba2)
                kolejka.push(std::make_pair(liczba1, liczba2));
        }
        plik.close();
    }else
        std::cout << "No score file found" << std::endl;

    return kolejka;
}

void Scoreboard::saveScore(int blue, int red) {
    std::ofstream plik(Scoreboard::getFilePath(), std::ios::app);
    if (plik.is_open()){
        plik<<blue<<" "<<red<<std::endl;
        plik.close();
    }
}