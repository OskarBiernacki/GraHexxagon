#include "../_Game/Board.h"
#include "../_Game/Field.h"
#include "queue"

#ifndef GRAHEXXAGON_PROJEKT_AI_H
#define GRAHEXXAGON_PROJEKT_AI_H


class AI {
public:
    AI(Board& board);
    std::pair<Field*, Field*> findNextMove(char playerCode);
private:
    int scoreOfMove(std::pair<Field*,Field*> move, char playerCode);
    std::priority_queue<std::pair<int, std::pair<Field*, Field*> > > moves;
    Board* board;
};


#endif //GRAHEXXAGON_PROJEKT_AI_H
