 /*! \mainpage Projekt na PJC
 *  Projekt na pjc gra hexagon
 *  autor: Oskar Biernacki s27338
 *
 *  Jesli nie można skompilować aplikacji:
 *      1. Sprawdzić czy w pliku CMakeList.txt jest prawidłowo podana scieszka do SFML
 *      2. Jesli dalej nie działa dodać SFML/bin SFML/include SFML/lib do zmiennych środowiskowych PATH i zrestartować maszynę
 *      3. Sprawdzić czy mingw64 jest odpowiedni do danej wersji SFML
 *      4. Sprawdzić czy dana wersja SFML jest odpowiednia: GCC 7.3.0 MinGW (SEH) - 64-bit
 */


#include <iostream>
#include "_Game/Board.h"
#include "_Graphic/AppGUI.h"

using namespace std;

int main() {
    AppGUI *gui = new AppGUI();
    return 0;
}