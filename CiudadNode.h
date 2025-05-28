#ifndef CIUDAD_NODE_H
#define CIUDAD_NODE_H

#include "Ciudad.h" // Incluye la clase Ciudad

class CiudadNode {
public:
    Ciudad ciudad;
    CiudadNode* izquierda;
    CiudadNode* derecha;

    CiudadNode(Ciudad& c);
    ~CiudadNode(); // Destructor para liberar memoria de nodos hijos
};

#endif // CIUDAD_NODE_H