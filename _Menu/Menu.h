#include "../_Graphic/Scene.h"
#include "Button.h"
#include "SFML/Graphics.hpp"


#ifndef GRAHEXXAGON_PROJEKT_MENU_H
#define GRAHEXXAGON_PROJEKT_MENU_H


class Menu : public Scene{
private:
    sf::RenderWindow *window;
public:
    Menu();
    void tick();
};


#endif //GRAHEXXAGON_PROJEKT_MENU_H
