#ifndef JUEGO_H
#define JUEGO_H

#include <vector>
#include <string>
#include <limits>
#include <algorithm>
#include "Mapa.h"
#include "TrainDeck.h"
#include "BoardRenderer.h"
#include "Jugador.h"

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
    Juego();
    void inicializarJuego();
    void iniciarBucleJuego();
    bool verificarFinDeJuego() const;
    void determinarGanador() const;
};

#endif // JUEGO_H