#include "Ruta.h"   // Incluimos el archivo de cabecera de la clase Ruta
#include <iostream> // Necesario para std::cout

// Constructor de la clase Ruta
Ruta::Ruta(int idOrigen, int idDestino, std::string colorRuta, int longitudRuta) :
    idOrigenCiudad(idOrigen),      // Inicializa el ID de la ciudad de origen
    idDestinoCiudad(idDestino),    // Inicializa el ID de la ciudad de destino
    color(colorRuta),              // Inicializa el color de la ruta
    longitud(longitudRuta),        // Inicializa la longitud de la ruta
    propietarioJugadorID(-1)       // Por defecto, la ruta está libre
{
    // El cuerpo del constructor puede estar vacío
}

// Implementación del método estaLibre
bool Ruta::estaLibre() const {
    return propietarioJugadorID == -1;
}

// Implementación del método reclamar
void Ruta::reclamar(int jugadorID) {
    if (estaLibre()) {
        propietarioJugadorID = jugadorID;
        // Podríamos añadir alguna validación o lanzar una excepción si ya estuviera reclamada
    } else {
        std::cout << "Error: La ruta ya ha sido reclamada por el jugador " << propietarioJugadorID << std::endl;
    }
}

// Implementación del método getPropietarioID
int Ruta::getPropietarioID() const {
    return propietarioJugadorID;
}

// Implementación del método mostrarInformacion
void Ruta::mostrarInformacion() const {
    std::cout << "Ruta: " << idOrigenCiudad << " <-> " << idDestinoCiudad
              << " | Color: " << color
              << " | Longitud: " << longitud;
    if (estaLibre()) {
        std::cout << " | Estado: Libre" << std::endl;
    } else {
        std::cout << " | Propietario: Jugador " << propietarioJugadorID << std::endl;
    }
}