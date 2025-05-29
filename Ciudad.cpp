#include "Ciudad.h"
#include <iostream>

// Constructor de la clase Ciudad
Ciudad::Ciudad(std::string nombreCiudad, int idCiudad) :
    nombre(nombreCiudad),
    id(idCiudad)
{

}


std::string Ciudad::getNombre() const {
    return nombre;
}

int Ciudad::getID() const {
    return id;
}

void Ciudad::mostrarInformacion() const {
    std::cout << "Ciudad: " << nombre << " (ID: " << id << ")" << std::endl;
}