#pragma once

#include <fstream>
#include <Windows.h>

enum class Content {POKEMON, POKEBALL, ROCK, EMPTY};

enum class Type { NORMAL, LEGENDARY };
enum class MovementType { HORIZONTAL, VERTICAL, DIAGONAL1, DIAGONAL2 };

struct Player {
    int x;
    int y;
    int playerSector;
    int pokeballAmount;
    int capturedPokemons;
    int pikachuDMG;
};

struct MapaConfiguracion {
    int ancho;
    int alto;
    int pokemonsIniciales;
    int pokemonsParaDesbloquear;
    int saludS;
    int saludL;
    int tTMMin;
    int tTMMax;
};

struct Pokemon
{
    Type type;
    MovementType mov;
    std::string name;
    int HP;
    void initializePokemonStats(Type settype, MapaConfiguracion mapa[]);
    void Move(MovementType move);
};


struct CellInfo {
    int PosX;
    int PosY;
    bool IsEmpty;
    Content id;
    Pokemon pokInCell;

    char ContentToChar(Content id);
};

void leerConfiguracion(const std::string& filename, MapaConfiguracion mapas[], int numMapas, Player& jugador);
CellInfo** inicializarMapa(int filas, int columnas);
void liberarMapa(CellInfo** mapa, int filas);
void imprimirMapa(CellInfo** mapa, int filas, int columnas, Player jugador, char direccion);


int DetectPlayerSector(CellInfo** mapa, MapaConfiguracion mapas[], Player& player);
void inicializarPokemons1(int& amountOfPokemonsInMap, CellInfo** mapa, MapaConfiguracion mapas[]);
void inicializarPokemons2(int& amountOfPokemonsInMap, CellInfo** mapa, MapaConfiguracion mapas[]);
void inicizlizarPokeballs(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, bool& pokeballInMap, int pos[]);
void PokemonDetection(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, char& direccion, int& pokemonAmountLvl1, int& pokemonAmountLvl2);
void PokeballColection(CellInfo**& mapa, Player& jugador, bool& pokeballInMap);
