//Enemigo.h
#ifndef ENEMIGO_H
#define ENEMIGO_H

#include "Jugador.h"

class Enemigo {
public:
    Enemigo(int x, int y);
    void mover();
    void atacar(Jugador* jugador);
private:
    int posX, posY;
    bool imprecisionDisparo;
};

#endif // ENEMIGO_H
