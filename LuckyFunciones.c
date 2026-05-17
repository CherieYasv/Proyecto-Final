#include "LuckyFunciones.h"
#include <stdlib.h>

Banco setDomino(int maximoDomino) {
    Banco banco;
    banco.cantidadActual = 0;

    for (int i = 0; i <= maximoDomino; i++) {
        for (int j = i; j <= maximoDomino; j++) {
            banco.lista[banco.cantidadActual].izquierda = i;
            banco.lista[banco.cantidadActual].derecha = j;
            banco.cantidadActual++;
        }
    }
    return banco;
}

Banco mezclarSet(Banco banco) {
    Ficha fichaTemporal;
    int numeroAleatorio = 0;

    for (int i = banco.cantidadActual - 1; i > 0; i--) {
        numeroAleatorio = rand() % (i + 1);

        fichaTemporal = banco.lista[i];
        banco.lista[i] = banco.lista[numeroAleatorio];
        banco.lista[numeroAleatorio] = fichaTemporal;
    }

    return banco;
}

EstadoReparto repartirSeisCartas(Banco bancoActual, Jugador jugadorActual) {
    EstadoReparto resultado;
    resultado.banco = bancoActual;
    resultado.jugador = jugadorActual;

    int indiceCima = 0;
    int indiceMano = 0;

    for (int i = 0; i < 6; i++) {
        indiceCima = resultado.banco.cantidadActual - 1;
        Ficha fichaTomada = resultado.banco.lista[indiceCima];

        indiceMano = resultado.jugador.cantidadFichas;
        resultado.jugador.mano[indiceMano] = fichaTomada;

        resultado.banco.cantidadActual--;
        resultado.jugador.cantidadFichas++;
    }

    return resultado;
}