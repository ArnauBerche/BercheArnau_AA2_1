#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void Pokemon::initializePokemonStats(Type settype, MapaConfiguracion mapa[])
{
    type = settype;

    code = rand() % 1000; // Se puede repetir pero es poco probable

    int movement = rand() % 4;
    if (settype == Type::LEGENDARY)
    {
        movement = 4;
    }
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
        case 4:
            mov = MovementType::STATIC;
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
            break;
        case 1:
            name = possibleNames[1];
            break;
        case 2:
            name = possibleNames[2];
            break;
        case 3:
            name = possibleNames[3];
            break;
        case 4:
            name = possibleNames[4];
            break;
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

void Move(CellInfo** mapa, MapaConfiguracion mapas[]) {
    int moveCords1[2] = { 1, 1 };
    int moveCords2[2] = { 1, 1 };
    int* code = new int[mapas[0].ancho*mapas[0].alto];
    int codesEntered = 0;

    bool repeated = false;

    for (int i = 0; i < mapas[0].alto; i++)
    {
        for (int j = 0; j < mapas[0].ancho; j++)
        {
            if (mapa[i][j].id == Content::POKEMON && mapa[i][j].pokInCell.mov != MovementType::STATIC)
            {
                for (int x = 0; x < codesEntered; x++)
                {
                    if (code[x] == mapa[i][j].pokInCell.code)
                    {
                        repeated = true;
                    }
                    else
                    {
                        repeated = false;
                    }
                     
                }
                if (!repeated)
                {
                    switch (mapa[i][j].pokInCell.mov) {
                    case MovementType::HORIZONTAL:
                        moveCords1[0] = mapa[i][j].PosX;
                        moveCords1[1] = mapa[i][j].PosY - 1;
                        moveCords2[0] = mapa[i][j].PosX;
                        moveCords2[1] = mapa[i][j].PosY + 1;
                        break;
                    case MovementType::VERTICAL:
                        moveCords1[0] = mapa[i][j].PosX - 1;
                        moveCords1[1] = mapa[i][j].PosY;
                        moveCords2[0] = mapa[i][j].PosX + 1;
                        moveCords2[1] = mapa[i][j].PosY;
                        break;
                    case MovementType::DIAGONAL1:
                        moveCords1[0] = mapa[i][j].PosX - 1;
                        moveCords1[1] = mapa[i][j].PosY - 1;
                        moveCords2[0] = mapa[i][j].PosX + 1;
                        moveCords2[1] = mapa[i][j].PosY + 1;
                        break;
                    case MovementType::DIAGONAL2:
                        moveCords1[0] = mapa[i][j].PosX - 1;
                        moveCords1[1] = mapa[i][j].PosY + 1;
                        moveCords2[0] = mapa[i][j].PosX + 1;
                        moveCords2[1] = mapa[i][j].PosY - 1;
                        break;
                    default:
                        break;
                    }

                    if (!mapa[i][j].pokInCell.direction)
                    {
                        if (mapa[moveCords1[0]][moveCords1[1]].IsEmpty == true && mapa[moveCords1[0]][moveCords1[1]].id == Content::EMPTY)
                        {
                            mapa[moveCords1[0]][moveCords1[1]].pokInCell = mapa[i][j].pokInCell;
                            mapa[moveCords1[0]][moveCords1[1]].id = mapa[i][j].id;
                            mapa[moveCords1[0]][moveCords1[1]].IsEmpty = mapa[i][j].IsEmpty;
                            mapa[i][j].id = Content::EMPTY;
                            mapa[i][j].IsEmpty = true;
                            code[codesEntered] = mapa[i][j].pokInCell.code;
                            codesEntered++;
                        }
                        else
                        {
                            mapa[i][j].pokInCell.direction = !mapa[i][j].pokInCell.direction;
                        }
                    }
                    else
                    {
                        if (mapa[moveCords2[0]][moveCords2[1]].IsEmpty == true)
                        {
                            mapa[moveCords2[0]][moveCords2[1]].pokInCell = mapa[i][j].pokInCell;
                            mapa[moveCords2[0]][moveCords2[1]].id = mapa[i][j].id;
                            mapa[moveCords2[0]][moveCords2[1]].IsEmpty = mapa[i][j].IsEmpty;
                            mapa[i][j].id = Content::EMPTY;
                            mapa[i][j].IsEmpty = true;
                            code[codesEntered] = mapa[i][j].pokInCell.code;
                            codesEntered++;
                        }
                        else
                        {
                            mapa[i][j].pokInCell.direction = !mapa[i][j].pokInCell.direction;
                        }
                    }
                }
                
            }

        }

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

void PokemonDetection(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, char& direccion,bool& capturing, int& storeX, int& storeY) {

    int middleX = (mapas[0].alto - 2) / 2 + 1;
    int middleY = (mapas[0].ancho - 2) / 2 + 1;

    if (mapa[jugador.x - 1][jugador.y].id == Content::POKEMON) {
        direccion = '<';
        capturing = true;
        storeX = jugador.x - 1;
        storeY = jugador.y;
    }
    if (mapa[jugador.x + 1][jugador.y].id == Content::POKEMON) {
        direccion = '>';
        capturing = true;
        storeX = jugador.x + 1;
        storeY = jugador.y;
    }
    if (mapa[jugador.x][jugador.y - 1].id == Content::POKEMON) {
        direccion = '^';
        capturing = true;
        storeX = jugador.x;
        storeY = jugador.y - 1;
    }
    if (mapa[jugador.x][jugador.y + 1].id == Content::POKEMON) {
        direccion = 'v';
        capturing = true;
        storeX = jugador.x;
        storeY = jugador.y + 1;
    }
}


void Atacar(Player& player, CellInfo**& mapa, int x, int y, bool& capturing, int& pokemonAmountLvl1, int& pokemonAmountLvl2, bool& mewtwoStillOnMap)
{
    mapa[x][y].pokInCell.HP -= player.pikachuDMG;
    if (mapa[x][y].pokInCell.HP <= 0)
    {
        mapa[x][y].id = Content::EMPTY;
        mapa[x][y].IsEmpty = true;
        capturing = false;
        if (player.playerSector == 0)
        {
            pokemonAmountLvl1--;
        }
        if (player.playerSector == 1)
        {
            pokemonAmountLvl2--;
        }
        if (player.playerSector == 2)
        {
            mewtwoStillOnMap = false;
        }
    }
}
void Capturar(Player& player, CellInfo**& mapa, int x, int y, bool& captured, bool& capturing, int& pokemonAmountLvl1, int& pokemonAmountLvl2, bool& mewtwoCaptured, bool& mewtwoStillOnMap)
{
    int chance = rand() % 100;

    if (chance >= mapa[x][y].pokInCell.HP && player.pokeballAmount > 0)
    {
        player.capturedPokemons++;
        mapa[x][y].id = Content::EMPTY;
        mapa[x][y].IsEmpty = true;
        capturing = false;
        captured = true;
        if (player.playerSector == 0)
        {
            pokemonAmountLvl1--;
        }
        if (player.playerSector == 1)
        {
            pokemonAmountLvl2--;
        }
        if (player.playerSector == 2)
        {
            mewtwoStillOnMap = false;
            mewtwoCaptured = true;
        }
    }
    else
    {
        if (mapa[x][y].pokInCell.type == Type::NORMAL)
        {
            captured = false;
        }
        else
        {
            if (player.pokeballAmount > 0)
            {
                captured = false;
            }
            else
            {
                mapa[x][y].id = Content::EMPTY;
                mapa[x][y].IsEmpty = true;
                mewtwoStillOnMap = false;
                capturing = false;
            }
        }
    }

    if (player.pokeballAmount > 0)
    {
        player.pokeballAmount--;
    }
}

void inicializeMewtwo(CellInfo** mapa, MapaConfiguracion mapas[], bool& spawned) 
{
    if (!spawned)
    {
        int middleX = (mapas[0].alto - 2) / 2 + 1;
        int middleY = (mapas[0].ancho - 2) / 2 + 1;
        mapa[middleX + middleX/2][middleY + middleY/2].id = Content::POKEMON;
        Pokemon poke;
        poke.initializePokemonStats(Type::LEGENDARY, mapas);
        mapa[middleX + middleX / 2][middleY + middleY / 2].pokInCell = poke;
        mapa[middleX + middleX / 2][middleY + middleY / 2].IsEmpty = false; 
        spawned = true;
    }

}
