#include "vector"
#include "Board.h"
#include "SFML/Graphics.hpp"
#ifndef GRAHEXXAGON_PROJEKT_FIELD_H
#define GRAHEXXAGON_PROJEKT_FIELD_H


class Field {
private:
    static vector<Field*> fieldBoard;
    static Board* board;
    static void reinterprateBoard();

    char code=0;
    const int degreeBasedShapeTransform = 30;
    const float xScale = 1.7f;
    const float yScale = 1.f;
    const int xMove = 40;
    const int yMove = 20;
    const float shapeSize=28.f;

    sf::CircleShape shape;
    std::vector<Field*> oneLayersNext;
    std::vector<Field*> twoLayersNext;
public:
    int xPoz,yPoz;
    static void setBoard(Board& board);
    static void drawFiledBoard(sf::RenderWindow& window);

    bool highLighted= false;

    Field(int xPoz, int yPoz, char code);
    Field(int xPoz, int yPoz);
    void changeCode(char code);
    void printField(sf::RenderWindow& window);
    int getPlayerNumber();

    void onClick();

    char getCode();
    sf::CircleShape getShape(){return this->shape;}

    vector<Field*>& getOneLayersNext();
    vector<Field*>& getTwoLayersNext();
    static vector<Field*>& getFieldsBoard(){return fieldBoard;}
};


#endif //GRAHEXXAGON_PROJEKT_FIELD_H
