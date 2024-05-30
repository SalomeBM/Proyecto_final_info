//EscenaEsquivarYLlegar.h
#ifndef ESCENAESQUIVARYLLEGAR_H
#define ESCENAESQUIVARYLLEGAR_H

#include "Escena.h"
#include "Jugador.h"
#include "Objeto.h"
#include <vector>

class EscenaEsquivarYLlegar : public Escena {
public:
    void inicializar() override;
    void actualizar() override;
    void renderizar() override;
    void manejarEventos() override;
private:
    int velocidadConstante;
    int vidasRestantes;
    Jugador* jugador;
    std::vector<Objeto> obstaculos;
};

#endif // ESCENAESQUIVARYLLEGAR_H
