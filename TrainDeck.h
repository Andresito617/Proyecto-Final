#ifndef TRAIN_DECK_H
#define TRAIN_DECK_H

#include <vector>
#include <string>
#include <random> 
#include <algorithm>
#include "TrainCard.h"

class TrainDeck {
private:
    std::vector<TrainCard> mazoRobo;    
    std::vector<TrainCard> mazoDescarte; 
    std::mt19937 rng; 

    void reponerMazoRoboDesdeDescarte(); 

public:
    TrainDeck(); 
    void inicializarMazo();
    TrainCard robarCarta(); 
    void descartarCarta(TrainCard carta); 

    int getCantidadCartasMazoRobo() const;
    int getCantidadCartasMazoDescarte() const;
    void mostrarMazoDescarte() const; 
};

#endif // TRAIN_DECK_H