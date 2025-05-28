#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H

#include <vector>
#include <string>
#include <map>
#include "Ciudad.h"
#include "Ruta.h"

// Definiciones de tamaño para el tablero ASCII según la imagen
const int FILAS_DISPLAY = 14;
const int COLUMNAS_DISPLAY = 19;

class BoardRenderer {
private:
    std::vector<std::vector<char>> displayGrid; // La matriz que representa el tablero
    // Un mapa para almacenar las coordenadas (fila, columna) de cada ciudad por su ID
    std::map<int, std::pair<int, int>> ciudadCoordenadas;
    // Un mapa para almacenar la letra de cada ciudad por su ID (para display)
    std::map<int, char> ciudadIDToChar;

    // Métodos privados auxiliares para dibujar
    void inicializarGrid();
    void colocarCiudades(const std::vector<Ciudad*>& ciudades);
    void dibujarSegmentoRuta(int r1, int c1, int r2, int c2, const Ruta& ruta);
    char getRouteChar(char defaultChar, int propietarioID);


public:
    BoardRenderer();

    // Método principal para generar la representación del tablero
    // Necesitará el Mapa (o al menos la información relevante del Mapa)
    void generateBoard(const std::vector<Ciudad*>& ciudades, const std::vector<Ruta>& rutas);

    // Método para imprimir la representación del tablero en la consola
    void renderBoard() const;
};

#endif // BOARD_RENDERER_H