#include "BoardRenderer.h"
#include <iostream>
#include <iomanip>
#include <cmath>  

BoardRenderer::BoardRenderer() {
    inicializarGrid();
    ciudadCoordenadas[0] = {7, 1}; // A (Row 8, Col 2) -> (7, 1)
    ciudadIDToChar[0] = 'A';
    ciudadCoordenadas[1] = {4, 5}; // B (Row 5, Col 6) -> (4, 5)
    ciudadIDToChar[1] = 'B';
    ciudadCoordenadas[2] = {13, 3}; // C (Row 14, Col 4) -> (13, 3)
    ciudadIDToChar[2] = 'C';
    ciudadCoordenadas[3] = {0, 3}; // D (Row 1, Col 4) -> (0, 3)
    ciudadIDToChar[3] = 'D';
    ciudadCoordenadas[4] = {3, 5}; // E (Row 4, Col 6) -> (3, 5)
    ciudadIDToChar[4] = 'E';
    ciudadCoordenadas[5] = {7, 6}; // F (Row 8, Col 7) -> (7, 6)
    ciudadIDToChar[5] = 'F';
    ciudadCoordenadas[6] = {10, 6}; // G (Row 11, Col 7) -> (10, 6)
    ciudadIDToChar[6] = 'G';
    ciudadCoordenadas[7] = {7, 8}; // H (Row 8, Col 9) -> (7, 8)
    ciudadIDToChar[7] = 'H';
    ciudadCoordenadas[8] = {4, 9}; // I (Row 5, Col 10) -> (4, 9)
    ciudadIDToChar[8] = 'I';
    ciudadCoordenadas[9] = {2, 10}; // J (Row 3, Col 11) -> (2, 10)
    ciudadIDToChar[9] = 'J';
    ciudadCoordenadas[10] = {7, 11}; // K (Row 8, Col 12) -> (7, 11)
    ciudadIDToChar[10] = 'K';
    ciudadCoordenadas[11] = {10, 11}; // L (Row 11, Col 12) -> (10, 11)
    ciudadIDToChar[11] = 'L';
    ciudadCoordenadas[12] = {12, 13}; // M (Row 13, Col 14) -> (12, 13)
    ciudadIDToChar[12] = 'M';
    ciudadCoordenadas[13] = {2, 14}; // N (Row 3, Col 15) -> (2, 14)
    ciudadIDToChar[13] = 'N';
    ciudadCoordenadas[14] = {3, 15}; // O (Row 4, Col 16) -> (3, 15)
    ciudadIDToChar[14] = 'O';
    ciudadCoordenadas[15] = {7, 15}; // P (Row 8, Col 16) -> (7, 15)
    ciudadIDToChar[15] = 'P';
    ciudadCoordenadas[16] = {11, 15}; // Q (Row 12, Col 16) -> (11, 15)
    ciudadIDToChar[16] = 'Q';
    ciudadCoordenadas[17] = {5, 18}; // R (Row 6, Col 19) -> (5, 18)
    ciudadIDToChar[17] = 'R';
    ciudadCoordenadas[18] = {9, 18}; // S (Row 10, Col 19) -> (9, 18)
    ciudadIDToChar[18] = 'S';
}

void BoardRenderer::inicializarGrid() {
    displayGrid.assign(FILAS_DISPLAY, std::vector<char>(COLUMNAS_DISPLAY, ' '));
}

void BoardRenderer::colocarCiudades(const std::vector<Ciudad*>& ciudades) {
    for (const auto& ciudadPtr : ciudades) {
        if (ciudadPtr) {
            int id = ciudadPtr->getID();
            if (ciudadCoordenadas.count(id) && ciudadIDToChar.count(id)) {
                int r = ciudadCoordenadas[id].first;
                int c = ciudadCoordenadas[id].second;
                if (r >= 0 && r < FILAS_DISPLAY && c >= 0 && c < COLUMNAS_DISPLAY) {
                    displayGrid[r][c] = ciudadIDToChar[id];
                }
            }
        }
    }
}

