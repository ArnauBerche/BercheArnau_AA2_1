#include "map.h"
#include <iostream>
#include <time.h>

#define NUM_FPS 24

int main() {
    srand(time(NULL));

    int time = 0;
    int GameState = 0;
    bool gameOver = false;
    int posInMenu = 0;
    while (!gameOver)
    {
        time++;
        system("cls");
        switch (GameState)
        {
        case 0:
            std::cout << "  _____      _        ______       _   _ \n";
            std::cout << " |  __ \\    | |      |  ____|     | | (_)\n";
            std::cout << " | |__) |__ | | _____| |__   _ __ | |_ _ \n";
            std::cout << " |  ___/ _ \\| |/ / _ \\  __| | '_ \\| __| |\n";
            std::cout << " | |  | (_) |   <  __/ |____| | | | |_| |\n";
            std::cout << " |_|   \\___/|_|\\_\\___|______|_| |_|\\__|_|\n";
            std::cout << "                                         \n";
            std::cout << "                                         \n";
            
            if (time % (3 * 6) == 0)
            {
                GameState = 1;
            }
            break;
        case 1:
            Menu(GameState, posInMenu, time);

            break;
        case 2:
            std::cout << "Game" << std::endl;
            Game(GameState, NUM_FPS, time);
            break;
        case 3:
            std::cout << "   _____                       ____                 \n";
            std::cout << "  / ____|                     / __ \\                \n";
            std::cout << " | |  __  __ _ _ __ ___   ___| |  | |_   _____ _ __ \n";
            std::cout << " | | |_ |/ _` | '_ ` _ \\ / _ \\ |  | \\ \\ / / _ \\ '__|\n";
            std::cout << " | |__| | (_| | | | | | |  __/ |__| |\\ V /  __/ |   \n";
            std::cout << "  \\_____|\\__,_|_| |_| |_|\\___|\\____/  \\_/ \\___|_|   \n";
            std::cout << "                                                    \n";
            std::cout << "                                                    \n";
            std::cout << "                     YOU LOSE                       \n";
            if (time % (5 * 6) == 0)
            {
                gameOver = true;
            }

            break;
        case 4:
            std::cout << " __     ______  _    _  __          _______ _   _ \n";
            std::cout << " \\ \\   / / __ \\| |  | | \\ \\        / /_   _| \\ | |\n";
            std::cout << "  \\ \\_/ / |  | | |  | |  \\ \\  /\\  / /  | | |  \\| |\n";
            std::cout << "   \\   /| |  | | |  | |   \\ \\/  \\/ /   | | | . ` |\n";
            std::cout << "    | | | |__| | |__| |    \\  /\\  /   _| |_| |\\  |\n";
            std::cout << "    |_|  \\____/ \\____/      \\/  \\/   |_____|_| \\_|\n";
            std::cout << "                                                  \n";
            std::cout << "                                                  \n";
            if (time % (5 * 6) == 0)
            {
                gameOver = true;
            }
            break;
        case 5:
            std::cout << "       _           _                   \n";
            std::cout << "      | |         (_)                  \n";
            std::cout << "   ___| | ___  ___ _ _ __   __ _       \n";
            std::cout << "  / __| |/ _ \\/ __| | '_ \\ / _` |      \n";
            std::cout << " | (__| | (_) \\__ \\ | | | | (_| |_ _ _ \n";
            std::cout << "  \\___|_|\\___/|___/_|_| |_|\\__, (_|_|_)\n";
            std::cout << "                            __/ |      \n";
            std::cout << "                           |___/       \n";
            if (time % (3 * 6) == 0)
            {
                gameOver = true;
            }
        default:
            break;
        }
        Sleep(1000 / NUM_FPS);
    }

    return 0;
}