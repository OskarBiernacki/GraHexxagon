#include <SFML/Audio.hpp>
#include "string"
#include "vector"

#ifndef GRAHEXXAGON_PROJEKT_MUSICMENAGER_H
#define GRAHEXXAGON_PROJEKT_MUSICMENAGER_H

using namespace std;
using sf::Music;

class MusicMenager {
public:
    /*!
     * Wydaje dzwiek klikniecia
     */
    static void playClickSound(){
        Music*  clickSound = new Music();
        const string clickSoundPath="../_Music/click.ogg";
        clickSound->openFromFile(clickSoundPath);
        clickSound->play();
    }
    /*!
     * Tworzy obiekt MusicMenagera i dodatkowo ustawia kolejke
     */
    MusicMenager(){
        std::unique_ptr<Music> music = std::make_unique<sf::Music>();
        music->openFromFile("../_Music/xd.ogg");
        music->setVolume(20);
        music_list.push_back(move(music));
        music = std::make_unique<sf::Music>();
        music->openFromFile("../_Music/what.ogg");
        music->setVolume(20);
        music_list.push_back(move(music));
        music = std::make_unique<sf::Music>();
        music->openFromFile("../_Music/nightc.ogg");
        music->setVolume(20);
        music_list.push_back(move(music));


        music_list.at(0)->play();
    }
    /*!
     * Wykonuje sie co tick okna
     */
    void tick(){
        if(music_list.at(playing_id)->getStatus() != Music::Playing){
            playing_id=(playing_id+1)%music_list.size();
            music_list.at(playing_id)->play();
        }
    }
private:
    vector<unique_ptr<Music>> music_list;
    int playing_id=0;
};


#endif //GRAHEXXAGON_PROJEKT_MUSICMENAGER_H
