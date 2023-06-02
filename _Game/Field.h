#include "vector"
#include "Board.h"
#include "SFML/Graphics.hpp"
#ifndef GRAHEXXAGON_PROJEKT_FIELD_H
#define GRAHEXXAGON_PROJEKT_FIELD_H

/*!
 * @brief Klasa reprezentujaca pole gry
 */
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
    /*!
     * Ustaw globalnie plansze
     * @param board plansza do ustawienia
     */
    static void setBoard(Board& board);
    /*!
     * Wysiwetla pola w podanym oknie
     * @param window okno w ktorym ma wyswietlic pola
     */
    static void drawFiledBoard(sf::RenderWindow& window);

    /*!
     * Czy dane pole ma byc podswietlone
     */
    bool highLighted= false;
    /*!
     * @param xPoz symboliczna pozycja na planszy, czyli numer kolumny
     * @param yPoz symboliczna pozycja na planszy, czyli numer wiersza
     * @param code kod
     */
    Field(int xPoz, int yPoz, char code);
    /*!
     * @param xPoz symboliczna pozycja na planszy, czyli numer kolumny
     * @param yPoz symboliczna pozycja na planszy, czyli numer wiersza
     */
    Field(int xPoz, int yPoz);
    /*!
     * Zmiany kodu pola na podany
     * @param code kod do zmiany
     */
    void changeCode(char code);
    /*!
     * Wyswietla konkretne pole
     * @param window okno w ktorym wysietla sie pole
     */
    void printField(sf::RenderWindow& window);
    /*!
     * Zwraca numer gracza(Na danym polu) bazujac na kodzie pola
     * @return Numer gracza
     */
    int getPlayerNumber();

    /*!
     * Wywoluje sie na kliknieciu przycisku
     */
    void onClick();

    /*!
     * @return Kod danego pola
     */
    char getCode();
    /*!
     * @return shape danego pola
     */
    sf::CircleShape getShape(){return this->shape;}

    /*!
     * @return wektor somsiadujacych pol
     */
    vector<Field*>& getOneLayersNext();
    /*!
     * @return wektor sasiadujacych pol oddzielonych o jedono pole
     */
    vector<Field*>& getTwoLayersNext();
    /*!
     * @return zwraca wektor wszystkich istniejacych pol
     */
    static vector<Field*>& getFieldsBoard(){return fieldBoard;}
};


#endif //GRAHEXXAGON_PROJEKT_FIELD_H
