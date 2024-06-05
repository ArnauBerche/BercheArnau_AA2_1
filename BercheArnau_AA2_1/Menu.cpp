#include "map.h"
#include <iostream>
#include <time.h>

void Menu(int& GameState, int& posInMenu, int& time)
{

    std::cout << "  __  __       _         __  __                  \n";
    std::cout << " |  \\/  |     (_)       |  \\/  |                 \n";
    std::cout << " | \\  / | __ _ _ _ __   | \\  / | ___ _ __  _   _ \n";
    std::cout << " | |\\/| |/ _` | | '_ \\  | |\\/| |/ _ \\ '_ \\| | | |\n";
    std::cout << " | |  | | (_| | | | | | | |  | |  __/ | | | |_| |\n";
    std::cout << " |_|  |_|\\__,_|_|_| |_| |_|  |_|\\___|_| |_|\\__,_|\n";
    std::cout << "                                                 \n";
    std::cout << "                                                 \n";

    std::cout << std::endl;
    std::cout << "--------------------------------------------------" << std::endl << std::endl;
    switch (posInMenu)
    {
    case 0:
        std::cout << "\t\t" << "    [PLAY] " << std::endl;
        std::cout << "\t\t" << "     EXIT  " << std::endl;
        break;
    case 1:
        std::cout << "\t\t" << "     PLAY  " << std::endl;
        std::cout << "\t\t" << "    [EXIT] " << std::endl;
        break;
    default:
        break;
    }

    if (GetAsyncKeyState(VK_UP))
    {
        if (posInMenu > 0)
        {
            posInMenu--;
        }
    }
    if (GetAsyncKeyState(VK_DOWN))
    {
        if (posInMenu < 1)
        {
            posInMenu++;
        }
    }
    if (GetAsyncKeyState(VK_SPACE))
    {
        switch (posInMenu)
        {
        case 0:
            GameState = 2;
            break;
        case 1:
            GameState = 5;
            time = 0;
            break;
        default:
            break;
        }
    }
}