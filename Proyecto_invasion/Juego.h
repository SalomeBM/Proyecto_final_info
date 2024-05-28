#ifndef JUEGO_H
#define JUEGO_H

#include "Escena.h"

class Juego {
public:
    Juego();
    void iniciar();
    void cambiarEscena(int escena);
    void finalizar();
    void manejarEntrada(int tecla, bool presionada);
    void actualizarTemporizador();
private:
    class Temporizador {
    public:
        Temporizador(int tiempoInicial);
        void iniciar();
        void detener();
        int obtenerTiempoRestante() const;
    private:
        int tiempoRestante;
        bool enMarcha;
    };

    class ControladorEntrada {
    public:
        static void manejarTeclaPresionada(int tecla);
        static void manejarTeclaSoltada(int tecla);
    };

    Escena* escenaActual;
    Temporizador temporizador;
    ControladorEntrada controladorEntrada;
};

#endif // JUEGO_H
