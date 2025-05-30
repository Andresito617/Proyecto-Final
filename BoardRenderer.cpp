#include "BoardRenderer.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

BoardRenderer::BoardRenderer() {
    inicializarGrid();
    ciudadCoordenadas[0] = {8-1, 1-1};
    ciudadIDToChar[0] = 'A';
    ciudadCoordenadas[1] = {5-1, 3-1};
    ciudadIDToChar[1] = 'B';
    ciudadCoordenadas[2] = {14-1, 3-1};
    ciudadIDToChar[2] = 'C';
    ciudadCoordenadas[3] = {1-1, 4-1};
    ciudadIDToChar[3] = 'D';
    ciudadCoordenadas[4] = {4-1, 6-1};
    ciudadIDToChar[4] = 'E';
    ciudadCoordenadas[5] = {8-1, 6-1};
    ciudadIDToChar[5] = 'F';
    ciudadCoordenadas[6] = {12-1, 6-1};
    ciudadIDToChar[6] = 'G';
    ciudadCoordenadas[7] = {8-1, 9-1};
    ciudadIDToChar[7] = 'H';
    ciudadCoordenadas[8] = {5-1, 10-1};
    ciudadIDToChar[8] = 'I';
    ciudadCoordenadas[9] = {2-1, 11-1}; 
    ciudadIDToChar[9] = 'J';
    ciudadCoordenadas[10] = {8-1, 12-1}; 
    ciudadIDToChar[10] = 'K';
    ciudadCoordenadas[11] = {12-1, 12-1};
    ciudadIDToChar[11] = 'L';
    ciudadCoordenadas[12] = {14-1, 13-1};
    ciudadIDToChar[12] = 'M';
    ciudadCoordenadas[13] = {2-1, 14-1}; 
    ciudadIDToChar[13] = 'N';
    ciudadCoordenadas[14] = {4-1, 16-1};
    ciudadIDToChar[14] = 'O';
    ciudadCoordenadas[15] = {8-1, 16-1}; 
    ciudadIDToChar[15] = 'P';
    ciudadCoordenadas[16] = {12-1, 16-1};
    ciudadIDToChar[16] = 'Q';
    ciudadCoordenadas[17] = {6-1, 19-1}; 
    ciudadIDToChar[17] = 'R';
    ciudadCoordenadas[18] = {10-1, 19-1}; 
    ciudadIDToChar[18] = 'S';

    // NUEVO: Inicializar el mapeo de colores a caracteres para las rutas
    colorToAnsiCode["Rojo"] = "\033[31m";    // Rojo
    colorToAnsiCode["Azul"] = "\033[34m";    // Azul
    colorToAnsiCode["Verde"] = "\033[32m";   // Verde
    colorToAnsiCode["Morado"] = "\033[35m";  // Magenta (el más cercano al morado)
    colorToAnsiCode["Cafe"] = "\033[33m";    // Amarillo (comúnmente usado para café/marrón)
    colorToAnsiCode["Naranja"] = "\033[38;5;208m";
}

void BoardRenderer::inicializarGrid() {
    displayGrid.assign(FILAS_DISPLAY, std::vector<char>(COLUMNAS_DISPLAY, ' '));
    colorGrid.assign(FILAS_DISPLAY, std::vector<std::string>(COLUMNAS_DISPLAY, "\033[0m"));
}

void BoardRenderer::colocarCiudades(const std::vector<Ciudad*>& ciudades) {
    const std::string COLOR_BLANCO_RESET = "\033[0m";

    for (const auto& ciudad : ciudades) {
        int id = ciudad->id;
        if (ciudadCoordenadas.count(id)) {
            int r = ciudadCoordenadas[id].first;
            int c = ciudadCoordenadas[id].second;
            
            if (r >= 0 && r < FILAS_DISPLAY && c >= 0 && c < COLUMNAS_DISPLAY) {
                displayGrid[r][c] = ciudadIDToChar[id];
                colorGrid[r][c] = COLOR_BLANCO_RESET; 
            }
        }
    }
}

