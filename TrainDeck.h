#ifndef TRAIN_DECK_H
#define TRAIN_DECK_H

#include <vector>
#include <string>
#include <random> // Para std::mt19937 y std::shuffle
#include <algorithm> // Para std::shuffle
#include "TrainCard.h" // Incluye la nueva clase TrainCard

class TrainDeck {
private:
    std::vector<TrainCard> mazoRobo;     // Cartas para robar
    std::vector<TrainCard> mazoDescarte; // Cartas descartadas
    std::mt19937 rng; // Generador de números aleatorios

    void reponerMazoRoboDesdeDescarte(); // Método privado para reponer el mazo

public:
    TrainDeck(); // Constructor
    void inicializarMazo(); // Llena el mazo con cartas y lo baraja
    TrainCard robarCarta(); // Roba una carta del mazo de robo
    void descartarCarta(TrainCard carta); // Añade una carta al mazo de descarte

    int getCantidadCartasMazoRobo() const;
    int getCantidadCartasMazoDescarte() const;
    void mostrarMazoDescarte() const; // Para depuración
};

#endif // TRAIN_DECK_H