#include "TrainDeck.h"
#include <iostream>
#include <chrono>

// Constructor
TrainDeck::TrainDeck() : rng(std::chrono::system_clock::now().time_since_epoch().count()) {
}

void TrainDeck::reponerMazoRoboDesdeDescarte() {
    if (mazoDescarte.empty()) {
    }

    std::cout << "Reponiendo mazo de robo desde descarte... Barajando " << mazoDescarte.size() << " cartas." << std::endl;
    mazoRobo.insert(mazoRobo.end(), std::make_move_iterator(mazoDescarte.begin()), std::make_move_iterator(mazoDescarte.end()));
    mazoDescarte.clear();
    std::shuffle(mazoRobo.begin(), mazoRobo.end(), rng);
    std::cout << "Mazo repuesto y barajado. Nuevo tamaño: " << mazoRobo.size() << " cartas." << std::endl;
}

void TrainDeck::inicializarMazo() {
    std::vector<std::string> colores = {"Rojo", "Azul", "Verde", "Morado", "Cafe", "Naranja"};
    const int CARTAS_POR_COLOR = 12;

    for (const std::string& color : colores) {
        for (int i = 0; i < CARTAS_POR_COLOR; ++i) {
            mazoRobo.emplace_back(color);
        }
    }

    // Barajar el mazo inicial
    std::shuffle(mazoRobo.begin(), mazoRobo.end(), rng);
    std::cout << "Mazo de vagones inicializado con " << mazoRobo.size() << " cartas y barajado." << std::endl;
}

// Roba una carta del mazo de robo
TrainCard TrainDeck::robarCarta() {
    if (mazoRobo.empty()) {
        reponerMazoRoboDesdeDescarte();
        if (mazoRobo.empty()) { 
            std::cerr << "Advertencia: No hay más cartas en el mazo para robar." << std::endl;
            return TrainCard("VACIA");
        }
    }
    TrainCard cartaRobada = mazoRobo.back();
    mazoRobo.pop_back();
    return cartaRobada;
}

void TrainDeck::descartarCarta(TrainCard carta) {
    mazoDescarte.push_back(carta);
}

// Getters
int TrainDeck::getCantidadCartasMazoRobo() const {
    return mazoRobo.size();
}

int TrainDeck::getCantidadCartasMazoDescarte() const {
    return mazoDescarte.size();
}

// Para depuración
void TrainDeck::mostrarMazoDescarte() const {
    std::cout << "Cartas en el mazo de descarte (" << mazoDescarte.size() << "):" << std::endl;
    for (const auto& carta : mazoDescarte) {
        carta.mostrarInformacion();
    }
}