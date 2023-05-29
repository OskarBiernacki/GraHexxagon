#include "../_Graphic/Scene.h"
#include "Board.h"
#include "SFML/Graphics.hpp"
#include "Field.h"
#include "../_AI/AI.h"

#ifndef GRAHEXXAGON_PROJEKT_GAME_H
#define GRAHEXXAGON_PROJEKT_GAME_H


class Game : public Scene{
public:
    static Game& getGame();
    /**
     * funkcja wywolywana z kazdym przeladowaniem okna
     */
    void tick();
    void setFocusedField(Field& field);

    Game(sf::RenderWindow &window, Board *board);
    Game(sf::RenderWindow &window, Board *board, bool isEnabledAI);
private:
    static Game *active_game;

    void printScore();
    void endGame();
    void checkNextMoveAvalable();
    void printEndScreen();

    bool moveFromTo(Field& toMove, Field& moveOn);
    bool player_move=true; // True - 1 False - 2
    bool canMove=true;
    bool endScreenFlag=false;
    bool isEnabledAI=false;


    Field* focusedField= nullptr;
    sf::RenderWindow *window;
    Board *board;
    AI* ai;
};

#endif //GRAHEXXAGON_PROJEKT_GAME_H
