#include "map.h"
#include <iostream>
#include <time.h>

int main() {
    srand(time(NULL));

    char direccion = '^';
    int pokemonAmountLvl1 = 0;
    int pokemonAmountLvl2 = 0;
    bool pokeballInMap = false;
    int pokeballInMapPos[2] = {0,0};
    bool lvl1Requirement = true;
    bool done1 = false;
    bool lvl2Requirement = true;
    bool done2 = false;

    Player jugador = { 1, 1,0,0 };

    MapaConfiguracion mapas[4];
    leerConfiguracion("config.txt", mapas, 4, jugador);
    CellInfo** mapa = inicializarMapa(mapas[0].alto, mapas[0].ancho);



    bool jugando = true;
    while (jugando) {
        system("cls");
        std::cout << "Pokemon Amount: " << jugador.capturedPokemons << "\t";

        std::cout << "Pokeball Amount: " << jugador.pokeballAmount << std::endl;
        jugador.playerSector = DetectPlayerSector(mapa, mapas, jugador);
        std::cout << "Player Sector: " << jugador.playerSector << std::endl;
        std::cout << "PDMG: " << jugador.pikachuDMG << std::endl;
        std::cout << "HP: " << mapas[0].saludS << std::endl;
        std::cout << "LHP: " << mapas[0].saludL << std::endl;
        std::cout << "TMIN: " << mapas[0].tTMMin << std::endl;
        std::cout << "TMAX: " << mapas[0].tTMMax << std::endl;

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
            PokemonDetection(mapa, mapas, jugador, direccion, pokemonAmountLvl1, pokemonAmountLvl2);
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
        imprimirMapa(mapa, mapas[0].alto, mapas[0].ancho, jugador, direccion);

        Sleep(100);
    }

    liberarMapa(mapa, mapas[0].alto);

    return 0;
}