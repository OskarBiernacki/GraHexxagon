cmake_minimum_required(VERSION 3.24)
project(GraHexxagon_Projekt)

set(CMAKE_CXX_STANDARD 17)

set(SFML_DIR "D:/SFML-2.5.1/lib/cmake/SFML")
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED-)


add_executable(GraHexxagon_Projekt main.cpp _Game/Board.cpp _Game/Board.h _Graphic/AppGUI.cpp _Graphic/AppGUI.h _Graphic/Scene.h _Game/Game.cpp _Game/Game.h _Game/Field.cpp _Game/Field.h _Graphic/EventMenager.cpp _Graphic/EventMenager.h _AI/AI.cpp _AI/AI.h _Menu/Button.cpp _Menu/Button.h _Menu/Menu.cpp _Menu/Menu.h _Menu/NewGameMenu.h _Menu/Scoreboard.cpp _Menu/Scoreboard.h _Menu/LoadGame.cpp _Menu/LoadGame.h _Graphic/Background.cpp _Graphic/Background.h _Music/MusicMenager.h)

target_link_libraries(GraHexxagon_Projekt sfml-graphics sfml-audio sfml-graphics sfml-window)