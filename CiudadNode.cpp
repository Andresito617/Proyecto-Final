#include "CiudadNode.h"
#include <iostream>

CiudadNode::CiudadNode(Ciudad& c) : ciudad(c), izquierda(nullptr), derecha(nullptr) {}

CiudadNode::~CiudadNode() {
    // La eliminación de nodos hijos se maneja en el destructor del Mapa
    // o en la función de eliminación de un BST. Aquí no es recursivo.
}