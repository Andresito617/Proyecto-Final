#include "Ruta.h" 
#include <iostream> 

Ruta::Ruta(int idOrigen, int idDestino, std::string colorRuta, int longitudRuta) :
    idOrigenCiudad(idOrigen),      
    idDestinoCiudad(idDestino),    
    color(colorRuta),              
    longitud(longitudRuta),
    propietarioJugadorID(-1)
{
    
}
bool Ruta::estaLibre() const {
    return propietarioJugadorID == -1;
}


void Ruta::reclamar(int jugadorID) {
    if (estaLibre()) {
        propietarioJugadorID = jugadorID;
        
    } else {
        std::cout << "Error: La ruta ya ha sido reclamada por el jugador " << propietarioJugadorID << std::endl;
    }
}

int Ruta::getPropietarioID() const {
    return propietarioJugadorID;
}

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