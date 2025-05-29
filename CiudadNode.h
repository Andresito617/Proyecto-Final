#ifndef CIUDAD_NODE_H
#define CIUDAD_NODE_H
#include "Ciudad.h" 

class CiudadNode {
public:
    Ciudad ciudad;
    CiudadNode* izquierda;
    CiudadNode* derecha;

    CiudadNode(Ciudad& c);
    ~CiudadNode();
};

#endif // CIUDAD_NODE_H