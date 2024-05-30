//Jugador.cpp
#include "Jugador.h"

Jugador::Jugador(int x, int y, int vidas)
    : posX(x), posY(y), vidas(vidas), puntuacion(0) {}

void Jugador::moverArriba() {
    posY -= 1; // Ajustar según sea necesario
}

void Jugador::moverAbajo() {
    posY += 1; // Ajustar según sea necesario
}

void Jugador::moverAdelante() {
    posX += 1; // Ajustar según sea necesario
}

void Jugador::saltar() {
    // Lógica para saltar
}

void Jugador::agacharse() {
    // Lógica para agacharse
}

void Jugador::recibirDano() {
    vidas--;
}

bool Jugador::estaVivo() const {
    return vidas > 0;
}

