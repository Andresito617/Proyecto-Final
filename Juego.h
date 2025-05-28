#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <string>
#include <limits> // Para std::numeric_limits
#include <algorithm> // Para std::find_if
#include "Mapa.h"
#include "TrainDeck.h"
#include "BoardRenderer.h"
#include "Jugador.h" // ¡Incluimos la clase Jugador!

class Juego {
private:
    Mapa mapa;
    TrainDeck mazoCartas;
    BoardRenderer boardRenderer;
    std::vector<Jugador> jugadores;
    int indiceJugadorActual;
    int jugadasUltimaRonda;
    int numJugadores;
    bool juegoEnUltimaRonda;

    // Métodos privados auxiliares
    void configurarJugadores();
    void repartirCartasIniciales();
    void mostrarEstadoJuego();
    void mostrarOpcionesTurno(const Jugador& jugador) const;
    bool procesarAccionRobarCartas(Jugador& jugador);
    bool procesarAccionReclamarTrayecto(Jugador& jugador);
    Ruta* seleccionarRutaParaReclamar(int& idOrigen, int& idDestino);
    bool tieneCartasSuficientes(const Jugador& jugador, const Ruta& ruta, std::vector<TrainCard>& cartasUsadas) const;
    void puntuarTrayecto(Jugador& jugador, const Ruta& ruta);


public:
    Juego(); // Constructor
    void inicializarJuego();
    void iniciarBucleJuego(); // El bucle principal del juego
    bool verificarFinDeJuego() const;
    void determinarGanador() const;
};

#endif // JUEGO_H