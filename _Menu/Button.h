#include "string"
#include "SFML/Graphics.hpp"
#include "iostream"
#include "../_Music/MusicMenager.h"
#ifndef GRAHEXXAGON_PROJEKT_BUTTON_H
#define GRAHEXXAGON_PROJEKT_BUTTON_H

using namespace sf;

class Button {
private:
    std::string texOfButton;
    Text textbox;
    Font font;
    RectangleShape endBarBackground;
    void setStyle();
    float x=0,y=0;

    void(*pFptr)() = [](){ std::cout<<"Not implemented onClick\n"; };

    bool isGenerated=false;
    void generateStyle();

public:
    /*!
     * tworzy przyckisk i dodaje do EventMenagera
     */
    Button();
    /*!
     * tworzy przyckisk i dodaje do EventMenagera
     * @param text text ktory ma byc na przycisku
     */
    Button(std::string text);

    /*!
     * Ustawia pozycje przycisku
     * @param x pozycja x
     * @param y pozycja y
     */
    void setPosition(float x, float y);
    /*!
     * Renderuje przyckisk w oknie
     * @param window okno w ktorym renderowac
     */
    void printButton(sf::RenderWindow &window);

    /*!
     * Ustawia nowy tekst przycisku
     * @param s nowy text przycisku
     */
    void setText(std::string s);
    /*!
     * ustaw funkcje wykonywana na onClick
     * @param function funkcja ktora zostanie wywolana na kliknieciu przycisku
     */
    void setOnClick(void(*function)()){
        pFptr=function;
    }
    /*!
     * funkcja wywolywana na klikniecie przycisku
     */
    void onClick(){
        MusicMenager::playClickSound();
        pFptr();
    }
    /*!
     * Funkcja wywolywana odnosnie focusu przycisku
     * @param isFocus czy jest sfokusowany
     */
    void onFocus(bool isFocus);
    /*!
     * @return ksztalt przycisku
     */
    RectangleShape& getShape(){return this->endBarBackground;}
};


#endif //GRAHEXXAGON_PROJEKT_BUTTON_H
