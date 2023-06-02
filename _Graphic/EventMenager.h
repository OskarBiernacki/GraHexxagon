#include "vector"
#include "../_Game/Field.h"
#include "../_Menu/Button.h"

#ifndef GRAHEXXAGON_PROJEKT_EVENTMENAGER_H
#define GRAHEXXAGON_PROJEKT_EVENTMENAGER_H

/*!
 * @brief Klasa do zarzadzania eventami, np. Kliknieciami
 */
class EventMenager {
    /*!
     * wektor obslugiwanych obiektuow typu Field
     */
    static std::vector<Field>   buttonsField;
    /*!
     * wektor obslugiwanych obiektuow typu Button
     */
    static std::vector<Button*>  buttonsButtons;
public:
    /*!
     * sprawdza ktory przycisk zostal nacisiniety i wywoluje jego onClick
     * tyczy sie tylko
     * static std::vector<Field> buttonsField;
     * @param event przekazany do interpretacji event
     * @param window okno obslugi
     */
    static void fieldClick(sf::Event& event, sf::RenderWindow& window);
    /*!
     * sprawdza ktory przycisk zostal nacisiniety i wywoluje jego onClick
     * tyczy sie tylko
     * static std::vector<Button*> buttonsButtons;
     * @param event przekazany do interpretacji event
     * @param window okno obslugi
     */
    static void buttonClick(sf::Event& event, sf::RenderWindow& window);
    /*!
     * sprawdza ktory przycisk zostal nacisiniety i wywoluje jego onFocus
     * tyczy sie tylko
     * static std::vector<Field> buttonsField;
     * @param event przekazany do interpretacji event
     * @param window okno obslugi
     */
    static void buttonFocus(sf::Event& event, sf::RenderWindow& window);
    /*!
     * wywoluje wszystkie eventy *Click
     * @param event przekazany do interpretacji event
     * @param window okno obslugi
     */
    static void eventHandler(sf::Event& event, sf::RenderWindow& window);
    /*!
     * Dodaje pole do obslugi wydarzen
     * @param field pole do dodania
     */
    static void addButtonField(Field& field);
    /*!
     * Dodaje przycisk do obslugi wydarzen
     * @param button przycisk do dodania
     */
    static void addButtonsButtons(Button& button);

    /*!
     * resetuje wszystkie aktywne oblskugi wydarzen
     */
    static void resetEvents();
};


#endif //GRAHEXXAGON_PROJEKT_EVENTMENAGER_H
