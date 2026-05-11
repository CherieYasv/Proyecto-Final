#include <stdio.h>
#include "LuckyFunciones.c"

int main() {
    int setDominos = 0;

    printf("     ==== LUCKY 20 ====");
    printf("\n\n¡Hola!, vamos a jugar Lucky 20.\n¿Con que set de domino desea jugar?\nDoble ");
    scanf("%d", &setDominos);

    Banco banco = setDomino(setDominos);
    printf("Bancos de fichas de %d", banco.cantidadActual);

    printf("Fichas antes de mezclar: ");
    printf("\n");
    for (int i = 0; i < banco.cantidadActual; i++) {
        printf("%d|%d ", banco.lista[i].izquierda, banco.lista[i].derecha);
    }

    printf("Fichas mezcladas: ");
    for (int i = 0; i < banco.cantidadActual; i++) {
        printf("%d|%d ", banco.lista[i].izquierda, banco.lista[i].derecha);
    }
}