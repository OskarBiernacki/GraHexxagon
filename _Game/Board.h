#include "vector"
#include "string"

#ifndef GRAHEXXAGON_PROJEKT_BOARD_H
#define GRAHEXXAGON_PROJEKT_BOARD_H

using std::vector;
using std::string;

class Board {
    public:
        const int standard_size=5;
        const char free_space_symbol=' ';
        const char field_symbol='O';
        const char disallow_field_symbol = 'X';
        const char player_one = '1';
        const char player_two = '2';

        /*!
         * Interpretacja planszy w postaci dwuwymiarowego zbioru znakow
         */
        vector<vector<char> > board_map;
        Board();

        /*!
         * funkcja zapisu planszy do pliku
         * @param file_path scieszka do pliku do zapisu
         */
        void saveBoardToFile(string file_path);
        /*!
         *
         * @param file_path scieszka do pliku z ktorego ma wczytac
         * @return Wczytana plansza
         */
        static Board* loadBoardFromFile(string file_path);
    private:
        void debugConsoleBoardPrint();
        void generateStandardBoard();
};


#endif //GRAHEXXAGON_PROJEKT_BOARD_H
