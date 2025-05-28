#ifndef TRAIN_CARD_H
#define TRAIN_CARD_H

#include <string>

class TrainCard {
public:
    std::string color;

    TrainCard(std::string c = "Locomotora"); // Constructor con color por defecto "Locomotora"
    void mostrarInformacion() const;
    std::string getColor() const;
    bool esLocomotora() const;
};

#endif // TRAIN_CARD_H