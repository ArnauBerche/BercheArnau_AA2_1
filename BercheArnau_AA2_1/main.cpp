#include "map.h"
#include "pokemon.h"
#include <iostream>
#include <time.h>

int main() {
    srand(time(NULL));

    char direccion = '^';
    int pokemonAmountLvl1 = 0;
    int pokemonAmountLvl2 = 0;
    bool lvl1Requirement = true;
    bool done1 = false;
    bool lvl2Requirement = true;
    bool done2 = false;
    int capturedPokemons = 0;

    MapaConfiguracion mapas[4];

    leerConfiguracion("config.txt", mapas, 4);
    char** mapa = inicializarMapa(mapas[0].alto, mapas[0].ancho);
    Position jugador = { 1, 1 };
    
    bool jugando = true;
    while (jugando) {
        system("cls");
        cout << capturedPokemons << endl;

        inicializarPokemons1(pokemonAmountLvl1,mapa, mapas);
        inicializarPokemons2(pokemonAmountLvl2, mapa, mapas);
        if (GetAsyncKeyState(VK_UP)) {
            if (mapa[jugador.x][jugador.y-1] != 'X') {
                jugador.y--;
                direccion = '^';
            }
        }
        else if (GetAsyncKeyState(VK_DOWN)) {
            if (mapa[jugador.x][jugador.y + 1] != 'X') {
                jugador.y++;
                direccion = 'v';
            }
        }
        else if (GetAsyncKeyState(VK_LEFT)) {
            if (mapa[jugador.x-1][jugador.y] != 'X') {
                jugador.x--;
                direccion = '<';
            }
        }
        else if (GetAsyncKeyState(VK_RIGHT)) {
            if (mapa[jugador.x +1][jugador.y] != 'X') {
                jugador.x++;
                direccion = '>';

            }
        }
        else if (GetAsyncKeyState(VK_SPACE)) {
            PokemonDetection(mapa, mapas,jugador, direccion, capturedPokemons, pokemonAmountLvl1, pokemonAmountLvl2);
        }

        if (capturedPokemons >= mapas[0].pokemonsParaDesbloquear && !done1)
        {
            for (int i = 0; i < mapas[0].alto; ++i) {
                for (int j = 0; j < mapas[0].ancho; ++j) {
                    if (j < (mapas[0].alto / 2) && j > 0 && i == (mapas[0].ancho / 2)) {
                        mapa[i][j] = ' ';                       
                    }
                }
            }
            done1 = true;
        }
        if (capturedPokemons >= mapas[1].pokemonsParaDesbloquear)
        {
            for (int i = 0; i < mapas[0].alto; ++i) {
                for (int j = 0; j < mapas[0].ancho; ++j) {
                    if (i > (mapas[0].ancho / 2) && i < mapas[0].ancho-1 && j == (mapas[0].alto / 2)) {
                        mapa[i][j] = ' ';
                    }
                }
            }
            done2 = true;
        }


        imprimirMapa(mapa, mapas[0].alto, mapas[0].ancho, jugador, direccion);

        Sleep(100);
    }

    liberarMapa(mapa, mapas[0].alto);

    return 0;
}