#include "Board.h"
#include "vector"
#include "string"
#include "iostream"
#include "fstream"


#define DEBUG

using std::vector;
using std::string;
using std::cout;
using std::pair;

Board::Board() {
    this->generateStandardBoard();
    //this->debugConsoleBoardPrint();
}

void Board::generateStandardBoard() {
    //Top piramid
    for(int i=0;i<standard_size;i++){
        if(board_map.size()<i+1)board_map.push_back(vector<char>());
        //frame left
        for(int frame=0;frame<standard_size-1-i;frame++)board_map.at(i).push_back(free_space_symbol);
        //fields
        bool fill=true;
        for(int fields=0; fields < (1 + i * 2); fields++, fill=!fill)board_map.at(i).push_back(fill ? field_symbol : free_space_symbol);
        //frame right
        for(int frame=0;frame<standard_size-1-i;frame++)board_map.at(i).push_back(free_space_symbol);
    }
    //MID part
    bool fill=false;
    for(int i=standard_size;i<standard_size*3-3;i++){
        if(board_map.size()<i+1)board_map.push_back(vector<char>());
        for(int fields=0; fields < standard_size*2-1; fields++, fill=!fill)
            board_map.at(i).push_back(fill ? field_symbol : free_space_symbol);
    }

    //Bottom piramid
    int level=0;
    for(int i=board_map.size();i<(standard_size*4-3);i++,level++){
        if(board_map.size()<i+1)board_map.push_back(vector<char>());
        //frame left
        for(int frame=0;frame<level;frame++)board_map.at(i).push_back(free_space_symbol);
        //fields
        bool fill=true;
        for(int field=0;field<2*(standard_size-level);field++,fill=!fill)board_map.at(i).push_back(fill ? field_symbol : free_space_symbol);
        //frame right
        for(int frame=0;frame<level-1;frame++)board_map.at(i).push_back(free_space_symbol);
    }
    //Disallow Fields
    pair<int, int> mid_field = std::make_pair(standard_size-2+standard_size, standard_size-1);
    board_map.at(mid_field.first-2).at(mid_field.second)=disallow_field_symbol;
    board_map.at(mid_field.first+1).at(mid_field.second-1)=disallow_field_symbol;
    board_map.at(mid_field.first+1).at(mid_field.second+1)=disallow_field_symbol;

    //Set players default
    board_map.at(0).at(4)=this->player_two;
    board_map.at(4).at(0)=this->player_one;
    board_map.at(4).at(8)=this->player_one;
    board_map.at(12).at(0)=this->player_two;
    board_map.at(12).at(8)=this->player_two;
    board_map.at(16).at(4)=this->player_one;

}
void Board::debugConsoleBoardPrint() {
    #ifdef DEBUG
        for(int i=0;i<board_map.size();i++){
            for(int x=0;x<board_map.at(i).size();x++){
                char field=board_map.at(i).at(x);
                if(field==free_space_symbol)
                    cout << field<<field<<field;
                else
                    cout << free_space_symbol << field << free_space_symbol;
            }
            cout << "\n";
        }
        cout << "\n\nstandard_size=" << standard_size << '\n';
        cout << "free_space_symbol='" << free_space_symbol << "'\n";
        cout << "field_symbol='" << field_symbol << "'\n";
        cout << "disallow_field_symbol='" << disallow_field_symbol << "'\n";
        cout << "DEBUG_Board=ON\n";
    #endif
}
void Board::saveBoardToFile(string file_path){
    std::ofstream plik(file_path, std::ios::app);
    if (plik.is_open()) {
        for(vector<char> vc : this->board_map){
            for(char znak : vc)plik<<znak;
            plik<<"\n";
        }
        plik.close();
        cout << "Zapisano!\n";
        this->debugConsoleBoardPrint();
    }else std::cout<<"Blad pliku " + file_path + "\n";
}

Board *Board::loadBoardFromFile(string file_path) {
    Board *nB = new Board();
    vector<vector<char> > load_map;
    std::ifstream plik(file_path);

    if (plik.is_open()) {
        char znak;
        vector<char> line;
        while (plik.get(znak)) {
            if(znak!='\n')line.push_back(znak);
            else{
                load_map.push_back(line);
                line = vector<char>();
            }
        }
        plik.close();
        nB->board_map=load_map;
    } else {
        std::cout << "No file to load" << std::endl;
    }

    return nB;
}
