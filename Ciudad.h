#ifndef CIUDAD_H
#define CIUDAD_H

#include <string>

class Ciudad {
public:
    std::string nombre;
    int id;

    Ciudad(std::string nombreCiudad, int idCiudad);
    std::string getNombre() const;
    int getID() const;
    void mostrarInformacion() const;
};

#endif // CIUDAD_H