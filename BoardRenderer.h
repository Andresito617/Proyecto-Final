#ifndef BOARD_RENDERER_H
#define BOARD_RENDERER_H
#include <vector>
#include <string>
#include <map>
#include "Ciudad.h"
#include "Ruta.h"

const int FILAS_DISPLAY = 14;
const int COLUMNAS_DISPLAY = 19;

class BoardRenderer {
private:
    std::vector<std::vector<char>> displayGrid;
    std::map<int, std::pair<int, int>> ciudadCoordenadas;
    std::map<int, char> ciudadIDToChar;
    std::map<std::string, char> colorToCharRuta;
    std::map<std::string, std::string> colorToAnsiCode;
    std::vector<std::vector<std::string>> colorGrid;
    void inicializarGrid();
    void colocarCiudades(const std::vector<Ciudad*>& ciudades);
    void dibujarSegmentoRuta(int r1, int c1, int r2, int c2, const Ruta& ruta);
    std::string getAnsiColorCode(const std::string& colorRuta) const;
    char getRouteChar(char defaultChar, int propietarioID, const std::string& colorRuta);
    
public:
    BoardRenderer();
    void generateBoard(const std::vector<Ciudad*>& ciudades, const std::vector<Ruta>& rutas);
    void renderBoard() const;
};

#endif // BOARD_RENDERER_H