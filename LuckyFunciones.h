#ifndef LUCKYFUNCIONES_H
#define LUCKYFUNCIONES_H

typedef struct {
    int izquierda;
    int derecha;
} Ficha;

typedef struct {
    Ficha lista[91];
    int cantidadActual;
} Banco;

typedef struct {
    Ficha mano[28];
    int cantidadFichas;
} Jugador;

typedef struct {
    Banco banco;
    Jugador jugador;
} EstadoReparto;

Banco setDomino(int maximoDomino);
Banco mezclarSet(Banco banco);
EstadoReparto repartirSeisCartas(Banco bancoActual, Jugador jugadorActual);

int validarPar(Ficha f1, Ficha f2);
Jugador removerFichas(Jugador jugador, int indiceJUno, int indiceJDos);

#endif