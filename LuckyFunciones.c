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

Banco mezclarSet() {

}