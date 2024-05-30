//Juego.cpp
#include "Juego.h"

// Implementación de Temporizador
Juego::Temporizador::Temporizador(int tiempoInicial)
    : tiempoRestante(tiempoInicial), enMarcha(false) {}

void Juego::Temporizador::iniciar() {
    enMarcha = true;
}

void Juego::Temporizador::detener() {
    enMarcha = false;
}

int Juego::Temporizador::obtenerTiempoRestante() const {
    return tiempoRestante;
}

// Implementación de ControladorEntrada
void Juego::ControladorEntrada::manejarTeclaPresionada(int tecla) {
    // Lógica de manejo de tecla presionada
}

void Juego::ControladorEntrada::manejarTeclaSoltada(int tecla) {
    // Lógica de manejo de tecla soltada
}

// Implementación de Juego
Juego::Juego()
    : escenaActual(nullptr), temporizador(60) {} // Suponiendo un tiempo inicial de 60 segundos

void Juego::iniciar() {
    // Lógica para iniciar el juego
    temporizador.iniciar();
}

void Juego::cambiarEscena(int escena) {
    // Lógica para cambiar de escena
}

void Juego::finalizar() {
    // Lógica para finalizar el juego
    temporizador.detener();
}

void Juego::manejarEntrada(int tecla, bool presionada) {
    if (presionada) {
        controladorEntrada.manejarTeclaPresionada(tecla);
    } else {
        controladorEntrada.manejarTeclaSoltada(tecla);
    }
}

void Juego::actualizarTemporizador() {
    int tiempoRestante = temporizador.obtenerTiempoRestante();
    // Lógica de actualización basada en el tiempo restante
}
