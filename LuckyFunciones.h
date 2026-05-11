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

Banco setDomino(int maximoDomino);

#endif