#include "SFML/Graphics.hpp"
#include "../_Game/Board.h"
#include "string"
#include "Scene.h"

#ifndef GRAHEXXAGON_PROJEKT_APPGUI_H
#define GRAHEXXAGON_PROJEKT_APPGUI_H


class AppGUI {
    public:
        static AppGUI* activeAppGui;
        static sf::Time deltaTime;
        AppGUI();
        void update();
        void changeScene(Scene& scene);
        sf::RenderWindow window;
    private:
        //(sf::VideoMode(800, 600), "Testowe okno SFML");
        //_Game Section

        //Window setings
        Scene* activeScene;
        const string window_name = "Hexagon _Game";
        const int window_width = 800;
        const int window_height = 600;
        const sf::Color background_color = sf::Color::Black;

};


#endif //GRAHEXXAGON_PROJEKT_APPGUI_H
