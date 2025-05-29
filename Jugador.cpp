#include "Jugador.h"
#include <iostream>
#include <algorithm>
#include <map>

// Constructor
Jugador::Jugador(int id, std::string nombre, int vagonesIniciales)
    : id(id), nombre(nombre), trenesRestantes(vagonesIniciales), puntos(0) {}

// Getters
int Jugador::getID() const {
    return id;
}

std::string Jugador::getNombre() const {
    return nombre;
}

const std::vector<TrainCard>& Jugador::getManoCartas() const {
    return manoCartas;
}

int Jugador::getTrenesRestantes() const {
    return trenesRestantes;
}

int Jugador::getPuntos() const {
    return puntos;
}

void Jugador::añadirCarta(const TrainCard& carta) {
    manoCartas.push_back(carta);
    // std::cout << nombre << " robó una carta: " << carta.getColor() << ". Cartas en mano: " << manoCartas.size() << std::endl;
}

void Jugador::removerCartas(const std::vector<TrainCard>& cartasARemover) {
    for (const auto& cartaRemover : cartasARemover) {
        // Busca y remueve la primera ocurrencia de la carta por color
        auto it = std::find_if(manoCartas.begin(), manoCartas.end(),
                               [&](const TrainCard& c) { return c.getColor() == cartaRemover.getColor(); });
        if (it != manoCartas.end()) {
            manoCartas.erase(it);
        }
    }
}

void Jugador::gastarTrenes(int cantidad) {
    if (cantidad > 0 && trenesRestantes >= cantidad) {
        trenesRestantes -= cantidad;
        // std::cout << nombre << " gastó " << cantidad << " trenes. Trenes restantes: " << trenesRestantes << std::endl;
    } else {
        std::cerr << "Error: " << nombre << " intentó gastar " << cantidad << " trenes pero solo tiene " << trenesRestantes << "." << std::endl;
    }
}

void Jugador::añadirPuntos(int cantidad) {
    if (cantidad > 0) {
        puntos += cantidad;
        // std::cout << nombre << " ganó " << cantidad << " puntos. Puntos totales: " << puntos << std::endl;
    }
}

void Jugador::mostrarMano() const {
    std::cout << nombre << " (ID: " << id << ", Trenes: " << trenesRestantes << ", Puntos: " << puntos << ") - Cartas en mano (" << manoCartas.size() << "):" << std::endl;
    // Agrupar cartas por color para una mejor visualización
    std::map<std::string, int> conteoCartas;
    for (const auto& carta : manoCartas) {
        conteoCartas[carta.getColor()]++;
    }

    for (const auto& pair : conteoCartas) {
        std::cout << "  - " << pair.first << ": " << pair.second << std::endl;
    }
    if (manoCartas.empty()) {
        std::cout << "  (Vacía)" << std::endl;
    }
}