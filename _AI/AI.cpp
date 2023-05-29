#include "../_Game/Board.h"
#include "../_Game/Field.h"
#include "AI.h"
#include "queue"

using namespace std;

AI::AI(Board &board) {
    this->board=&board;
}

std::pair<Field *, Field *> AI::findNextMove(char playerCode) {
    while(!moves.empty())moves.pop();
    for(Field* f : Field::getFieldsBoard())
        if(f->getCode()==playerCode){
            for (Field *allowed: f->getOneLayersNext())
                if (allowed->getCode() == board->field_symbol) {
                    pair<Field *, Field *> move = std::make_pair(f, allowed);
                    int score = this->scoreOfMove(move,playerCode);
                    moves.push(make_pair(score, move));
                }
            for (Field *allowed: f->getTwoLayersNext())
                if (allowed->getCode() == board->field_symbol) {
                    pair<Field *, Field *> move = std::make_pair(f, allowed);
                    int score = this->scoreOfMove(move,playerCode)-1;
                    moves.push(make_pair(score, move));
                }
        }
    return moves.top().second;
}

int AI::scoreOfMove(std::pair<Field*, Field*> move, char playerCode) {
    int score=1;
    for (Field* next : move.second->getOneLayersNext())
        if(next->getCode()==(playerCode==board->player_one?board->player_two:board->player_one))
            score++;

    return score;
}