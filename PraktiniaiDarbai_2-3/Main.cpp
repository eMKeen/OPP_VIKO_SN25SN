/**
* @file Main.cpp
* @brief Contains the program entry point.
*
* Configures the Windows console for UTF-8 and starts the game.
*/
#include <iostream>
#include <windows.h>
#include "Game.h"

using namespace std;

/**
* @brief Starts the mathematical game.
*
* Sets the Windows input and output code pages to UTF-8, runs the game.
*
* @return Zero when the program finishes normally.
*/
int main() {
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    CGame _game;
    _game.run();

    cout << "Iki kito karto!" << endl;
    return 0;
}