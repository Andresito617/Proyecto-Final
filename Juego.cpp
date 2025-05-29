#include "Juego.h"
#include <iostream>
#include <limits>

Juego::Juego() : indiceJugadorActual(0), jugadasUltimaRonda(0), juegoEnUltimaRonda(false) {}

void Juego::inicializarJuego() {
    std::cout << "Inicializando el juego..." << std::endl;
    mapa.inicializarMapa();
    mazoCartas.inicializarMazo();
    configurarJugadores();
    repartirCartasIniciales();

    std::cout << "Juego inicializado. ¡Que empiece la partida!\n" << std::endl;
}

void Juego::configurarJugadores() {
    jugadores.emplace_back(1, "Jugador 1", 18);
    jugadores.emplace_back(2, "Jugador 2", 18);
    jugadores.emplace_back(3, "Jugador 3", 18);
    jugadores.emplace_back(4, "Jugador 4", 18);
    numJugadores = jugadores.size();
    std::cout << "Se han configurado " << jugadores.size() << " jugadores." << std::endl;
}

void Juego::repartirCartasIniciales() {
    std::cout << "Repartiendo cartas iniciales a los jugadores..." << std::endl;
    const int CARTAS_INICIALES = 4; // Típico en TTR

    for (Jugador& j : jugadores) {
        for (int i = 0; i < CARTAS_INICIALES; ++i) {
            j.añadirCarta(mazoCartas.robarCarta());
        }
        std::cout << j.getNombre() << " recibió " << CARTAS_INICIALES << " cartas." << std::endl;
        j.mostrarMano(); // Para verificar
    }
}

void Juego::iniciarBucleJuego() {
    while (!verificarFinDeJuego()) {
        Jugador& jugadorActual = jugadores[indiceJugadorActual];
        std::cout << "\n--- Turno de " << jugadorActual.getNombre() << " ---" << std::endl;

        mostrarEstadoJuego();

        int opcion;
        bool accionValida = false;
        while (!accionValida) {
            mostrarOpcionesTurno(jugadorActual);
            std::cout << "Selecciona una acción (1 o 2): ";
            std::cin >> opcion;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

            switch (opcion) {
                case 1: // Robar dos cartas
                    accionValida = procesarAccionRobarCartas(jugadorActual);
                    break;
                case 2: // Reclamar un trayecto
                    accionValida = procesarAccionReclamarTrayecto(jugadorActual);
                    break;
                default:
                    std::cout << "Opción no válida. Por favor, elige 1 o 2." << std::endl;
                    break;
            }
        }
        
        if (juegoEnUltimaRonda) {
            jugadasUltimaRonda++;
            std::cout << "Jugadas en la última ronda: " << jugadasUltimaRonda << "/" << numJugadores << std::endl;
        }

        indiceJugadorActual = (indiceJugadorActual + 1) % jugadores.size();

    }
    determinarGanador();
}

void Juego::mostrarEstadoJuego() {
    std::cout << "\n--- Estado Actual del Juego ---" << std::endl;
    mapa.mostrarMapa(boardRenderer); // Muestra el mapa

    std::cout << "\n--- Puntuaciones y Trenes ---" << std::endl;
    for (const auto& j : jugadores) {
        std::cout << j.getNombre() << ": Puntos = " << j.getPuntos()
                  << ", Trenes restantes = " << j.getTrenesRestantes()
                  << ", Cartas en mano = " << j.getManoCartas().size() << std::endl;
    }
    std::cout << "Cartas en mazo de robo: " << mazoCartas.getCantidadCartasMazoRobo() << std::endl;
    std::cout << "Cartas en mazo de descarte: " << mazoCartas.getCantidadCartasMazoDescarte() << std::endl;
    std::cout << "------------------------------\n" << std::endl;
}

void Juego::mostrarOpcionesTurno(const Jugador& jugador) const {
    std::cout << "\n" << jugador.getNombre() << ", ¿qué quieres hacer?" << std::endl;
    std::cout << "1. Robar dos cartas de vagón." << std::endl;
    std::cout << "2. Reclamar un trayecto." << std::endl;
    jugador.mostrarMano();
}

bool Juego::procesarAccionRobarCartas(Jugador& jugador) {
    std::cout << jugador.getNombre() << " va a robar dos cartas..." << std::endl;
    if (mazoCartas.getCantidadCartasMazoRobo() == 0 && mazoCartas.getCantidadCartasMazoDescarte() == 0) {
        std::cout << "No quedan cartas para robar. Fin del juego inminente." << std::endl;
        return false;
    }

    // Robar la primera carta
    TrainCard carta1 = mazoCartas.robarCarta();
    if (carta1.getColor() == "VACIA") return false;
    jugador.añadirCarta(carta1);
    std::cout << "Robaste: " << carta1.getColor() << std::endl;

    // Robar la segunda carta
    TrainCard carta2 = mazoCartas.robarCarta();
    if (carta2.getColor() == "VACIA") return false;
    jugador.añadirCarta(carta2);
    std::cout << "Robaste: " << carta2.getColor() << std::endl;

    std::cout << "Cartas de " << jugador.getNombre() << " después de robar:" << std::endl;
    jugador.mostrarMano();
    return true;
}

