#ifndef LUCKY20_LUCKYFUNCIONES_H
#define LUCKY20_LUCKYFUNCIONES_H

typedef struct {
    int izquierda;
    int derecha;
} Ficha;

typedef struct {
    Ficha lista[91]; //<-- Si fuera el maximo (pares de 12), el maximo son 91 fichas.
    int cantidadActual; //<-- Cantidad que se ira modificando mostrando la cantidad de fichas en el banco
} Banco;

typedef struct { //Se crea una estructura para el jugador y para el banco
    Ficha mano[28];
    int cantidadFichas;
} Jugador;

typedef struct { //Se junta el banco/jugador en una sola
    Banco banco;
    Jugador jugador;
} EstadoReparto;

Banco setDomino(int maximoDomino);
Banco mezclarSet(Banco banco);
EstadoReparto repartirSeisCartas(Banco bancoActual, Jugador jugadorActual);

#endif