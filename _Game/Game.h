#include "../_Graphic/Scene.h"
#include "Board.h"
#include "SFML/Graphics.hpp"
#include "Field.h"
#include "../_AI/AI.h"

#ifndef GRAHEXXAGON_PROJEKT_GAME_H
#define GRAHEXXAGON_PROJEKT_GAME_H

/*!
 * @brief Klasa Implementujaca logike gry
 */
class Game : public Scene{
public:
    static Game& getGame();
    /*!
     * funkcja wywolywana z kazdym przeladowaniem okna
     */
    void tick();
    /*!
     * Ustawia dane pole na tryb fokus
     * @param field pole do ustawienia na fokus
     */
    void setFocusedField(Field& field);

    /*!
     * @param window okno do w ktorym wysietlic scene
     * @param board plansza dla gry
     */
    Game(sf::RenderWindow &window, Board *board);
    /*!
     * @param window okno do w ktorym wysietlic scene
     * @param board plansza dla gry
     * @param isEnabledAI czy ma byc wlaczone AI
     */
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
