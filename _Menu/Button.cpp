#include "Button.h"
#include "../_Graphic/EventMenager.h"
#include "iostream"

Button::Button() {
    this->setStyle();
    EventMenager::addButtonsButtons(*this);
}

Button::Button(std::string text) {
    this->texOfButton=text;
    this->setStyle();
    EventMenager::addButtonsButtons(*this);
}

void Button::printButton(sf::RenderWindow &window) {
    window.draw(this->endBarBackground);
    window.draw(this->textbox);
}
void Button::setStyle() {
    generateStyle();
    this->endBarBackground.setPosition(this->x,this->y);
    this->endBarBackground.setSize(Vector2f(this->textbox.getLocalBounds().width*1.3, this->textbox.getLocalBounds().height*1.7));
    this->textbox.setPosition(this->endBarBackground.getPosition().x+endBarBackground.getSize().x/2-this->textbox.getLocalBounds().width/2,

                              this->endBarBackground.getPosition().y+endBarBackground.getSize().y/2-this->textbox.getLocalBounds().height/1.2);
}
void Button::generateStyle() {
    if(this->isGenerated)return;

    this->endBarBackground.setOutlineThickness(5);
    this->endBarBackground.setOutlineColor(Color::Yellow);
    this->isGenerated=true;
    this->textbox.setCharacterSize(30);
    this->endBarBackground.setFillColor(Color::Black);
    this->font.loadFromFile("../_Menu/Minecraft.ttf");
    this->textbox.setString(this->texOfButton);
    this->textbox.setFont(font);
    this->textbox.setFillColor(Color::Yellow);
}
void Button::setPosition(float x, float y) {
    this->x=x;
    this->y=y;
    setStyle();
}
void Button::onFocus(bool isFocus) {
    if(isFocus) {
        this->textbox.setFillColor(Color::Blue);
        this->endBarBackground.setOutlineColor(Color::Blue);
    }else{
        this->textbox.setFillColor(Color::Yellow);
        this->endBarBackground.setOutlineColor(Color::Yellow);
    }
}

void Button::setText(std::string s) {
    this->texOfButton=s;
    this->textbox.setString(this->texOfButton);
    this->setStyle();
}
