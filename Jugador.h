#ifndef JUGADOR_H
#define JUGADOR_H

#include <string>
#include <vector>
#include "TrainCard.h" // Necesitamos incluir TrainCard para la mano del jugador

class Jugador {
private:
    int id; // ID único del jugador (ej. 1, 2, 3, 4)
    std::string nombre; // Nombre del jugador (ej. "Jugador 1")
    std::vector<TrainCard> manoCartas; // Cartas de vagón en la mano del jugador
    int trenesRestantes; // Cantidad de vagones disponibles para construir rutas
    int puntos; // Puntuación actual del jugador

public:
    // Constructor
    Jugador(int id, std::string nombre, int vagonesIniciales = 18);

    // Getters
    int getID() const;
    std::string getNombre() const;
    const std::vector<TrainCard>& getManoCartas() const;
    int getTrenesRestantes() const;
    int getPuntos() const;

    // Métodos para modificar el estado del jugador
    void añadirCarta(const TrainCard& carta);
    // Eliminar cartas de la mano (cuando se reclama una ruta)
    // Esto es más complejo, lo haremos en la lógica del juego.
    // Por ahora, solo un placeholder o un método más simple para test.
    void removerCartas(const std::vector<TrainCard>& cartasARemover);

    void gastarTrenes(int cantidad);
    void añadirPuntos(int cantidad);
    void mostrarMano() const; // Para depuración y visualización
};

#endif // JUGADOR_H