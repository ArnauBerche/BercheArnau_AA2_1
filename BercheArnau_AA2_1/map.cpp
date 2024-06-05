#include "map.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

char CellInfo::ContentToChar(Content id)
{
    switch (id)
    {
    case Content::POKEMON:
        if (pokInCell.type == Type::NORMAL)
        {
            return 'P';
        }
        else 
        {
            return 'M';
        }
        break;
    case Content::POKEBALL:
        return 'O';
        break;
    case Content::ROCK:
        return 'X';
        break;
    case Content::EMPTY:
        return ' ';
        break;
    default:
        break;
    }

}

void leerConfiguracion(const std::string& filename, MapaConfiguracion mapas[], int numMapas, Player& jugador) {
    std::ifstream archivo(filename);
    if (archivo.is_open()) {
        std::string linea;
        if (getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string token;
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
            std::cerr << "Error: Se esperaba una línea en el archivo de configuración." << std::endl;
        }
        if (getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string token;
            getline(ss, token, ';');
            mapas[0].pokemonsIniciales = stoi(token);
            getline(ss, token, ';');
            mapas[0].pokemonsParaDesbloquear = stoi(token);
        }
        else {
            std::cerr << "Error: Se esperaba una línea en el archivo de configuración." << std::endl;
        }
        if (getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string token;
            getline(ss, token, ';');
            mapas[1].pokemonsIniciales = stoi(token);
            getline(ss, token, ';');
            mapas[1].pokemonsParaDesbloquear = stoi(token);
        }
        else {
            std::cerr << "Error: Se esperaba una línea en el archivo de configuración." << std::endl;
        }
        if (getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string token;
            getline(ss, token, ';');
            jugador.pikachuDMG = stoi(token);
        }
        else {
            std::cerr << "Error: Se esperaba una línea en el archivo de configuración." << std::endl;
        }
        if (getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string token;
            getline(ss, token, ';');
            mapas[0].saludS = stoi(token);
            getline(ss, token, ';');
            mapas[0].saludL = stoi(token);
        }
        else {
            std::cerr << "Error: Se esperaba una línea en el archivo de configuración." << std::endl;
        }
        if (getline(archivo, linea)) {
            std::stringstream ss(linea);
            std::string token;
            getline(ss, token, ';');
            mapas[0].tTMMin = stoi(token);
            getline(ss, token, ';');
            mapas[0].tTMMax = stoi(token);
        }
        else {
            std::cerr << "Error: Se esperaba una línea en el archivo de configuración." << std::endl;
        }
        archivo.close();
    }
    else {
        std::cerr << "Error: No se pudo abrir el archivo de configuración." << std::endl;
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

CellInfo** inicializarMapa(int filas, int columnas) {
    CellInfo** mapa = new CellInfo * [filas];
    for (int i = 0; i < filas; ++i) {
        mapa[i] = new CellInfo[columnas];
        for (int j = 0; j < columnas; ++j) {
            mapa[i][j].PosX = i;
            mapa[i][j].PosY = j;
            if (i == 0 || i == filas - 1 || j == 0 || j == columnas - 1 || i == filas / 2 || j == columnas / 2) {
                mapa[i][j].IsEmpty = false;
                mapa[i][j].id = Content::ROCK;
            }
            else {
                mapa[i][j].IsEmpty = true;
                mapa[i][j].id = Content::EMPTY;
            }
        }
    }
    return mapa;
}

void liberarMapa(CellInfo** mapa, int filas) {
    for (int i = 0; i < filas; ++i) {
        delete[] mapa[i];
    }
    delete[] mapa;
}

void imprimirMapa(CellInfo** mapa, int filas, int columnas, Player jugador, char direccion) {
    int vistaAltura = 20;
    int vistaAnchura = 20;

    int maxColumnLength = 0;
    for (int j = 0; j < columnas; ++j) {
        int columnLength = 0;
        for (int i = 0; i < filas; ++i) {
            if (!mapa[i][j].IsEmpty) {
                columnLength++;
            }
        }
        maxColumnLength = max(maxColumnLength, columnLength);
    }

    vistaAltura = min(vistaAltura, maxColumnLength);

    int vistaInicioX = max(0, jugador.y - vistaAnchura / 2);
    int vistaInicioY = max(0, jugador.x - vistaAltura / 2);

    int vistaFinX = min(columnas - 1, vistaInicioX + vistaAnchura);
    int vistaFinY = min(filas - 1, vistaInicioY + vistaAltura);

    for (int j = vistaInicioX; j <= vistaFinX; ++j) {
        for (int i = vistaInicioY; i <= vistaFinY; ++i) {
            if (i == jugador.x && j == jugador.y) {
                std::cout << " " << direccion;
            }
            else {
                std::cout << " " << mapa[i][j].ContentToChar(mapa[i][j].id);
            }
        }
        std::cout << std::endl;
    }
}

int DetectPlayerSector(CellInfo** mapa, MapaConfiguracion mapas[],Player& player)
{
    int middleX = (mapas[0].alto - 2) / 2 + 1;
    int middleY = (mapas[0].ancho - 2) / 2 + 1;

    if (player.y > 0 && player.y < middleY && player.x > 0 && player.x < middleX)
    {
        return 0;
    }
    else if (player.y > 0 && player.y < middleY && player.x > middleX && player.x < middleX + middleX)
    {
        return 1;
    }
    else if (player.y > middleY && player.y < middleY + middleY && player.x > middleX && player.x < middleX + middleX)
    {
        return 2;
    }
    else if (player.y > middleY && player.y < middleY + middleY && player.x > 0 && player.x < middleX)
    {
        return 3;
    }
    else
    {
        return 5;
    }
}
