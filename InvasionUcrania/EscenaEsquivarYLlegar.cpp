//EscenaEsquivarYLlegar.cpp
#include "EscenaEsquivarYLlegar.h"
#include <iostream> // Para imprimir mensajes de depuración, si es necesario

void EscenaEsquivarYLlegar::inicializar() {
    // Inicializar variables
    velocidadConstante = 5; // La velocidad constante del jugador
    vidasRestantes = 3; // Vidas iniciales del jugador

    // Inicializar el jugador
    jugador = new Jugador(0, 0, vidasRestantes);

    // Inicializar los obstáculos
    obstaculos.push_back(Objeto(10, 0)); // Añadir un obstáculo de ejemplo
    // Añadir más obstáculos según sea necesario
}

void EscenaEsquivarYLlegar::actualizar() {
    // Actualizar la posición del jugador basándose en la velocidad constante
    jugador->moverAdelante();

    // Verificar colisiones
    for (auto& obstaculo : obstaculos) {
        if (obstaculo.esColision(jugador)) {
            jugador->recibirDano();
            if (!jugador->estaVivo()) {
                vidasRestantes--;
                if (vidasRestantes == 0) {
                    std::cout << "Juego terminado" << std::endl;
                    // Manejar el fin del juego
                }
            }
        }
    }
}

void EscenaEsquivarYLlegar::renderizar() {
    // Renderizar el jugador y los obstáculos
    std::cout << "Renderizando jugador en posición (" << jugador->posX << ", " << jugador->posY << ")" << std::endl;
    for (const auto& obstaculo : obstaculos) {
        if (!obstaculo.destruido) {
            std::cout << "Renderizando obstáculo en posición (" << obstaculo.posX << ", " << obstaculo.posY << ")" << std::endl;
        }
    }
}

void EscenaEsquivarYLlegar::manejarEventos() {
    // Manejar eventos de entrada (teclas presionadas)
    // Esto dependerá de cómo se maneje la entrada en tu juego
    // Aquí solo hay un ejemplo simple
    int teclaPresionada = 0; // Obtener la tecla presionada
    switch (teclaPresionada) {
    case 'W': // Mover arriba
        jugador->moverArriba();
        break;
    case 'S': // Mover abajo
        jugador->moverAbajo();
        break;
    case ' ': // Saltar
        jugador->saltar();
        break;
    case 'C': // Agacharse
        jugador->agacharse();
        break;
    default:
        break;
    }
}
