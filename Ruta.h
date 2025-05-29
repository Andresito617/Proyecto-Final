#ifndef RUTA_H
#define RUTA_H
#include <string>

class Ruta {
public:
    int idOrigenCiudad;
    int idDestinoCiudad;
    std::string color;
    int longitud;
    int propietarioJugadorID;
    Ruta(int idOrigen, int idDestino, std::string colorRuta, int longitudRuta);
    bool estaLibre() const;
    void reclamar(int jugadorID);
    int getPropietarioID() const;
    void mostrarInformacion() const;
};

#endif // RUTA_H