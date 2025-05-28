#ifndef RUTA_H
#define RUTA_H

#include <string> // Para std::string

class Ruta {
public:
    // Atributos de la ruta
    int idOrigenCiudad;     // ID de la primera ciudad que conecta la ruta
    int idDestinoCiudad;    // ID de la segunda ciudad que conecta la ruta
    std::string color;      // Color de la ruta (ej. "Rojo", "Gris")
    int longitud;           // Cantidad de vagones necesarios para reclamar la ruta
    int propietarioJugadorID; // ID del jugador que ha reclamado la ruta (-1 si está libre)

    // Constructor de la clase Ruta
    // Inicializa una ruta con sus ciudades, color y longitud.
    // Por defecto, una ruta nueva está libre (propietarioJugadorID = -1).
    Ruta(int idOrigen, int idDestino, std::string colorRuta, int longitudRuta);

    // Método para verificar si la ruta está libre
    bool estaLibre() const;

    // Método para reclamar la ruta por un jugador
    void reclamar(int jugadorID);

    // Método para obtener el ID del jugador propietario
    int getPropietarioID() const;

    // Método para mostrar información de la ruta (útil para depuración)
    void mostrarInformacion() const;
};

#endif // RUTA_H