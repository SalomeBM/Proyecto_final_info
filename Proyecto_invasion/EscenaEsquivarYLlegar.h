#ifndef ESCENAESQUIVARYLLEGAR_H
#define ESCENAESQUIVARYLLEGAR_H

#include "Escena.h"

class EscenaEsquivarYLlegar : public Escena {
public:
    void inicializar() override;
    void actualizar() override;
    void renderizar() override;
    void manejarEventos() override;
private:
    int velocidadConstante;
    int vidasRestantes;
};

#endif // ESCENAESQUIVARYLLEGAR_H
