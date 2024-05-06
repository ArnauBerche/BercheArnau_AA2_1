#ifndef POKEMON_H
#define POKEMON_H

#include <fstream>
#include <Windows.h>
#include "map.h"

using namespace std;

void inicializarPokemons1(int& amountOfPokemonsInMap, char** mapa, MapaConfiguracion mapas[]);
void inicializarPokemons2(int& amountOfPokemonsInMap, char** mapa, MapaConfiguracion mapas[]);
void PokemonDetection(char**& mapa, MapaConfiguracion mapas[], Position jugador, char& direccion, int& capturedPokemons, int& pokemonAmountLvl1, int& pokemonAmountLvl2);
#endif
