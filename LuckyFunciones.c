#include "LuckyFunciones.h"
#include <stdlib.h>
#include <time.h>

/*
 * Función para generar el set de domino.
 * De parametro se usa el valor que ingrese el usuario que quiera
 * que sea el set de domino y por ende, su juego. (6, 9 o 12 pares)
 */
Banco setDomino(int maximoDomino) {
    Banco banco;
    banco.cantidadActual = 0; //<-- Inicializamos la estructura.

    for (int i = 0;i <= maximoDomino; i++) {
        for (int j = i; j <= maximoDomino; j++) {
            banco.lista[banco.cantidadActual].izquierda = i;
            banco.lista[banco.cantidadActual].derecha = j;
            banco.cantidadActual++;
        }
    }
    return banco;
}

Banco mezclarSet(Banco banco) {
    //Plantear algoritmo Fisher-Yates
    /*
     *Limite: maximoDomino - 1
     *Hacer un for en reversa.
     *
     *En cada iteracion del ciclo se generara un numero al azar
     *entre el 0 y la iteracion actual.
     *
     *Intercambiar la posicion de la ficha del ciclo por la posicion
     *del numero generado al azar
     */
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
    EstadoReparto resultado; //Copia local
    resultado.banco = bancoActual;
    resultado.jugador = jugadorActual;

    //Repartimos las 6 fichas, como ya estan mezcladas, se toman linealmente
    for (int i = 0; i < 6; i++) {
        int indiceCima = resultado.banco.cantidadActual - 1;
        Ficha fichaTomada = resultado.banco.lista[indiceCima];

        int indiceMano = resultado.jugador.cantidadFichas;
        resultado.jugador.mano[indiceMano] = fichaTomada;

        resultado.banco.cantidadActual--;
        resultado.jugador.cantidadFichas++;
    }

    return resultado;
}