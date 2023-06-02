#include "SFML/Graphics.hpp"
#ifndef GRAHEXXAGON_PROJEKT_BACKGROUND_H
#define GRAHEXXAGON_PROJEKT_BACKGROUND_H
#include "math.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "iostream"
#include "vector"
#include "random"

/*!
 * @brief Pojedyncza kulka, ktora lata w tle
 */
struct bloob{
    float ax,ay;
    float dest_x,dest_y;
    float radius=1.f;
    float end_radius=10.f;
    float source_distance_x, source_distance_y;
    float ileSecMove=5;
    bool toKill=false;
    sf::CircleShape *bll;
    bloob(float _ax, float _ay, float dx, float dy): ax(_ax),ay(_ay),dest_x(dx),dest_y(dy){
        this->source_distance_x=_ax-dx;
        this->source_distance_y=_ay-dy;
        bll = new sf::CircleShape(radius, 13);
        bll->setPosition(ax,ay);
    }
    void move(float deltaTime){
        if(toKill)return;
        ax-=source_distance_x*deltaTime/ileSecMove;
        ay-=source_distance_y*deltaTime/ileSecMove;
        bll->setPosition(ax, ay);
        float distancePrec = sqrt((ax-dest_x)*(ax-dest_x)+ (ay-dest_y)*(ax-dest_y))/
                sqrt(source_distance_x*source_distance_x+source_distance_y*source_distance_y);
        distancePrec=1-distancePrec;
        if(distancePrec>0.95)toKill=true;
        bll->setRadius(radius+(end_radius-radius)*distancePrec);
    }

    void print(sf::RenderWindow& window){
        if(toKill)return;
        window.draw(*bll);
    }
};

/*!
 * @brief Klasa generujaca tlo
 */
class Background {
public:
    /*!
     * mala kuleczka w centrum ekranu
     */
    sf::CircleShape *center;
    /*!
     * Inicjuje tlo
     * @param window okno w ktorym bedzie ono wyswietlane
     */
    Background(sf::RenderWindow& window) : m_window(window)
    {
         srand(time(NULL));
         bl=new bloob(250,250,400,500);

         center=new sf::CircleShape(2,20);
         center->setOrigin(center->getRadius(), center->getRadius());
         center->setPosition(400,300);
    }
    /*!
     * Wykonuje sie co tick okna
     * @param deltaTime ile sekund mija co tick
     */
    void tick(float deltaTime) {
        for(bloob* b : stars){
            b->move(deltaTime);
            b->print(this->m_window);
            if(b->toKill){
                auto iterator = std::find(stars.begin(), stars.end(), b);
                if (iterator != stars.end()) {
                    stars.erase(iterator);
                }
            }
        }
        toAddTimer +=deltaTime;
        if(toAddTimer>nextAdd){
            for(int i=0;i<2;i++) {
                toAddTimer = 0;
                nextAdd = ((float) (std::rand() % 10)) / 100;

                int xp = rand() % 1500;
                int yp = rand() % 1500;

                while(sqrt(xp*xp+yp*yp)<900) {
                    xp = rand() % 1000;
                    yp = rand() % 800;
                }
                xp = (rand() % 2 == 0) ? xp : -(xp%800);
                yp = (rand() % 2 == 0) ? yp : -(yp%600);
                stars.push_back(new bloob(400, 300, xp, yp));
            }
        }
        m_window.draw(*center);
    }

private:
    sf::RenderWindow& m_window;
    bloob *bl;
    std::vector<bloob*> stars;
    float toAddTimer=0;
    float nextAdd=0.2f;
};

#endif //GRAHEXXAGON_PROJEKT_BACKGROUND_H
