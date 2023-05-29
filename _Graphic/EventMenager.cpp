#include "vector"
#include "EventMenager.h"
#include "SFML/Graphics.hpp"
#include "../_Game/Field.h"
#include "math.h"
#include "iostream"

using namespace std;
using namespace sf;
vector<Field> EventMenager::buttonsField;
vector<Button*> EventMenager::buttonsButtons;

double distance_calc(double ax, double ay, double bx, double by){
    int x = ax-bx;
    int y = ay-by;

    return sqrt(x*x+y*y);
}
void EventMenager::eventHandler(sf::Event& event, sf::RenderWindow& window) {
    fieldClick(event, window);
    buttonClick(event, window);
    buttonFocus(event, window);
}
void EventMenager::addButtonField(Field& field){
    buttonsField.push_back(field);
}

void EventMenager::addButtonsButtons(Button &button) {
    buttonsButtons.push_back(&button);
}

void EventMenager::fieldClick(Event &event, RenderWindow &window) {
    if(event.type == Event::MouseButtonPressed){
        if(event.mouseButton.button == Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            vector<Field*> candidates;
            for(Field &f : buttonsField)
                if (f.getShape().getGlobalBounds().contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)))
                    candidates.push_back(&f);
            //Eliminacja bledu przesuniecia i zaznaczania kilku na raz
            double min=100000;
            for(Field *f : candidates){
                double c = distance_calc(mousePos.x, mousePos.y, f->getShape().getPosition().x+10, f->getShape().getPosition().y+40);
                min=min>c?c:min;
            }
            for(Field *f : candidates)
                if(distance_calc(mousePos.x, mousePos.y, f->getShape().getPosition().x+10, f->getShape().getPosition().y+40)==min)
                    f->onClick();

        }
    }
}

void EventMenager::buttonClick(Event &event, RenderWindow &window) {
    if(event.type == Event::MouseButtonPressed) {
        if (event.mouseButton.button == Mouse::Left){
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for(Button *b : buttonsButtons)
                if (b->getShape().getGlobalBounds().contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)))
                    b->onClick();
        }
    }
}

void EventMenager::buttonFocus(Event &event, RenderWindow &window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    for(Button *b : buttonsButtons)
        b->onFocus(b->getShape().getGlobalBounds().contains(static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)));
}

void EventMenager::resetEvents() {
    while(!buttonsButtons.empty()) {buttonsButtons.pop_back();}
    while(!buttonsField.empty())buttonsField.pop_back();
}
