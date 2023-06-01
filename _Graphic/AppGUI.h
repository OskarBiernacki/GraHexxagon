#include "SFML/Graphics.hpp"
#include "../_Game/Board.h"
#include "string"
#include "Scene.h"

#ifndef GRAHEXXAGON_PROJEKT_APPGUI_H
#define GRAHEXXAGON_PROJEKT_APPGUI_H

/*!
 * @brief Klasa ta obsluguje cala grafike aplikacji
 */
class AppGUI {
    public:
        /*!
         * @brief Aktualne uruchomione glowne okno gry
         */
        static AppGUI* activeAppGui;
        /*!
         * @brief Czas, ktory mina miedzy dwoma wykonaniami aplikacji
         */
        static sf::Time deltaTime;
        /*!
         * @brief Konstruktor, tworzy on okno i zapetla funkcje wewnatrz update, dodaje rowniez muzyke i pomniejsze funkcje
         */
        AppGUI();
        /*!
         * @brief Funkcja wykonywana co tick aplikacji
         */
        void update();
        /*!
         * @brief Fynkcja do zmiany sceny, czyli obecnie wysiwetlanej sceny na ekranie
         * @param scene scena, na ktora zmienic
         */
        void changeScene(Scene& scene);
        /*!
         * @brief Okno main obiektu
         */
        sf::RenderWindow window;
    private:
        Scene* activeScene;
        const string window_name = "Hexagon _Game";
        const int window_width = 800;
        const int window_height = 600;
        const sf::Color background_color = sf::Color::Black;

};


#endif //GRAHEXXAGON_PROJEKT_APPGUI_H
