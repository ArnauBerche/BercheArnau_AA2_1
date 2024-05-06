#ifndef MAP_H
#define MAP_H

#include <fstream>
#include <Windows.h>

using namespace std;

struct Position {
    int x;
    int y;
};

struct MapaConfiguracion {
    int ancho;
    int alto;
    int pokemonsIniciales;
    int pokemonsParaDesbloquear;
};

void leerConfiguracion(const string& filename, MapaConfiguracion mapas[], int numMapas);
char** inicializarMapa(int filas, int columnas);
void liberarMapa(char** mapa, int filas);
void imprimirMapa(char** mapa, int filas, int columnas, Position jugador, char direccion);

#endif