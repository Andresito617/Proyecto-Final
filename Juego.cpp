#include "Juego.h"
#include <iostream>
#include <limits> // Para std::numeric_limits y std::streamsize

// Constructor
Juego::Juego() : indiceJugadorActual(0), jugadasUltimaRonda(0), juegoEnUltimaRonda(false) {}

// Métodos de inicialización
void Juego::inicializarJuego() {
    std::cout << "Inicializando el juego..." << std::endl;
    mapa.inicializarMapa();
    mazoCartas.inicializarMazo();
    configurarJugadores();
    repartirCartasIniciales();

    std::cout << "Juego inicializado. ¡Que empiece la partida!\n" << std::endl;
}

void Juego::configurarJugadores() {
    // La rúbrica especifica 4 jugadores con 18 vagones.
    // Podríamos pedir nombres, pero por simplicidad, los creamos por defecto.
    jugadores.emplace_back(1, "Jugador 1", 18);
    jugadores.emplace_back(2, "Jugador 2", 18);
    jugadores.emplace_back(3, "Jugador 3", 18);
    jugadores.emplace_back(4, "Jugador 4", 18);
    numJugadores = jugadores.size();
    std::cout << "Se han configurado " << jugadores.size() << " jugadores." << std::endl;
}

void Juego::repartirCartasIniciales() {
    // En TTR, se reparten 4 cartas de tren a cada jugador al inicio.
    // La rúbrica no lo especifica, pero es estándar y necesario para "realizar trayectos".
    // Si el profe tiene otra regla, ajustamos.

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

// Métodos de juego
void Juego::iniciarBucleJuego() {
    // La condición principal del bucle es que el juego no haya terminado por completo
    while (!verificarFinDeJuego()) {
        Jugador& jugadorActual = jugadores[indiceJugadorActual];
        std::cout << "\n--- Turno de " << jugadorActual.getNombre() << " ---" << std::endl;

        mostrarEstadoJuego(); // Muestra el mapa y el estado de los jugadores

        int opcion;
        bool accionValida = false;
        while (!accionValida) {
            mostrarOpcionesTurno(jugadorActual);
            std::cout << "Selecciona una acción (1 o 2): ";
            std::cin >> opcion;

            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Limpiar buffer

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

        // Si estamos en la última ronda, incrementamos el contador de jugadas de la ronda
        if (juegoEnUltimaRonda) {
            jugadasUltimaRonda++;
            std::cout << "Jugadas en la última ronda: " << jugadasUltimaRonda << "/" << numJugadores << std::endl;
        }

        // Pasar al siguiente jugador
        indiceJugadorActual = (indiceJugadorActual + 1) % jugadores.size();

        // Si después de pasar el turno y verificar la condición de fin de juego, el juego
        // DEBE TERMINAR. Esto maneja la rúbrica "se terminará de jugar esa ronda".
        // La condición `verificarFinDeJuego()` ahora devolverá `true` si ya se completaron
        // todos los turnos de la última ronda.
    }
    // El bucle ha terminado, el juego ha finalizado completamente.
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
    jugador.mostrarMano(); // Muestra la mano del jugador actual
}

bool Juego::procesarAccionRobarCartas(Jugador& jugador) {
    std::cout << jugador.getNombre() << " va a robar dos cartas..." << std::endl;
    if (mazoCartas.getCantidadCartasMazoRobo() == 0 && mazoCartas.getCantidadCartasMazoDescarte() == 0) {
        std::cout << "No quedan cartas para robar. Fin del juego inminente." << std::endl;
        return false; // O manejar como fin de juego si no hay más opciones
    }

    // Robar la primera carta
    TrainCard carta1 = mazoCartas.robarCarta();
    if (carta1.getColor() == "VACIA") return false; // No hay cartas
    jugador.añadirCarta(carta1);
    std::cout << "Robaste: " << carta1.getColor() << std::endl;

    // Robar la segunda carta
    TrainCard carta2 = mazoCartas.robarCarta();
    if (carta2.getColor() == "VACIA") return false; // No hay cartas
    jugador.añadirCarta(carta2);
    std::cout << "Robaste: " << carta2.getColor() << std::endl;

    std::cout << "Cartas de " << jugador.getNombre() << " después de robar:" << std::endl;
    jugador.mostrarMano();
    return true; // Acción válida
}

bool Juego::procesarAccionReclamarTrayecto(Jugador& jugador) {
    std::cout << jugador.getNombre() << " va a reclamar un trayecto." << std::endl;
    int idOrigen, idDestino;
    Ruta* rutaSeleccionada = seleccionarRutaParaReclamar(idOrigen, idDestino);

    if (!rutaSeleccionada) {
        std::cout << "Ruta no encontrada o ya reclamada. Intenta de nuevo." << std::endl;
        return false; // Acción no válida
    }

    if (rutaSeleccionada->propietarioJugadorID != -1) {
        std::cout << "Esa ruta ya ha sido reclamada por " << jugadores[rutaSeleccionada->propietarioJugadorID - 1].getNombre() << ". Elige otra." << std::endl;
        return false; // Acción no válida
    }

    if (jugador.getTrenesRestantes() < rutaSeleccionada->longitud) {
        std::cout << jugador.getNombre() << " no tiene suficientes trenes para reclamar esta ruta ("
                  << rutaSeleccionada->longitud << " trenes necesarios)." << std::endl;
        return false; // Acción no válida
    }

    // Ahora, verificar las cartas en mano del jugador
    std::vector<TrainCard> cartasUsadas;
    if (!tieneCartasSuficientes(jugador, *rutaSeleccionada, cartasUsadas)) {
        std::cout << jugador.getNombre() << " no tiene las cartas necesarias para reclamar esta ruta." << std::endl;
        return false; // Acción no válida
    }

    // Si todo está bien, reclamar la ruta
    rutaSeleccionada->reclamar(jugador.getID());
    jugador.gastarTrenes(rutaSeleccionada->longitud);
    jugador.removerCartas(cartasUsadas); // Quitar las cartas de la mano del jugador
    for (const auto& carta : cartasUsadas) {
        mazoCartas.descartarCarta(carta); // Poner las cartas en el descarte
    }
    puntuarTrayecto(jugador, *rutaSeleccionada); // Sumar puntos

    std::cout << jugador.getNombre() << " ha reclamado la ruta "
              << mapa.buscarCiudad(idOrigen)->getNombre() << "-"
              << mapa.buscarCiudad(idDestino)->getNombre()
              << " (" << rutaSeleccionada->longitud << " vagones, " << rutaSeleccionada->color << ")." << std::endl;
    return true; // Acción válida
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
    // La rúbrica dice: "Tener el color de las cartas necesarias para cada trayecto."
    // Asumimos que se necesitan cartas del color de la ruta, o locomotoras (aunque no estén en el mazo,
    // es una consideración de juego de TTR. Por simplicidad, aquí solo consideramos el color exacto).

    int cartasRequeridas = ruta.longitud;
    std::string colorRequerido = ruta.color;
    int cartasDisponiblesDelColor = 0;

    // Contar cartas del color requerido en la mano del jugador
    for (const auto& carta : jugador.getManoCartas()) {
        if (carta.getColor() == colorRequerido) {
            cartasDisponiblesDelColor++;
        }
    }

    if (cartasDisponiblesDelColor >= cartasRequeridas) {
        // Recolectar las cartas que se usarán
        int cont = 0;
        for (const auto& carta : jugador.getManoCartas()) {
            if (carta.getColor() == colorRequerido && cont < cartasRequeridas) {
                cartasUsadas.push_back(carta);
                cont++;
            }
        }
        return true;
    }

    return false; // No tiene suficientes cartas del color requerido
}

void Juego::puntuarTrayecto(Jugador& jugador, const Ruta& ruta) {
    int puntosGanados = 0;
    switch (ruta.longitud) {
        case 2: puntosGanados = 1; break;
        case 3: puntosGanados = 2; break;
        case 4: puntosGanados = 4; break;
        case 5: puntosGanados = 6; break;
        case 6: puntosGanados = 9; break;
        default: puntosGanados = 0; break; // Longitudes no estándar o error
    }
    jugador.añadirPuntos(puntosGanados);
    std::cout << jugador.getNombre() << " gana " << puntosGanados << " puntos por esta ruta." << std::endl;
}

bool Juego::verificarFinDeJuego() const {
    // Si ya estamos en la última ronda y se han completado las jugadas, entonces el juego termina.
    if (juegoEnUltimaRonda && jugadasUltimaRonda >= numJugadores) { // Usamos numJugadores aquí
        return true;
    }

    if (!juegoEnUltimaRonda) {
        for (const auto& j : jugadores) {
            if (j.getTrenesRestantes() < 5) {
                std::cout << "\n¡" << j.getNombre() << " tiene menos de 5 trenes! El juego entrará en la última ronda." << std::endl;
                const_cast<Juego*>(this)->juegoEnUltimaRonda = true; // Activa la bandera (necesita const_cast)
                const_cast<Juego*>(this)->jugadasUltimaRonda = 0; // Reinicia el contador para la última ronda
                return false; // El juego NO termina aún, solo entra en la última ronda
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
            ganador = const_cast<Jugador*>(&j); // Necesario porque 'j' es const
        } else if (j.getPuntos() == maxPuntos && ganador != nullptr) {
            // Empate: la rúbrica no especifica desempate, el primero en alcanzarlo gana por defecto aquí.
            // Para TTR real, el más largo o más tickets podrían desempatar.
        }
    }

    if (ganador) {
        std::cout << "\n¡El ganador es: " << ganador->getNombre() << " con " << ganador->getPuntos() << " puntos!" << std::endl;
    } else {
        std::cout << "No se pudo determinar un ganador." << std::endl;
    }
}