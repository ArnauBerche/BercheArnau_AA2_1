#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

void leerConfiguracion(const string& filename, MapaConfiguracion mapas[], int numMapas) {
    ifstream archivo(filename);
    if (archivo.is_open()) {

        string linea;
        if (getline(archivo, linea)) {
            stringstream ss(linea);
            string token;
            getline(ss, token, ';');
            for (int i = 0; i < numMapas; ++i) {
                mapas[i].ancho = stoi(token);
            }
            getline(ss, token, ';');
            for (int i = 0; i < numMapas; ++i) {
                mapas[i].alto = stoi(token);
            }
        }
        else {
            cerr << "Error: Se esperaba una línea en el archivo de configuración." << endl;
        }
        if (getline(archivo, linea)) {
            stringstream ss(linea);
            string token;
            getline(ss, token, ';');
            mapas[0].pokemonsIniciales = stoi(token);
            getline(ss, token, ';');
            mapas[0].pokemonsParaDesbloquear = stoi(token);
        }
        else {
            cerr << "Error: Se esperaba una línea en el archivo de configuración." << endl;
        }
        if (getline(archivo, linea)) {
            stringstream ss(linea);
            string token;
            getline(ss, token, ';');
            mapas[1].pokemonsIniciales = stoi(token);
            getline(ss, token, ';');
            mapas[1].pokemonsParaDesbloquear = stoi(token);
        }
        else {
            cerr << "Error: Se esperaba una línea en el archivo de configuración." << endl;
        }
        archivo.close();
    }
    else {
        cerr << "Error: No se pudo abrir el archivo de configuración." << endl;
    }
    mapas[2].pokemonsIniciales = 0;
    mapas[2].pokemonsParaDesbloquear = 0;
    mapas[3].pokemonsIniciales = 0;
    mapas[3].pokemonsParaDesbloquear = 0;
}

void liberarMapa(char** mapa, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;
}

char** inicializarMapa(int filas, int columnas) {
    char** mapa = new char* [filas];
    for (int i = 0; i < filas; ++i) {
        mapa[i] = new char[columnas];
        for (int j = 0; j < columnas; ++j) {
            if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1)
            {
                mapa[i][j] = 'X';
            }
            else if (i == filas / 2 || j == columnas / 2)
            {
                mapa[i][j] = 'X';
            }
            else {
                mapa[i][j] = ' ';
            }
        }
    }
    return mapa;
}

void imprimirMapa(char** mapa, int filas, int columnas, Position jugador, char direccion) {
    int vistaAltura = 11;
    int vistaAnchura = 21;

    int vistaInicioX = max(0, jugador.x - vistaAnchura / 2);
    int vistaInicioY = max(0, jugador.y - vistaAltura / 2);

    int vistaFinX = min(columnas - 1, vistaInicioX + vistaAnchura);
    int vistaFinY = min(filas - 1, vistaInicioY + vistaAltura);

    for (int i = vistaInicioY; i <= vistaFinY; ++i) {
        for (int j = vistaInicioX; j <= vistaFinX; ++j) {
            if (i == jugador.y && j == jugador.x) {
                cout << " " << direccion;
            }
            else {
                cout << " " << mapa[j][i];
            }
        }
        cout << endl;
    }
}