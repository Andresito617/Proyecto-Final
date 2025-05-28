#include "TrainDeck.h"
#include <iostream>
#include <chrono> // Para usar el tiempo como semilla

// Constructor
TrainDeck::TrainDeck() : rng(std::chrono::system_clock::now().time_since_epoch().count()) {
    // El constructor inicializa el generador de números aleatorios.
    // La inicialización real del mazo se hace en inicializarMazo().
}

// Repone el mazo de robo usando las cartas del mazo de descarte
void TrainDeck::reponerMazoRoboDesdeDescarte() {
    if (mazoDescarte.empty()) {
        // En un juego real, esto podría significar el final del juego si ya no quedan cartas.
        // Aquí, simplemente notificamos y no hacemos nada si el descarte también está vacío.
        // std::cout << "No hay cartas en el mazo de descarte para reponer el mazo de robo." << std::endl;
        return; // No hay cartas para reponer
    }

    std::cout << "Reponiendo mazo de robo desde descarte... Barajando " << mazoDescarte.size() << " cartas." << std::endl;
    // Mueve todas las cartas del descarte al mazo de robo
    mazoRobo.insert(mazoRobo.end(), std::make_move_iterator(mazoDescarte.begin()), std::make_move_iterator(mazoDescarte.end()));
    mazoDescarte.clear(); // Vacía el mazo de descarte

    // Baraja el nuevo mazo de robo
    std::shuffle(mazoRobo.begin(), mazoRobo.end(), rng);
    std::cout << "Mazo repuesto y barajado. Nuevo tamaño: " << mazoRobo.size() << " cartas." << std::endl;
}

// Llena el mazo con cartas y lo baraja
void TrainDeck::inicializarMazo() {
    // Definir los colores SEGÚN LA RÚBRICA
    std::vector<std::string> colores = {"Rojo", "Azul", "Verde", "Morado", "Cafe", "Naranja"}; // Ajustado: 6 colores
    const int CARTAS_POR_COLOR = 12; // 12 cartas de cada color, SEGÚN LA RÚBRICA

    // NOTA IMPORTANTE: La rúbrica NO menciona cartas de Locomotora en esta sección.
    // Por lo tanto, las eliminamos para cumplir estrictamente con el requisito.

    // Añadir cartas de vagón por color
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
        reponerMazoRoboDesdeDescarte(); // Intenta reponer si el mazo de robo está vacío
        if (mazoRobo.empty()) { // Si después de reponer sigue vacío (ej. no había descarte)
            std::cerr << "Advertencia: No hay más cartas en el mazo para robar." << std::endl;
            return TrainCard("VACIA"); // Retorna una carta "vacía" o inválida
        }
    }
    TrainCard cartaRobada = mazoRobo.back();
    mazoRobo.pop_back();
    return cartaRobada;
}

// Añade una carta al mazo de descarte
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