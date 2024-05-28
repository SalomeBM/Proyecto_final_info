TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Enemigo.cpp \
        EscenaCubrirseYRefugiarse.cpp \
        EscenaDestruccionMasiva.cpp \
        EscenaEsquivarYLlegar.cpp \
        Juego.cpp \
        Objeto.cpp \
        main.cpp

HEADERS += \
    Enemigo.h \
    Escena.h \
    EscenaCubrirseYRefugiarse.h \
    EscenaDestruccionMasiva.h \
    EscenaEsquivarYLlegar.h \
    Juego.h \
    Jugador.h \
    Objeto.h
