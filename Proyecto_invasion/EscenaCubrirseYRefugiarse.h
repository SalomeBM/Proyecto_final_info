#ifndef ESCENACUBRIRSEYREFUGIARSE_H
#define ESCENACUBRIRSEYREFUGIARSE_H

#include "Escena.h"

class EscenaCubrirseYRefugiarse : public Escena {
public:
    void inicializar() override;
    void actualizar() override;
    void renderizar() override;
    void manejarEventos() override;
private:
    int nivelImprecisionDisparos;
    int poderEspecial;
    int vidasRestantes;
};

#endif // ESCENACUBRIRSEYREFUGIARSE_H
