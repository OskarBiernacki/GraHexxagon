#include "vector"
#include "../_Game/Field.h"
#include "../_Menu/Button.h"

#ifndef GRAHEXXAGON_PROJEKT_EVENTMENAGER_H
#define GRAHEXXAGON_PROJEKT_EVENTMENAGER_H


class EventMenager {
    static std::vector<Field>   buttonsField;
    static std::vector<Button*>  buttonsButtons;
public:
    static void fieldClick(sf::Event& event, sf::RenderWindow& window);
    static void buttonClick(sf::Event& event, sf::RenderWindow& window);
    static void buttonFocus(sf::Event& event, sf::RenderWindow& window);

    static void eventHandler(sf::Event& event, sf::RenderWindow& window);
    static void addButtonField(Field& field);
    static void addButtonsButtons(Button& button);

    static void resetEvents();
};


#endif //GRAHEXXAGON_PROJEKT_EVENTMENAGER_H
