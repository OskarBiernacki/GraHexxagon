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

#ifndef GRAHEXXAGON_PROJEKT_LOADGAME_H
#define GRAHEXXAGON_PROJEKT_LOADGAME_H


class LoadGame : public Scene{
private:
public:
    static LoadGame* activeLoadGame;
    int visualMove=0;
    Text load_textbox;
    Font load_font;
    vector<string> fileNames;
    Button* _backButton;
    Button* upButton;
    Button* downButton;
    Button *load_files_buttons[6];
    /*!
     * Wczytuje scene pod indexsem przycisku
     * @param i index przycisku
     */
    void loadOnIndex(int i);
    /*!
     * uaktualnia nazwy przyciskow
     */
    void updateButtonsNames();
    /*!
     * Konstruktor LoadGame sceny
     */
    LoadGame();
    /*!
     * funkcja wywolywana co tick okna
     */
    void tick();
};


#endif //GRAHEXXAGON_PROJEKT_LOADGAME_H
