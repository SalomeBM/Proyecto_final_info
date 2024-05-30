//Objeto.cpp
#include "Objeto.h"

Objeto::Objeto(int x, int y) : posX(x), posY(y), destruido(false) {}

bool Objeto::esColision(Jugador* jugador) const {
    //Lógica de colisión
    return (jugador->posX == posX && jugador->posY == posY);
}
void Objeto::destruir() {
    destruido = true;
}
