#ifndef MAPA_H
#define MAPA_H

#include "CiudadNode.h" // Nuevo nombre
#include "Ciudad.h"
#include "Ruta.h"
#include <vector>
#include <map>

class BoardRenderer; // Nuevo nombre: Forward declaration de la clase de display

class Mapa {
private:
    CiudadNode* raiz; // Nuevo nombre
    std::vector<Ruta> todasLasRutas;

    // Métodos BST auxiliares
    CiudadNode* insertarCiudadRecursivo(CiudadNode* nodo, Ciudad& ciudad); // Nuevo nombre
    CiudadNode* buscarCiudadRecursivo(CiudadNode* nodo, int idCiudad) const; // Nuevo nombre
    void destruirBST(CiudadNode* nodo); // Nuevo nombre
    void mostrarBSTInOrder(CiudadNode* nodo) const; // Nuevo nombre
    void recolectarCiudades(CiudadNode* nodo, std::vector<Ciudad*>& ciudades) const; // Nuevo nombre

public:
    Mapa();
    ~Mapa();

    void insertarCiudad(Ciudad ciudad);
    Ciudad* buscarCiudad(int idCiudad);
    void inicializarMapa();

    void agregarRuta(const Ruta& ruta);
    Ruta* obtenerRuta(int idOrigen, int idDestino);

    void mostrarMapa(BoardRenderer& displayer);
    std::vector<Ciudad*> getTodasLasCiudades() const;
    const std::vector<Ruta>& getTodasLasRutas() const;
};

#endif // MAPA_H