#ifndef OBJETO_H
#define OBJETO_H

#include "Jugador.h"

class Objeto {
public:
    Objeto(int x, int y);
    bool esColision(Jugador* jugador) const;
    void destruir();
private:
    int posX, posY;
    bool destruido;
};

#endif // OBJETO_H
