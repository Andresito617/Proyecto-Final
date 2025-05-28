#include "Mapa.h"
#include "Ruta.h"
#include "BoardRenderer.h" // Nuevo nombre
#include <iostream>
#include <algorithm>

// Constructor, destructor y métodos BST auxiliares con nombres actualizados
Mapa::Mapa() : raiz(nullptr) {}

Mapa::~Mapa() {
    destruirBST(raiz);
}

CiudadNode* Mapa::insertarCiudadRecursivo(CiudadNode* nodo, Ciudad& ciudad) {
    if (nodo == nullptr) {
        return new CiudadNode(ciudad);
    }
    if (ciudad.getID() < nodo->ciudad.getID()) {
        nodo->izquierda = insertarCiudadRecursivo(nodo->izquierda, ciudad);
    } else if (ciudad.getID() > nodo->ciudad.getID()) {
        nodo->derecha = insertarCiudadRecursivo(nodo->derecha, ciudad);
    }
    return nodo;
}

void Mapa::insertarCiudad(Ciudad ciudad) {
    raiz = insertarCiudadRecursivo(raiz, ciudad);
}

CiudadNode* Mapa::buscarCiudadRecursivo(CiudadNode* nodo, int idCiudad) const {
    if (nodo == nullptr || nodo->ciudad.getID() == idCiudad) {
        return nodo;
    }
    if (idCiudad < nodo->ciudad.getID()) {
        return buscarCiudadRecursivo(nodo->izquierda, idCiudad);
    } else {
        return buscarCiudadRecursivo(nodo->derecha, idCiudad);
    }
}

Ciudad* Mapa::buscarCiudad(int idCiudad) {
    CiudadNode* nodo = buscarCiudadRecursivo(raiz, idCiudad);
    return (nodo != nullptr) ? &(nodo->ciudad) : nullptr;
}

void Mapa::destruirBST(CiudadNode* nodo) {
    if (nodo != nullptr) {
        destruirBST(nodo->izquierda);
        destruirBST(nodo->derecha);
        delete nodo;
    }
}

void Mapa::recolectarCiudades(CiudadNode* nodo, std::vector<Ciudad*>& ciudades) const {
    if (nodo != nullptr) {
        recolectarCiudades(nodo->izquierda, ciudades);
        ciudades.push_back(&(nodo->ciudad));
        recolectarCiudades(nodo->derecha, ciudades);
    }
}

std::vector<Ciudad*> Mapa::getTodasLasCiudades() const {
    std::vector<Ciudad*> ciudadesEncontradas;
    recolectarCiudades(raiz, ciudadesEncontradas);
    return ciudadesEncontradas;
}

const std::vector<Ruta>& Mapa::getTodasLasRutas() const {
    return todasLasRutas;
}

