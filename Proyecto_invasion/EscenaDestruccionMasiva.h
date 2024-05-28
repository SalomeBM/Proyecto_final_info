#ifndef ESCENADESTRUCCIONMASIVA_H
#define ESCENADESTRUCCIONMASIVA_H

#include "Escena.h"

class EscenaDestruccionMasiva : public Escena {
public:
    void inicializar() override;
    void actualizar() override;
    void renderizar() override;
    void manejarEventos() override;
private:
    int tiempoRestante;
    int disparosPermitidos;
};

#endif // ESCENADESTRUCCIONMASIVA_H
