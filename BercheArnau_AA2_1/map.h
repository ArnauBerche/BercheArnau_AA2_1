#pragma once
#include <fstream>
#include <Windows.h>

enum class Content {POKEMON, POKEBALL, ROCK, EMPTY};

enum class Type { NORMAL, LEGENDARY };
enum class MovementType { HORIZONTAL, VERTICAL, DIAGONAL1, DIAGONAL2 , STATIC};

struct Player {
    int x;
    int y;
    int playerSector;
    int pokeballAmount;
    int capturedPokemons;
    int pikachuDMG;
    std::string selectorToName(int playerSector);
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
    int code;
    Type type;
    MovementType mov;
    bool direction = false;
    std::string name;
    int HP;
    void initializePokemonStats(Type settype, MapaConfiguracion mapas[]);
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

void Move(CellInfo** mapa, MapaConfiguracion mapas[]);

int DetectPlayerSector(CellInfo** mapa, MapaConfiguracion mapas[], Player& player);
void inicializarPokemons1(int& amountOfPokemonsInMap, CellInfo** mapa, MapaConfiguracion mapas[]);
void inicializarPokemons2(int& amountOfPokemonsInMap, CellInfo** mapa, MapaConfiguracion mapas[]);
void inicizlizarPokeballs(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, bool& pokeballInMap, int pos[]);
void PokemonDetection(CellInfo**& mapa, MapaConfiguracion mapas[], Player& jugador, char& direccion, bool& capturing, int& storeX, int& storeY);
void PokeballColection(CellInfo**& mapa, Player& jugador, bool& pokeballInMap);


void Atacar(Player& player, CellInfo**& mapa, int x, int y, bool& capturing, int& pokemonAmountLvl1, int& pokemonAmountLvl2, bool& mewtwoStillOnMap);
void Capturar(Player& player, CellInfo**& mapa, int x, int y, bool& captured, bool& capturing, int& pokemonAmountLvl1, int& pokemonAmountLvl2, bool& mewtwoCaptured, bool& mewtwoStillOnMap);

void inicializeMewtwo(CellInfo** mapa, MapaConfiguracion mapas[], bool& spawned);

void Game(int& GameState, int num_FPS, int& timer);
void Menu(int& GameState, int& posInMenu, int& time);