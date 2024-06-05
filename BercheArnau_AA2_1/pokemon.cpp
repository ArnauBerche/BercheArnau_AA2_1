#include "map.h"
#include <iostream>

void Pokemon::initializePokemonStats(Type settype, MapaConfiguracion mapa[])
{
    type = settype;

    int movement = rand() % 4;
    switch (movement)
    {
    case 0:
            mov = MovementType::HORIZONTAL;
        break;
        case 1:
            mov = MovementType::VERTICAL;
        break;
        case 2: 
            mov = MovementType::DIAGONAL1;
        break;
        case 3:
            mov = MovementType::DIAGONAL2;
        break;
    default:
        break;
    }
    int intName = rand() % 5;

    std::string possibleNames[6] = { "Magicarp","Clefairy","Kabutops","Nidorita","Catrpi","Mewtow" };

    if (type == Type::NORMAL)
    {
        switch (intName)
        {
        case 0:
            name = possibleNames[0];
        case 1:
            name = possibleNames[1];
        case 2:
            name = possibleNames[2];
        case 3:
            name = possibleNames[3];
        case 4:
            name = possibleNames[4];
        default:
            break;
        }
    }
    else
    {
        name = possibleNames[5];
    }

    if (type == Type::NORMAL)
    {
        HP = mapa[0].saludS;
    }
    else
    {
        HP = mapa[0].saludL;
    }

}

void inicializarPokemons1(int& amountOfPokemonsInMap, CellInfo** mapa, MapaConfiguracion mapas[]) {
    int middleX = (mapas[0].alto - 2) / 2 + 1;
    int middleY = (mapas[0].ancho - 2) / 2 + 1;
    int pokemonPosY = rand() % (middleY);
    int pokemonPosX = rand() % (middleX);
    if (amountOfPokemonsInMap < mapas[0].pokemonsIniciales && mapa[pokemonPosX][pokemonPosY].IsEmpty) {
        mapa[pokemonPosX][pokemonPosY].id = Content::POKEMON;
        Pokemon poke;
        poke.initializePokemonStats(Type::NORMAL, mapas);
        mapa[pokemonPosX][pokemonPosY].pokInCell = poke;
        mapa[pokemonPosX][pokemonPosY].IsEmpty = false;
        amountOfPokemonsInMap++;
    }
}

void inicializarPokemons2(int& amountOfPokemonsInMap, CellInfo** mapa, MapaConfiguracion mapas[]) {
    int middleX = (mapas[0].alto - 2) / 2 + 1;
    int middleY = (mapas[0].ancho - 2) / 2 + 1;
    int pokemonPosY = rand() % (middleY);
    int pokemonPosX = rand() % (middleX) + (middleX+1);
    if (amountOfPokemonsInMap < mapas[1].pokemonsIniciales && mapa[pokemonPosX][pokemonPosY].IsEmpty) {
        mapa[pokemonPosX][pokemonPosY].id = Content::POKEMON;
        Pokemon poke;
        poke.initializePokemonStats(Type::NORMAL, mapas);
        mapa[pokemonPosX][pokemonPosY].pokInCell = poke;
        mapa[pokemonPosX][pokemonPosY].IsEmpty = false;
        amountOfPokemonsInMap++;
    }
}

void PokemonDetection(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, char& direccion, int& pokemonAmountLvl1, int& pokemonAmountLvl2) {

    int middleX = (mapas[0].alto - 2) / 2 + 1;
    int middleY = (mapas[0].ancho - 2) / 2 + 1;

    if (jugador.playerSector == 0) {
        if (mapa[jugador.x - 1][jugador.y].id == Content::POKEMON) {
            direccion = '<';
            jugador.capturedPokemons++;
            mapa[jugador.x - 1][jugador.y].id = Content::EMPTY;
            mapa[jugador.x - 1][jugador.y].IsEmpty = true;
            pokemonAmountLvl1--;
        }
        if (mapa[jugador.x + 1][jugador.y].id == Content::POKEMON) {
            direccion = '>';
            jugador.capturedPokemons++;
            mapa[jugador.x + 1][jugador.y].id = Content::EMPTY;
            mapa[jugador.x + 1][jugador.y].IsEmpty = true;
            pokemonAmountLvl1--;
        }
        if (mapa[jugador.x][jugador.y - 1].id == Content::POKEMON) {
            direccion = '^';
            jugador.capturedPokemons++;
            mapa[jugador.x][jugador.y - 1].id = Content::EMPTY;
            mapa[jugador.x][jugador.y - 1].IsEmpty = true;
            pokemonAmountLvl1--;
        }
        if (mapa[jugador.x][jugador.y + 1].id == Content::POKEMON) {
            direccion = 'v';
            jugador.capturedPokemons++;
            mapa[jugador.x][jugador.y + 1].id = Content::EMPTY;
            mapa[jugador.x][jugador.y + 1].IsEmpty = true;
            pokemonAmountLvl1--;
        }
    }

    else if (jugador.playerSector == 1) {
        if (mapa[jugador.x - 1][jugador.y].id == Content::POKEMON) {
            direccion = '<';
            jugador.capturedPokemons++;
            mapa[jugador.x - 1][jugador.y].id = Content::EMPTY;
            mapa[jugador.x - 1][jugador.y].IsEmpty = true;
            pokemonAmountLvl2--;
        }
        if (mapa[jugador.x + 1][jugador.y].id == Content::POKEMON) {
            direccion = '>';
            jugador.capturedPokemons++;
            mapa[jugador.x + 1][jugador.y].id = Content::EMPTY;
            mapa[jugador.x + 1][jugador.y].IsEmpty = true;
            pokemonAmountLvl2--;
        }
        if (mapa[jugador.x][jugador.y - 1].id == Content::POKEMON) {
            direccion = '^';
            jugador.capturedPokemons++;
            mapa[jugador.x][jugador.y - 1].id = Content::EMPTY;
            mapa[jugador.x][jugador.y - 1].IsEmpty = true;
            pokemonAmountLvl2--;
        }
        if (mapa[jugador.x][jugador.y + 1].id == Content::POKEMON) {
            direccion = 'v';
            jugador.capturedPokemons++;
            mapa[jugador.x][jugador.y + 1].id = Content::EMPTY;
            mapa[jugador.x][jugador.y + 1].IsEmpty = true;
            pokemonAmountLvl2--;
        }
    }
}



