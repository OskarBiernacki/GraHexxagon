#include "Field.h"
#include "Board.h"
#include "iostream"
#include "vector"
#include "SFML/Graphics.hpp"
#include "../_Graphic/EventMenager.h"
#include "Game.h"
#include "../_Graphic/AppGUI.h"
#include "vector"

using namespace sf;

Board* Field::board=nullptr;
vector<Field*> Field::fieldBoard;
void Field::setBoard(Board& board) {
    Field::board=&board;
    reinterprateBoard();
}

void Field::reinterprateBoard() {
    if(fieldBoard.size()!=0)
        fieldBoard.erase(fieldBoard.begin(), fieldBoard.end());
    if(board == nullptr)return;

    for(int y=0;y<board->board_map.size();y++)
        for(int x=0;x<board->board_map.at(y).size();x++)
            if(board->board_map.at(y).at(x)!=board->free_space_symbol && board->board_map.at(y).at(x)!=board->disallow_field_symbol)
                fieldBoard.push_back(new Field(x,y,board->board_map.at(y).at(x)));
}
Field::Field(int xPoz, int yPoz, char code) {
    this->code=code;
    this->xPoz=xPoz;
    this->yPoz=yPoz;

    this->shape=CircleShape(this->shapeSize, 6);
    this->shape.rotate(this->degreeBasedShapeTransform);
    this->shape.setPosition
        (this->xScale*shape.getRadius()*xPoz+xMove, this->yScale*shape.getRadius()*yPoz+yMove);
    EventMenager::addButtonField(*this);
}
Field::Field(int xPoz, int yPoz) {
    if(board == nullptr){
        std::cout << "[CRITICAL] - no board field created " << this << "\n";
        return;
    }
    Field(xPoz,yPoz,board->field_symbol);
}

void Field::changeCode(char code) {
    this->code=code;
    board->board_map.at(yPoz).at(xPoz)=code;
}
void Field::printField(RenderWindow &window){
    code=board->board_map.at(yPoz).at(xPoz);
    if(code==board->field_symbol)this->shape.setFillColor(Color::White);
    if(highLighted)this->shape.setFillColor(Color::Yellow);
    if(code==board->player_one)this->shape.setFillColor(Color::Blue);
    if(code==board->player_two)
        this->shape.setFillColor(Color::Red);

    AppGUI::activeAppGui->window.draw(this->shape);
}
void Field::drawFiledBoard(sf::RenderWindow &window) {
    for(Field* f : fieldBoard){
        f->printField(window);
    }
}
int Field::getPlayerNumber() {
    code=board->board_map.at(yPoz).at(xPoz);
    if(this->code==board->player_one)return 1;
    if(this->code==board->player_two)return 2;
    return 0;
}
void Field::onClick() {
    Game::getGame().setFocusedField(*this);
}

vector<Field*> & Field::getOneLayersNext(){
    //generate
    if(this->oneLayersNext.size()==0){
        std::pair<int,int> poz[6]={
                std::make_pair(-1,1),
                std::make_pair(1,1),
                std::make_pair(0,2),
                std::make_pair(1,-1),
                std::make_pair(-1,-1),
                std::make_pair(0,-2)
        };
        for(Field* f : fieldBoard)
            for(int i=0;i<6;i++)
                if(f->xPoz == this->xPoz+poz[i].first &&  f->yPoz == this->yPoz+poz[i].second)
                    this->oneLayersNext.push_back(f);
    }

    return this->oneLayersNext;
}
vector<Field*> & Field::getTwoLayersNext(){
    //generate
    if(this->twoLayersNext.size()==0){
        std::pair<int,int> poz[12]={

                std::make_pair(0,4),
                std::make_pair(0,-4),
                std::make_pair(1,3),
                std::make_pair(1,-3),
                std::make_pair(2,-2),
                std::make_pair(2,0),
                std::make_pair(2,2),
                std::make_pair(-1,3),
                std::make_pair(-1,-3),
                std::make_pair(-2,2),
                std::make_pair(-2,-2),
                std::make_pair(-2,0),
        };
        for(Field* f : fieldBoard)
            for(int i=0;i<12;i++)
                if(f->xPoz == this->xPoz+poz[i].first &&  f->yPoz == this->yPoz+poz[i].second)
                    this->twoLayersNext.push_back(f);
    }

    return this->twoLayersNext;
}

char Field::getCode() {
    return code=board->board_map.at(yPoz).at(xPoz),code;
}
