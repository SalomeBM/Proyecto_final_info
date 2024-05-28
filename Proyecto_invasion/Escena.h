#ifndef ESCENA_H
#define ESCENA_H

#include "Jugador.h"
#include "Enemigo.h"
#include "Objeto.h"
#include <vector>

class Escena {
public:
    virtual void inicializar() = 0;
    virtual void actualizar() = 0;
    virtual void renderizar() = 0;
    virtual void manejarEventos() = 0;
protected:
    Jugador* jugador;
    std::vector<Enemigo*> enemigos;
    std::vector<Objeto*> objetos;
};

#endif // ESCENA_H