char BoardRenderer::getRouteChar(char defaultChar, int propietarioID) {
    return (propietarioID != -1) ? 'X' : ' ';
}

void BoardRenderer::dibujarSegmentoRuta(int r1, int c1, int r2, int c2, const Ruta& ruta) {
    if (r1 == r2) { // Horizontal
        int startC = std::min(c1, c2);
        int endC = std::max(c1, c2);
        for (int c = startC + 1; c < endC; ++c) {
            if (c >= 0 && c < COLUMNAS_DISPLAY && r1 >= 0 && r1 < FILAS_DISPLAY) {
                if (displayGrid[r1][c] == ' ') {
                    displayGrid[r1][c] = getRouteChar('-', ruta.propietarioJugadorID);
                }
            }
        }
    } else if (c1 == c2) { // Vertical
        int startR = std::min(r1, r2);
        int endR = std::max(r1, r2);
        for (int r = startR + 1; r < endR; ++r) {
            if (r >= 0 && r < FILAS_DISPLAY && c1 >= 0 && c1 < COLUMNAS_DISPLAY) {
                if (displayGrid[r][c1] == ' ') {
                    displayGrid[r][c1] = getRouteChar('|', ruta.propietarioJugadorID);
                }
            }
        }
    }
}

void BoardRenderer::generateBoard(const std::vector<Ciudad*>& ciudades, const std::vector<Ruta>& rutas) {
    inicializarGrid();
    colocarCiudades(ciudades);

    for (const auto& ruta : rutas) {
        int id1 = ruta.idOrigenCiudad;
        int id2 = ruta.idDestinoCiudad;

        // D(3)-E(4)
        if ((id1 == 3 && id2 == 4) || (id1 == 4 && id2 == 3)) {
            dibujarSegmentoRuta(0, 3, 3, 3, ruta);
            dibujarSegmentoRuta(3, 3, 3, 5, ruta);
        }
        // E(4)-B(1)
        if ((id1 == 4 && id2 == 1) || (id1 == 1 && id2 == 4)) {
            dibujarSegmentoRuta(3, 5, 4, 5, ruta);
        }
        // B(1)-A(0)
        if ((id1 == 1 && id2 == 0) || (id1 == 0 && id2 == 1)) {
            dibujarSegmentoRuta(4, 5, 7, 5, ruta);
            dibujarSegmentoRuta(7, 1, 7, 5, ruta);
        }
        // A(0)-F(5)
        if ((id1 == 0 && id2 == 5) || (id1 == 5 && id2 == 0)) {
            dibujarSegmentoRuta(7, 1, 7, 6, ruta);
        }
        // F(5)-E(4)
        if ((id1 == 5 && id2 == 4) || (id1 == 4 && id2 == 5)) {
            dibujarSegmentoRuta(3, 5, 7, 5, ruta);
            dibujarSegmentoRuta(7, 5, 7, 6, ruta);
        }
        // F(5)-G(6)
        if ((id1 == 5 && id2 == 6) || (id1 == 6 && id2 == 5)) {
            dibujarSegmentoRuta(7, 6, 10, 6, ruta);
        }
        // G(6)-C(2)
        if ((id1 == 6 && id2 == 2) || (id1 == 2 && id2 == 6)) {
            dibujarSegmentoRuta(10, 3, 10, 6, ruta);
            dibujarSegmentoRuta(10, 3, 13, 3, ruta);
        }
        // H(7)-F(5)
        if ((id1 == 7 && id2 == 5) || (id1 == 5 && id2 == 7)) {
            dibujarSegmentoRuta(7, 6, 7, 8, ruta);
        }
        // H(7)-I(8)
        if ((id1 == 7 && id2 == 8) || (id1 == 8 && id2 == 7)) {
            dibujarSegmentoRuta(4, 9, 7, 9, ruta);
            dibujarSegmentoRuta(7, 8, 7, 9, ruta);
        }
        // I(8)-J(9)
        if ((id1 == 8 && id2 == 9) || (id1 == 9 && id2 == 8)) {
            dibujarSegmentoRuta(2, 10, 4, 10, ruta);
            dibujarSegmentoRuta(4, 9, 4, 10, ruta);
        }
        // J(9)-N(13)
        if ((id1 == 9 && id2 == 13) || (id1 == 13 && id2 == 9)) {
             dibujarSegmentoRuta(2, 10, 2, 14, ruta);
        }
        // N(13)-O(14)
        if ((id1 == 13 && id2 == 14) || (id1 == 14 && id2 == 13)) {
            dibujarSegmentoRuta(2, 14, 3, 14, ruta);
            dibujarSegmentoRuta(3, 14, 3, 15, ruta);
        }
        // O(14)-R(17)
        if ((id1 == 14 && id2 == 17) || (id1 == 17 && id2 == 14)) {
            dibujarSegmentoRuta(3, 15, 5, 15, ruta);
            dibujarSegmentoRuta(5, 15, 5, 18, ruta);
        }
        // R(17)-S(18)
        if ((id1 == 17 && id2 == 18) || (id1 == 18 && id2 == 17)) {
            dibujarSegmentoRuta(5, 18, 9, 18, ruta);
        }
        // K(10)-H(7)
        if ((id1 == 10 && id2 == 7) || (id1 == 7 && id2 == 10)) {
            dibujarSegmentoRuta(7, 8, 7, 11, ruta);
        }
        // K(10)-I(8)
        if ((id1 == 10 && id2 == 8) || (id1 == 8 && id2 == 10)) {
            dibujarSegmentoRuta(4, 9, 7, 9, ruta);
            dibujarSegmentoRuta(7, 9, 7, 11, ruta);
        }
        // K(10)-L(11)
        if ((id1 == 10 && id2 == 11) || (id1 == 11 && id2 == 10)) {
            dibujarSegmentoRuta(7, 11, 10, 11, ruta);
        }
        // K(10)-P(15)
        if ((id1 == 10 && id2 == 15) || (id1 == 15 && id2 == 10)) {
            dibujarSegmentoRuta(7, 11, 7, 15, ruta);
        }
        // L(11)-M(12)
        if ((id1 == 11 && id2 == 12) || (id1 == 12 && id2 == 11)) {
            dibujarSegmentoRuta(10, 11, 12, 11, ruta);
            dibujarSegmentoRuta(12, 11, 12, 13, ruta);
        }
        // L(11)-Q(16)
        if ((id1 == 11 && id2 == 16) || (id1 == 16 && id2 == 11)) {
            dibujarSegmentoRuta(10, 11, 11, 11, ruta);
            dibujarSegmentoRuta(11, 11, 11, 15, ruta);
        }
        // M(12)-Q(16)
        if ((id1 == 12 && id2 == 16) || (id1 == 16 && id2 == 12)) {
            dibujarSegmentoRuta(12, 13, 11, 13, ruta);
            dibujarSegmentoRuta(11, 13, 11, 15, ruta);
        }
        // Q(16)-P(15)
        if ((id1 == 16 && id2 == 15) || (id1 == 15 && id2 == 16)) {
            dibujarSegmentoRuta(7, 15, 11, 15, ruta);
        }
        // P(15)-O(14)
        if ((id1 == 15 && id2 == 14) || (id1 == 14 && id2 == 15)) {
            dibujarSegmentoRuta(3, 15, 7, 15, ruta);
        }
        // P(15)-S(18)
        if ((id1 == 15 && id2 == 18) || (id1 == 18 && id2 == 15)) {
            dibujarSegmentoRuta(7, 15, 9, 15, ruta);
            dibujarSegmentoRuta(9, 15, 9, 18, ruta);
        }
    }
}

void BoardRenderer::renderBoard() const {
    for (int r = 0; r < FILAS_DISPLAY; ++r) {
        for (int c = 0; c < COLUMNAS_DISPLAY; ++c) {
            std::cout << "[";
            if (displayGrid[r][c] == ' ') {
                std::cout << " ";
            } else {
                std::cout << displayGrid[r][c];
            }
            std::cout << "]";
            if (c < COLUMNAS_DISPLAY - 1) {
                std::cout << " ";
            }
        }
        std::cout << std::endl;
    }
}