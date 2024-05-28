#ifndef JUGADOR_H
#define JUGADOR_H

class Jugador {
public:
    Jugador(int x, int y, int vidas);
    void moverArriba();
    void moverAbajo();
    void moverAdelante();
    void saltar();
    void agacharse();
    void recibirDano();
    bool estaVivo() const;
private:
    int posX, posY;
    int vidas;
    int puntuacion;
};

#endif // JUGADOR_H
