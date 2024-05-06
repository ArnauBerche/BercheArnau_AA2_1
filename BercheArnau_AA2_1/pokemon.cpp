#include "map.h"
#include <iostream>

void inicializarPokemons1(int& amountOfPokemonsInMap, char** mapa, MapaConfiguracion mapas[])
{
	int pokemonPosX = rand() % ((mapas[0].ancho-2) / 2) + 1;
	int pokemonPosY = rand() % ((mapas[0].alto-2) / 2) + 1;
	if (amountOfPokemonsInMap < mapas[0].pokemonsIniciales)
	{
		mapa[pokemonPosX][pokemonPosY] = 'P';
		amountOfPokemonsInMap++;
	}
}
void inicializarPokemons2(int& amountOfPokemonsInMap, char** mapa, MapaConfiguracion mapas[])
{
    int pokemonPosX = rand() % ((mapas[0].ancho - 2) / 2) + ((mapas[0].ancho - 2) / 2) + 2;
    int pokemonPosY = rand() % ((mapas[0].alto - 2) / 2) + 1;
    if (amountOfPokemonsInMap < mapas[1].pokemonsIniciales)
    {
        mapa[pokemonPosX][pokemonPosY] = 'P';
        amountOfPokemonsInMap++;
    }
}

void PokemonDetection(char**& mapa, MapaConfiguracion mapas[], Position jugador,char& direccion,int& capturedPokemons, int& pokemonAmountLvl1, int& pokemonAmountLvl2) {
    if (jugador.x > 0 && jugador.x < ((mapas[0].ancho - 2) / 2) + 1 && jugador.y > 0 && jugador.y < ((mapas[0].alto - 2) / 2) + 1)
    {
        if (mapa[jugador.x][jugador.y - 1] == 'P') {
            direccion = '^';
            capturedPokemons++;
            mapa[jugador.x][jugador.y - 1] = ' ';
            pokemonAmountLvl1--;
        }
        if (mapa[jugador.x][jugador.y + 1] == 'P') {
            direccion = 'v';
            capturedPokemons++;
            mapa[jugador.x][jugador.y + 1] = ' ';
            pokemonAmountLvl1--;
        }
        if (mapa[jugador.x - 1][jugador.y] == 'P') {
            direccion = '<';
            capturedPokemons++;
            mapa[jugador.x - 1][jugador.y] = ' ';
            pokemonAmountLvl1--;
        }
        if (mapa[jugador.x + 1][jugador.y] == 'P') {
            direccion = '>';
            capturedPokemons++;
            mapa[jugador.x + 1][jugador.y] = ' ';
            pokemonAmountLvl1--;
        }
    }
    else if (jugador.x > 0 && jugador.x < ((mapas[0].ancho - 2) / 2) + ((mapas[0].ancho - 2) / 2) + 2 && jugador.y > 0 && jugador.y < ((mapas[0].alto - 2) / 2) + 1)
    {
        if (mapa[jugador.x][jugador.y - 1] == 'P') {
            direccion = '^';
            capturedPokemons++;
            mapa[jugador.x][jugador.y - 1] = ' ';
            pokemonAmountLvl2--;
        }
        if (mapa[jugador.x][jugador.y + 1] == 'P') {
            direccion = 'v';
            capturedPokemons++;
            mapa[jugador.x][jugador.y + 1] = ' ';
            pokemonAmountLvl2--;
        }
        if (mapa[jugador.x - 1][jugador.y] == 'P') {
            direccion = '<';
            capturedPokemons++;
            mapa[jugador.x - 1][jugador.y] = ' ';
            pokemonAmountLvl2--;
        }
        if (mapa[jugador.x + 1][jugador.y] == 'P') {
            direccion = '>';
            capturedPokemons++;
            mapa[jugador.x + 1][jugador.y] = ' ';
            pokemonAmountLvl2--;
        }
    }

}


