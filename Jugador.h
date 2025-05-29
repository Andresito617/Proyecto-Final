#ifndef JUGADOR_H
#define JUGADOR_H
#include <string>
#include <vector>
#include "TrainCard.h"

class Jugador {
private:
    int id;
    std::string nombre;
    std::vector<TrainCard> manoCartas;
    int trenesRestantes;
    int puntos;

public:
    Jugador(int id, std::string nombre, int vagonesIniciales = 18);
    int getID() const;
    std::string getNombre() const;
    const std::vector<TrainCard>& getManoCartas() const;
    int getTrenesRestantes() const;
    int getPuntos() const;
    void añadirCarta(const TrainCard& carta);
    void removerCartas(const std::vector<TrainCard>& cartasARemover);
    void gastarTrenes(int cantidad);
    void añadirPuntos(int cantidad);
    void mostrarMano() const;
};

#endif // JUGADOR_H