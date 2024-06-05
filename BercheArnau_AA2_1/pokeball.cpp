#include "map.h"
#include <iostream>

void inicizlizarPokeballs(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, bool& pokeballInMap, int pos[])
{
    int middleX = (mapas[0].alto - 2) / 2 + 1;
    int middleY = (mapas[0].ancho - 2) / 2 + 1;
    if (!pokeballInMap)
    {
        if (jugador.playerSector == 0)
        {
            int pokeballPosY = rand() % (middleY);
            int pokeballPosX = rand() % (middleX);
            if (mapa[pokeballPosX][pokeballPosY].IsEmpty)
            {
                mapa[pokeballPosX][pokeballPosY].id = Content::POKEBALL;
                pos[0] = pokeballPosY;
                pos[1] = pokeballPosX;
                pokeballInMap = true;
            }
        }
        if (jugador.playerSector == 1)
        {
            int pokeballPosY = rand() % (middleY);
            int pokeballPosX = rand() % (middleX)+(middleX + 1);
            if (mapa[pokeballPosX][pokeballPosY].IsEmpty)
            {
                mapa[pokeballPosX][pokeballPosY].id = Content::POKEBALL;
                pos[0] = pokeballPosY;
                pos[1] = pokeballPosX;
                pokeballInMap = true;
            }
        }
    }
    else if (jugador.playerSector == 5)
    {
        pokeballInMap = false;
        mapa[pos[1]][pos[0]].IsEmpty = true;
        mapa[pos[1]][pos[0]].id = Content::EMPTY;

    }
}


void PokeballColection(CellInfo**& mapa, Player& jugador, bool& pokeballInMap)
{
    if (mapa[jugador.x][jugador.y].id == Content::POKEBALL && pokeballInMap)
    {
        mapa[jugador.x][jugador.y].id = Content::EMPTY;
        mapa[jugador.x][jugador.y].IsEmpty = true;
        pokeballInMap = false;
        jugador.pokeballAmount++;
    }
}