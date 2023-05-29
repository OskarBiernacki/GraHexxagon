#include "SFML/Graphics.hpp"
#include "../_Game/Board.h"
#include "AppGUI.h"
#include <Windows.h>
#include "../_Game/Game.h"
#include "../_Game/Field.h"
#include "iostream"
#include "EventMenager.h"
#include "Scene.h"
#include "../_Menu/Menu.h"
#include "Background.h"
#include "../_Music/MusicMenager.h"

//#define DEBUG_CONFIG

using namespace sf;
using namespace std;

Time AppGUI::deltaTime;
AppGUI* AppGUI::activeAppGui;

AppGUI::AppGUI(){
    MusicMenager *mm = new MusicMenager();
    activeAppGui = this;
    sf::Clock clock;
    window.create(VideoMode(this->window_width, this->window_height), this->window_name, Style::Close);
    Image image = Image();
    if(image.loadFromFile("../_Graphic/hexagon.png")) {
        window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    }
    this->activeScene = new Menu();
    Background* b = new Background(this->window);

    while (window.isOpen()){
        deltaTime  = clock.restart();
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            EventMenager::eventHandler(event, window);
        }
        window.clear(this->background_color);
        mm->tick();
        b->tick(this->deltaTime.asSeconds());
        this->update();
        window.display();
    }
}

void AppGUI::update() {
    activeScene->tick();
}

void AppGUI::changeScene(Scene &scene) {
    this->activeScene=&scene;
}
