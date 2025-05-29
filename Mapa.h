#ifndef MAPA_H
#define MAPA_H

#include "CiudadNode.h"
#include "Ciudad.h"
#include "Ruta.h"
#include <vector>
#include <map>

class BoardRenderer;

class Mapa {
private:
    CiudadNode* raiz;
    std::vector<Ruta> todasLasRutas;
    CiudadNode* insertarCiudadRecursivo(CiudadNode* nodo, Ciudad& ciudad);
    CiudadNode* buscarCiudadRecursivo(CiudadNode* nodo, int idCiudad) const;
    void destruirBST(CiudadNode* nodo);
    void mostrarBSTInOrder(CiudadNode* nodo) const;
    void recolectarCiudades(CiudadNode* nodo, std::vector<Ciudad*>& ciudades) const;

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