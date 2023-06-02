#include "../_Game/Board.h"
#include "../_Game/Field.h"
#include "queue"

#ifndef GRAHEXXAGON_PROJEKT_AI_H
#define GRAHEXXAGON_PROJEKT_AI_H

/*!
 * @brief Klasa obslugujaca AI
 */
class AI {
public:
    /*!
     * @param board Plansza ktora bedzie analizowac AI
     */
    AI(Board& board);
    /*!
     * @param playerCode Kod gracza z ktorego perspektywy odbedzie sie analiza
     * @return Para pol, pierwsze to z ktorego wykonac ruch, a drugie na ktroe wykonac ruch
     */
    std::pair<Field*, Field*> findNextMove(char playerCode);
private:
    int scoreOfMove(std::pair<Field*,Field*> move, char playerCode);
    std::priority_queue<std::pair<int, std::pair<Field*, Field*> > > moves;
    Board* board;
};


#endif //GRAHEXXAGON_PROJEKT_AI_H
