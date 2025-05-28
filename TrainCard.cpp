#include "TrainCard.h"
#include <iostream>

TrainCard::TrainCard(std::string c) : color(c) {}

void TrainCard::mostrarInformacion() const {
    std::cout << "Carta Vagón: " << color << std::endl;
}

std::string TrainCard::getColor() const {
    return color;
}

bool TrainCard::esLocomotora() const {
    return color == "Locomotora";
}