std::string BoardRenderer::getAnsiColorCode(const std::string& colorRuta) const {
    auto it = colorToAnsiCode.find(colorRuta);
    if (it != colorToAnsiCode.end()) {
        return it->second;
    }
    return "\033[0m"; // Color por defecto (reset) si no se encuentra
}

// MODIFICADA: Ahora recibe el color de la ruta
char BoardRenderer::getRouteChar(char defaultChar, int propietarioID, const std::string& colorRuta) {
    if (propietarioID != -1) {
        return 'X'; // La ruta está reclamada, muestra 'X'
    } else {
        // La ruta está libre, muestra el carácter correspondiente a su color
        auto it = colorToCharRuta.find(colorRuta);
        if (it != colorToCharRuta.end()) {
            return it->second; // Retorna el carácter asignado al color
        }
        return defaultChar; // Si el color no está mapeado, usa el carácter por defecto ('-' o '|')
    }
}

// En BoardRenderer.cpp, la función dibujarSegmentoRuta

// En BoardRenderer.cpp, la función dibujarSegmentoRuta

void BoardRenderer::dibujarSegmentoRuta(int r1, int c1, int r2, int c2, const Ruta& ruta) {
    int display_r1 = r1 - 1;
    int display_c1 = c1 - 1;
    int display_r2 = r2 - 1;
    int display_c2 = c2 - 1;

    char routeChar = 'X'; // <-- Siempre queremos la 'X'

    std::string ansiColor;

    if (ruta.propietarioJugadorID != -1) {
        // Si la ruta tiene propietario, la 'X' se pondrá del color del jugador.
        // Aquí necesitarías el color del jugador. Por ahora, asumimos blanco o un color genérico.
        ansiColor = "\033[37m"; // Blanco para rutas tomadas, o el color de un jugador
        // Si tienes acceso al color del jugador (ej. una función getPlayerColor(id)), úsala aquí.
        // Ejemplo: ansiColor = getPlayerColorCode(ruta.propietarioJugadorID);
    } else {
        // Si no tiene propietario, la 'X' se pondrá del color de la ruta (Rojo, Azul, Marron, etc.)
        ansiColor = getAnsiColorCode(ruta.color);
    }

    // Ahora usamos las coordenadas ajustadas a base 0
    if (display_r1 == display_r2) { // Horizontal
        int startC = std::min(display_c1, display_c2);
        int endC = std::max(display_c1, display_c2);
        for (int c = startC; c <= endC; ++c) {
            if (c >= 0 && c < COLUMNAS_DISPLAY && display_r1 >= 0 && display_r1 < FILAS_DISPLAY) {
                displayGrid[display_r1][c] = routeChar;
                colorGrid[display_r1][c] = ansiColor;
            }
        }
    } else if (display_c1 == display_c2) { // Vertical
        int startR = std::min(display_r1, display_r2);
        int endR = std::max(display_r1, display_r2);
        for (int r = startR; r <= endR; ++r) {
            if (r >= 0 && r < FILAS_DISPLAY && display_c1 >= 0 && display_c1 < COLUMNAS_DISPLAY) {
                displayGrid[r][display_c1] = routeChar;
                colorGrid[r][display_c1] = ansiColor;
            }
        }
    }
}

