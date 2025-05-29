#include "CiudadNode.h"
#include <iostream>

CiudadNode::CiudadNode(Ciudad& c) : ciudad(c), izquierda(nullptr), derecha(nullptr) {}

CiudadNode::~CiudadNode() {
}