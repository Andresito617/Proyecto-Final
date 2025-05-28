#include "Ciudad.h" // Incluir el archivo de cabecera de la clase Ciudad
#include <iostream>  // Necesario para std::cout

// Constructor de la clase Ciudad
Ciudad::Ciudad(std::string nombreCiudad, int idCiudad) :
    nombre(nombreCiudad), // Inicializa el atributo 'nombre' con 'nombreCiudad'
    id(idCiudad)          // Inicializa el atributo 'id' con 'idCiudad'
{
    // El cuerpo del constructor puede estar vacío si solo se usan los inicializadores
}

// Implementación del método getNombre
std::string Ciudad::getNombre() const {
    return nombre;
}

// Implementación del método getID
int Ciudad::getID() const {
    return id;
}

// Implementación del método mostrarInformacion
void Ciudad::mostrarInformacion() const {
    std::cout << "Ciudad: " << nombre << " (ID: " << id << ")" << std::endl;
}