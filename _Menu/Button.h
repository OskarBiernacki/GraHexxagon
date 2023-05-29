#include "string"
#include "SFML/Graphics.hpp"
#include "iostream"
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
    Button();
    Button(std::string text);

    void setPosition(float x, float y);
    void printButton(sf::RenderWindow &window);

    void setText(std::string s);
    void setOnClick(void(*function)()){
        pFptr=function;
    }
    void onClick(){
        pFptr();
    }
    void onFocus(bool isFocus);
    RectangleShape& getShape(){return this->endBarBackground;}
};


#endif //GRAHEXXAGON_PROJEKT_BUTTON_H