// inicializarMapa (sin cambios, ya que crea las ciudades y rutas con sus IDs)
void Mapa::inicializarMapa() {
    // 1. Crear las 19 ciudades (A-S) y añadirlas al BST
    insertarCiudad(Ciudad("A", 0)); // ID 0
    insertarCiudad(Ciudad("B", 1)); // ID 1
    insertarCiudad(Ciudad("C", 2)); // ID 2
    insertarCiudad(Ciudad("D", 3)); // ID 3
    insertarCiudad(Ciudad("E", 4)); // ID 4
    insertarCiudad(Ciudad("F", 5)); // ID 5
    insertarCiudad(Ciudad("G", 6)); // ID 6
    insertarCiudad(Ciudad("H", 7)); // ID 7
    insertarCiudad(Ciudad("I", 8)); // ID 8
    insertarCiudad(Ciudad("J", 9)); // ID 9
    insertarCiudad(Ciudad("K", 10)); // ID 10
    insertarCiudad(Ciudad("L", 11)); // ID 11
    insertarCiudad(Ciudad("M", 12)); // ID 12
    insertarCiudad(Ciudad("N", 13)); // ID 13
    insertarCiudad(Ciudad("O", 14)); // ID 14
    insertarCiudad(Ciudad("P", 15)); // ID 15
    insertarCiudad(Ciudad("Q", 16)); // ID 16
    insertarCiudad(Ciudad("R", 17)); // ID 17
    insertarCiudad(Ciudad("S", 18)); // ID 18

    // 2. Crear las 24 rutas predefinidas y añadirlas al vector todasLasRutas
    todasLasRutas.emplace_back(3, 4, "Marron", 2);   // D-E
    todasLasRutas.emplace_back(4, 1, "Verde", 2);    // E-B
    todasLasRutas.emplace_back(1, 0, "Rojo", 2);     // B-A
    todasLasRutas.emplace_back(0, 5, "Azul", 4);     // A-F
    todasLasRutas.emplace_back(5, 4, "Verde", 2);    // F-E
    todasLasRutas.emplace_back(5, 6, "Naranja", 3);  // F-G
    todasLasRutas.emplace_back(6, 2, "Marron", 2);   // G-C
    todasLasRutas.emplace_back(7, 5, "Naranja", 2);  // H-F
    todasLasRutas.emplace_back(7, 8, "Rojo", 2);     // H-I
    todasLasRutas.emplace_back(8, 9, "Azul", 2);     // I-J
    todasLasRutas.emplace_back(9, 13, "Naranja", 3); // J-N
    todasLasRutas.emplace_back(13, 14, "Azul", 2);   // N-O
    todasLasRutas.emplace_back(14, 17, "Morado", 3); // O-R
    todasLasRutas.emplace_back(17, 18, "Marron", 2); // R-S
    todasLasRutas.emplace_back(10, 7, "Verde", 2);   // K-H
    todasLasRutas.emplace_back(10, 8, "Morado", 2);  // K-I
    todasLasRutas.emplace_back(10, 11, "Naranja", 3); // K-L
    todasLasRutas.emplace_back(10, 15, "Verde", 3);  // K-P
    todasLasRutas.emplace_back(11, 12, "Naranja", 2); // L-M
    todasLasRutas.emplace_back(11, 16, "Rojo", 2);   // L-Q
    todasLasRutas.emplace_back(12, 16, "Morado", 2); // M-Q
    todasLasRutas.emplace_back(16, 15, "Verde", 3);  // Q-P
    todasLasRutas.emplace_back(15, 14, "Naranja", 2); // P-O
    todasLasRutas.emplace_back(15, 18, "Azul", 2);   // P-S

    std::cout << "Mapa inicializado con " << getTodasLasCiudades().size() << " ciudades y " << todasLasRutas.size() << " rutas." << std::endl;
}

void Mapa::agregarRuta(const Ruta& ruta) {
    todasLasRutas.push_back(ruta);
}

Ruta* Mapa::obtenerRuta(int idOrigen, int idDestino) {
    for (size_t i = 0; i < todasLasRutas.size(); ++i) {
        if ((todasLasRutas[i].idOrigenCiudad == idOrigen && todasLasRutas[i].idDestinoCiudad == idDestino) ||
            (todasLasRutas[i].idOrigenCiudad == idDestino && todasLasRutas[i].idDestinoCiudad == idOrigen)) {
            return &todasLasRutas[i];
        }
    }
    return nullptr;
}

void Mapa::mostrarMapa(BoardRenderer& renderer) { // Renombrado a renderer
    std::cout << "\n--- Estado Actual del Tablero ---" << std::endl;

    std::vector<Ciudad*> ciudadesDelMapa = getTodasLasCiudades();
    const std::vector<Ruta>& rutasDelMapa = getTodasLasRutas();

    renderer.generateBoard(ciudadesDelMapa, rutasDelMapa); // Renombrado a generateBoard
    renderer.renderBoard(); // Renombrado a renderBoard

    std::cout << "------------------------------------------\n" << std::endl;
}

void Mapa::mostrarBSTInOrder(CiudadNode* nodo) const { // Renombrado a CiudadNode
    if (nodo != nullptr) {
        mostrarBSTInOrder(nodo->izquierda);
        nodo->ciudad.mostrarInformacion();
        mostrarBSTInOrder(nodo->derecha);
    }
}