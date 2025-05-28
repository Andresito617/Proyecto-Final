#ifndef CIUDAD_H
#define CIUDAD_H

#include <string> // Necesario para std::string

class Ciudad {
public:
    // Atributos de la ciudad
    std::string nombre; // Nombre de la ciudad (ej. "Ciudad A", "New York")
    int id;             // Identificador único de la ciudad (ej. 0, 1, 2...)

    // Constructor de la clase Ciudad
    // Inicializa una nueva ciudad con un nombre y un ID
    Ciudad(std::string nombreCiudad, int idCiudad);

    // Métodos para acceder a los atributos (opcional, pero buena práctica)
    std::string getNombre() const; // Devuelve el nombre de la ciudad
    int getID() const;             // Devuelve el ID de la ciudad

    // Método para mostrar información de la ciudad (útil para depuración)
    void mostrarInformacion() const;
};

#endif // CIUDAD_H