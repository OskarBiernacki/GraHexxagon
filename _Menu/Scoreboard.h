#include "../_Graphic/Scene.h"
#include "Button.h"
#include "SFML/Graphics.hpp"
#include "queue"

#ifndef GRAHEXXAGON_PROJEKT_SCOREBOARD_H
#define GRAHEXXAGON_PROJEKT_SCOREBOARD_H


class Scoreboard : public Scene{
public:
    /*!
     * Scieszka do pliku ze scoreboardem
     */
    const std::string file_path="scoreboard.txt";
    /*!
     * zapisuje wynik do scoreboardu
     * @param blue wynik niebieskiego gracza
     * @param red wynik czerwonego gracza
     */
    static void saveScore(int blue, int red);
    /*!
     * tworzy obiekt socreboardu, czyli scene
     */
    Scoreboard();
    /*!
     * Funkcja wykonywana co tick okna
     */
    void tick();
    /*!
     * @return Scieszke do pliku z scoreboardem
     */
    static std::string getFilePath(){return (new Scoreboard())->file_path ;}
private:
    Button* back_button;
    Text tt;Font font2;
    std::priority_queue<std::pair<int, int> > loadScore();
};


#endif //GRAHEXXAGON_PROJEKT_SCOREBOARD_H
