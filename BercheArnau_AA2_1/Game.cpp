#include "map.h"
#include <iostream>
#include <time.h>

void Game(int& GameState, int num_FPS, int& timer)
{
    int time = 0;
    char direccion = '^';
    int pokemonAmountLvl1 = 0;
    int pokemonAmountLvl2 = 0;
    bool pokeballInMap = false;
    int pokeballInMapPos[2] = { 0,0 };
    bool lvl1Requirement = true;
    bool done1 = false;
    bool lvl2Requirement = true;
    bool done2 = false;
    bool mewtwoSpawned = false;
    bool mewtwoCaptured = false;
    bool mewtwoStillOnMap = true;
    bool done3 = false;

    Player jugador = { 1, 1,0,0 };

    MapaConfiguracion mapas[4];
    leerConfiguracion("config.txt", mapas, 4, jugador);
    CellInfo** mapa = inicializarMapa(mapas[0].alto, mapas[0].ancho);

    int posInMenu = 0;
    int storePokemonPos[2];
    bool jugando = true;
    bool capturing = false;

    while (jugando) {
        std::cout << "Pokemon Amount: " << jugador.capturedPokemons << "\t";

        std::cout << "Pokeball Amount: " << jugador.pokeballAmount << std::endl;
        jugador.playerSector = DetectPlayerSector(mapa, mapas, jugador);
        std::cout << "\t      "  << jugador.selectorToName(jugador.playerSector) << std::endl;

        imprimirMapa(mapa, mapas[0].alto, mapas[0].ancho, jugador, direccion);
        int randomTime = rand() % 2;

        if (!capturing) {
            switch (randomTime)
            {
            case 0:
                if (time % (mapas[0].tTMMin * 6) == 0)
                {
                    Move(mapa, mapas);
                    time = 0;
                }
                break;
            case 1:
                if (time % (mapas[0].tTMMax * 6) == 0)
                {
                    Move(mapa, mapas);
                    time = 0;
                }
                break;
            default:
                break;
            }
            inicializeMewtwo(mapa, mapas, mewtwoSpawned);
            inicializarPokemons1(pokemonAmountLvl1, mapa, mapas);
            inicializarPokemons2(pokemonAmountLvl2, mapa, mapas);
            inicizlizarPokeballs(mapa, mapas, jugador, pokeballInMap, pokeballInMapPos);
            PokeballColection(mapa, jugador, pokeballInMap);
            if (GetAsyncKeyState(VK_UP)) {
                if (mapa[jugador.x][jugador.y - 1].IsEmpty) {
                    jugador.y--;
                    direccion = '^';
                }
            }
            else if (GetAsyncKeyState(VK_DOWN)) {
                if (mapa[jugador.x][jugador.y + 1].IsEmpty) {
                    jugador.y++;
                    direccion = 'v';
                }
            }
            else if (GetAsyncKeyState(VK_LEFT)) {
                if (mapa[jugador.x - 1][jugador.y].IsEmpty) {
                    jugador.x--;
                    direccion = '<';
                }
            }
            else if (GetAsyncKeyState(VK_RIGHT)) {
                if (mapa[jugador.x + 1][jugador.y].IsEmpty) {
                    jugador.x++;
                    direccion = '>';
                }
            }
            else if (GetAsyncKeyState(VK_SPACE)) {
                PokemonDetection(mapa, mapas, jugador, direccion,capturing, storePokemonPos[0], storePokemonPos[1]);
            }
            if (jugador.capturedPokemons >= mapas[0].pokemonsParaDesbloquear && !done1) {
                for (int j = 1; j < mapas[0].ancho / 2; ++j) {
                    mapa[mapas[0].alto / 2][j].IsEmpty = true;
                    mapa[mapas[0].alto / 2][j].id = Content::EMPTY;
                }
                done1 = true;
            }
            if (jugador.capturedPokemons >= mapas[1].pokemonsParaDesbloquear && !done2) {
                for (int i = mapas[0].alto / 2 + 1; i < mapas[0].alto - 1; ++i) {
                    mapa[i][mapas[0].ancho / 2].IsEmpty = true;
                    mapa[i][mapas[0].ancho / 2].id = Content::EMPTY;
                }
                done2 = true;
            }
            if (!mewtwoStillOnMap && !done3) {
                for (int j = (mapas[0].ancho / 2) + 1; j < mapas[0].ancho -1; ++j) {
                    mapa[mapas[0].alto / 2][j].IsEmpty = true;
                    mapa[mapas[0].alto / 2][j].id = Content::EMPTY;
                }
                done3 = true;
            }

            if (jugador.playerSector == 3 && !mewtwoCaptured)
            {
                GameState = 3;
                jugando = false;
                timer = 0;
            }
            if (jugador.playerSector == 3 && mewtwoCaptured)
            {
                GameState = 4;
                jugando = false;
                timer = 0;
            }

            time++;
        }
        else 
        {
            std::cout << std::endl;
            std::cout << "  -------------------------" << std::endl;
            std::cout << "  " << mapa[storePokemonPos[0]][storePokemonPos[1]].pokInCell.name << "\t\t" << mapa[storePokemonPos[0]][storePokemonPos[1]].pokInCell.HP << std::endl;
            if (posInMenu == 0)
            {
                std::cout << "\t" << "    [Atacar] " << std::endl;
                std::cout << "\t" << "    Capturar " << std::endl;
                std::cout << "\t" << "      Huir   " << std::endl;

            }
            if (posInMenu == 1)
            {
                std::cout << "\t" << "     Atacar  " << std::endl;
                std::cout << "\t" << "   [Capturar]" << std::endl;
                std::cout << "\t" << "      Huir   " << std::endl;

            }
            if (posInMenu == 2)
            {
                std::cout << "\t" << "     Atacar  " << std::endl;
                std::cout << "\t" << "    Capturar " << std::endl;
                std::cout << "\t" << "     [Huir]  " << std::endl;

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
                if (posInMenu < 2)
                {
                    posInMenu++;
                }
            }
            if (GetAsyncKeyState(VK_SPACE))
            {
                if (posInMenu == 0)
                {
                    Atacar(jugador,mapa, storePokemonPos[0],storePokemonPos[1], capturing, pokemonAmountLvl1, pokemonAmountLvl2, mewtwoStillOnMap);
                }                
                else if (posInMenu == 1)
                {
                    bool captured = false;
                    Capturar(jugador, mapa, storePokemonPos[0], storePokemonPos[1], captured, capturing, pokemonAmountLvl1, pokemonAmountLvl2, mewtwoCaptured, mewtwoStillOnMap);
                    if (captured) 
                    {
                        capturing = false;
                    }
                }
                else
                {
                    capturing = false;
                    if (mapa[storePokemonPos[0]][storePokemonPos[1]].pokInCell.type == Type::LEGENDARY)
                    {
                        mapa[storePokemonPos[0]][storePokemonPos[1]].id = Content::EMPTY;
                        mapa[storePokemonPos[0]][storePokemonPos[1]].IsEmpty = true;
                        mewtwoStillOnMap = false;
                    }
                }
            }
        }
        Sleep(1000/ num_FPS);
        system("cls");
    }

    liberarMapa(mapa, mapas[0].alto);

}