void BoardRenderer::generateBoard(const std::vector<Ciudad*>& ciudades, const std::vector<Ruta>& rutas) {
    inicializarGrid(); 
    
    for (const auto& ruta : rutas) {
        int id1 = ruta.idOrigenCiudad;
        int id2 = ruta.idDestinoCiudad;

        // --- RUTA A(0)-B(1) ---
        if ((id1 == 0 && id2 == 1) || (id1 == 1 && id2 == 0)) {
            dibujarSegmentoRuta(8, 1, 5, 1, ruta); // X en (8,1), (7,1), (6,1), (5,1)
            dibujarSegmentoRuta(5, 1, 5, 2, ruta); // X en (5,1), (5,2)
        }

        // --- RUTA A(0)-F(5) ---
        if ((id1 == 0 && id2 == 5) || (id1 == 5 && id2 == 0)) {
            dibujarSegmentoRuta(8, 2, 8, 5, ruta); // X en (8,2), (8,3), (8,4), (8,5)
        }

        // --- RUTA D(3)-E(4) ---
        if ((id1 == 3 && id2 == 4) || (id1 == 4 && id2 == 3)) {
            dibujarSegmentoRuta(1, 5, 1, 6, ruta); // X en (1,5), (1,6)
            dibujarSegmentoRuta(1, 6, 3, 6, ruta); // X en (1,6), (2,6), (3,6)
        }

        // --- RUTA E(4)-F(5) ---
        if ((id1 == 4 && id2 == 5) || (id1 == 5 && id2 == 4)) {
            dibujarSegmentoRuta(5, 6, 7, 6, ruta); // X en (5,6), (6,6), (7,6)
        }

        // --- RUTA F(5)-G(6) ---
        if ((id1 == 5 && id2 == 6) || (id1 == 6 && id2 == 5)) {
            dibujarSegmentoRuta(9, 6, 11, 6, ruta); // X en (9,6), (10,6), (11,6)
        }

        // --- RUTA G(6)-C(2) --- (CORREGIDA)
        if ((id1 == 6 && id2 == 2) || (id1 == 2 && id2 == 6)) {
            dibujarSegmentoRuta(12, 5, 12, 3, ruta); // X en (12,5), (12,4), (12,3)
            dibujarSegmentoRuta(12, 3, 13, 3, ruta); // X en (12,3), (13,3)
        }

        // --- RUTA F(5)-H(7) --- (Interpretada como H-F)
        if ((id1 == 5 && id2 == 7) || (id1 == 7 && id2 == 5)) {
            dibujarSegmentoRuta(8, 7, 8, 8, ruta); // X en (8,7), (8,8)
        }
        
        // --- RUTA H(7)-K(10) ---
        if ((id1 == 7 && id2 == 10) || (id1 == 10 && id2 == 7)) {
            dibujarSegmentoRuta(8, 10, 8, 11, ruta); // X en (8,10), (8,11)
        }

        // --- RUTA H(7)-L(11) --- (CORREGIDA)
        if ((id1 == 7 && id2 == 11) || (id1 == 11 && id2 == 7)) {
            dibujarSegmentoRuta(9, 9, 12, 9, ruta); // X en (9,9), (10,9), (11,9), (12,9)
            dibujarSegmentoRuta(12, 9, 12, 11, ruta); // X en (12,9), (12,10), (12,11)
        }

        // --- RUTA I(8)-O(14) --- (CORREGIDO DE NUEVO, según tu última descripción)
        if ((id1 == 8 && id2 == 14) || (id1 == 14 && id2 == 8)) {
            dibujarSegmentoRuta(4, 10, 4, 15, ruta); // X en (4,10), (4,11), (4,12), (4,13), (4,14), (4,15)
        }

        // --- RUTA J(9)-N(13) ---
        if ((id1 == 9 && id2 == 13) || (id1 == 13 && id2 == 9)) {
            dibujarSegmentoRuta(2, 12, 2, 13, ruta); // X en (2,12), (2,13)
        }

        // --- RUTA I(8)-K(10) --- (CORREGIDO)
        if ((id1 == 8 && id2 == 10) || (id1 == 10 && id2 == 8)) {
            dibujarSegmentoRuta(6, 10, 6, 12, ruta); // X en (6,10), (6,11), (6,12)
            dibujarSegmentoRuta(6, 12, 7, 12, ruta); // X en (6,12), (7,12)
        }

        // --- RUTA K(10)-L(11) ---
        if ((id1 == 10 && id2 == 11) || (id1 == 11 && id2 == 10)) {
            dibujarSegmentoRuta(9, 12, 11, 12, ruta); // X en (9,12), (10,12), (11,12)
        }

        // --- RUTA K(10)-P(15) ---
        if ((id1 == 10 && id2 == 15) || (id1 == 15 && id2 == 10)) {
            dibujarSegmentoRuta(8, 13, 8, 15, ruta); // X en (8,13), (8,14), (8,15)
        }

        // --- RUTA N(13)-O(14) --- (CORREGIDO)
        if ((id1 == 13 && id2 == 14) || (id1 == 14 && id2 == 13)) {
            dibujarSegmentoRuta(2, 15, 2, 16, ruta); // X en (2,15), (2,16)
            dibujarSegmentoRuta(2, 16, 3, 16, ruta); // X en (2,16), (3,16)
        }

        // --- RUTA O(14)-P(15) ---
        if ((id1 == 14 && id2 == 15) || (id1 == 15 && id2 == 14)) {
            dibujarSegmentoRuta(5, 16, 7, 16, ruta); // X en (5,16), (6,16), (7,16)
        }

        // --- RUTA O(14)-R(17) --- (CORREGIDO)
        if ((id1 == 14 && id2 == 17) || (id1 == 17 && id2 == 14)) {
            dibujarSegmentoRuta(4, 17, 4, 19, ruta); // X en (4,17), (4,18), (4,19)
            dibujarSegmentoRuta(4, 19, 5, 19, ruta); // X en (4,19), (5,19)
        }

        // --- RUTA P(15)-Q(16) ---
        // NOTA: Esta ruta no estaba en tu última recapitulación. Si no existe, bórrala manualmente.
        if ((id1 == 15 && id2 == 16) || (id1 == 16 && id2 == 15)) {
            dibujarSegmentoRuta(9, 16, 11, 16, ruta); // X en (9,16), (10,16), (11,16)
        }

        // --- RUTA Q(16)-M(12) --- (CORREGIDA)
        if ((id1 == 16 && id2 == 12) || (id1 == 12 && id2 == 16)) {
            dibujarSegmentoRuta(13, 16, 14, 16, ruta); // X en (13,16), (14,16)
            dibujarSegmentoRuta(14, 15, 14, 14, ruta); // X en (14,15), (14,14)
            dibujarSegmentoRuta(14, 14, 14, 13, ruta); // X en (14,14), (14,13)
        }

        // --- RUTA Q(16)-S(18) --- (CORREGIDO DE NUEVO)
        if ((id1 == 16 && id2 == 18) || (id1 == 18 && id2 == 16)) {
            dibujarSegmentoRuta(12, 17, 12, 19, ruta); // X en (12,17), (12,18), (12,19)
            dibujarSegmentoRuta(10, 19, 12, 19, ruta); // X en (10,19), (11,19), (12,19)
        }

    }
    
    colocarCiudades(ciudades);
}

void BoardRenderer::renderBoard() const {
    const std::string RESET_COLOR = "\033[0m"; // Código para resetear el color

    for (int r = 0; r < FILAS_DISPLAY; ++r) {
        for (int c = 0; c < COLUMNAS_DISPLAY; ++c) {
            std::cout << "[";
            // Imprimir el color si es un trayecto o ciudad
            if (displayGrid[r][c] != ' ') {
                std::cout << colorGrid[r][c]; // Aplicar el código de color ANSI
                std::cout << displayGrid[r][c]; // Imprimir el carácter (ciudad o 'X')
                std::cout << RESET_COLOR;     // Resetear el color después de imprimir el carácter
            } else {
                std::cout << " "; // Espacio vacío
            }
            std::cout << "]";
            if (c < COLUMNAS_DISPLAY - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}