bool Juego::procesarAccionReclamarTrayecto(Jugador& jugador) {
    std::cout << jugador.getNombre() << " va a reclamar un trayecto." << std::endl;
    int idOrigen, idDestino;
    Ruta* rutaSeleccionada = seleccionarRutaParaReclamar(idOrigen, idDestino);

    if (!rutaSeleccionada) {
        std::cout << "Ruta no encontrada o ya reclamada. Intenta de nuevo." << std::endl;
        return false;
    }

    if (rutaSeleccionada->propietarioJugadorID != -1) {
        std::cout << "Esa ruta ya ha sido reclamada por " << jugadores[rutaSeleccionada->propietarioJugadorID - 1].getNombre() << ". Elige otra." << std::endl;
        return false;
    }

    if (jugador.getTrenesRestantes() < rutaSeleccionada->longitud) {
        std::cout << jugador.getNombre() << " no tiene suficientes trenes para reclamar esta ruta ("
                  << rutaSeleccionada->longitud << " trenes necesarios)." << std::endl;
        return false;
    }

    std::vector<TrainCard> cartasUsadas;
    if (!tieneCartasSuficientes(jugador, *rutaSeleccionada, cartasUsadas)) {
        std::cout << jugador.getNombre() << " no tiene las cartas necesarias para reclamar esta ruta." << std::endl;
        return false;
    }

    rutaSeleccionada->reclamar(jugador.getID());
    jugador.gastarTrenes(rutaSeleccionada->longitud);
    jugador.removerCartas(cartasUsadas);
    for (const auto& carta : cartasUsadas) {
        mazoCartas.descartarCarta(carta);
    }
    puntuarTrayecto(jugador, *rutaSeleccionada);

    std::cout << jugador.getNombre() << " ha reclamado la ruta "
              << mapa.buscarCiudad(idOrigen)->getNombre() << "-"
              << mapa.buscarCiudad(idDestino)->getNombre()
              << " (" << rutaSeleccionada->longitud << " vagones, " << rutaSeleccionada->color << ")." << std::endl;
    return true;
}

Ruta* Juego::seleccionarRutaParaReclamar(int& idOrigen, int& idDestino) {
    std::cout << "Ingresa el ID de la ciudad de origen: ";
    while (!(std::cin >> idOrigen)) {
        std::cout << "Entrada inválida. Ingresa un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    std::cout << "Ingresa el ID de la ciudad de destino: ";
    while (!(std::cin >> idDestino)) {
        std::cout << "Entrada inválida. Ingresa un número: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return mapa.obtenerRuta(idOrigen, idDestino);
}

bool Juego::tieneCartasSuficientes(const Jugador& jugador, const Ruta& ruta, std::vector<TrainCard>& cartasUsadas) const {

    int cartasRequeridas = ruta.longitud;
    std::string colorRequerido = ruta.color;
    int cartasDisponiblesDelColor = 0;

    for (const auto& carta : jugador.getManoCartas()) {
        if (carta.getColor() == colorRequerido) {
            cartasDisponiblesDelColor++;
        }
    }

    if (cartasDisponiblesDelColor >= cartasRequeridas) {
        int cont = 0;
        for (const auto& carta : jugador.getManoCartas()) {
            if (carta.getColor() == colorRequerido && cont < cartasRequeridas) {
                cartasUsadas.push_back(carta);
                cont++;
            }
        }
        return true;
    }

    return false;
}

void Juego::puntuarTrayecto(Jugador& jugador, const Ruta& ruta) {
    int puntosGanados = 0;
    switch (ruta.longitud) {
        case 2: puntosGanados = 1; break;
        case 3: puntosGanados = 2; break;
        case 4: puntosGanados = 4; break;
        case 5: puntosGanados = 6; break;
        case 6: puntosGanados = 9; break;
        default: puntosGanados = 0; break;
    }
    jugador.añadirPuntos(puntosGanados);
    std::cout << jugador.getNombre() << " gana " << puntosGanados << " puntos por esta ruta." << std::endl;
}

bool Juego::verificarFinDeJuego() const {
    if (juegoEnUltimaRonda && jugadasUltimaRonda >= numJugadores) {
        return true;
    }

    if (!juegoEnUltimaRonda) {
        for (const auto& j : jugadores) {
            if (j.getTrenesRestantes() < 5) {
                std::cout << "\n¡" << j.getNombre() << " tiene menos de 5 trenes! El juego entrará en la última ronda." << std::endl;
                const_cast<Juego*>(this)->juegoEnUltimaRonda = true;
                const_cast<Juego*>(this)->jugadasUltimaRonda = 0;
                return false;
            }
        }
    }
    return false;
}

void Juego::determinarGanador() const {
    std::cout << "\n--- FIN DEL JUEGO ---" << std::endl;
    std::cout << "--- Puntuaciones Finales ---" << std::endl;
    Jugador* ganador = nullptr;
    int maxPuntos = -1;

    for (const auto& j : jugadores) {
        std::cout << j.getNombre() << ": " << j.getPuntos() << " puntos." << std::endl;
        if (j.getPuntos() > maxPuntos) {
            maxPuntos = j.getPuntos();
            ganador = const_cast<Jugador*>(&j);
        } else if (j.getPuntos() == maxPuntos && ganador != nullptr) {
        }
    }

    if (ganador) {
        std::cout << "\n¡El ganador es: " << ganador->getNombre() << " con " << ganador->getPuntos() << " puntos!" << std::endl;
    } else {
        std::cout << "No se pudo determinar un ganador." << std::endl;
    }
}