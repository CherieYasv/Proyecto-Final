#include <stdio.h>
#include "LuckyFunciones.c"

int main() {
    int setDominos = 0;
    srand(time(NULL));

    printf("     ==== LUCKY 20 ====");
    printf("\n\n¡Hola!, vamos a jugar Lucky 20.\n¿Con que set de domino desea jugar?\nDoble ");
    scanf("%d", &setDominos);

    Banco banco = setDomino(setDominos);
    printf("Bancos de fichas de %d\n", banco.cantidadActual);

    printf("Fichas antes de mezclar: ");
    printf("\n");
    for (int i = 0; i < banco.cantidadActual; i++) {
        printf("%d|%d ", banco.lista[i].izquierda, banco.lista[i].derecha);
    }

    banco = mezclarSet(banco);
    printf("\nFichas mezcladas:\n");
    for (int i = 0; i < banco.cantidadActual; i++) {
        printf("%d|%d ", banco.lista[i].izquierda, banco.lista[i].derecha);
    }

    Jugador jugador1;
    jugador1.cantidadFichas = 0;

    EstadoReparto paquete = repartirSeisCartas(banco, jugador1);

    jugador1 = paquete.jugador;

    // La mano del jugador -->
    printf("\n\nFichas en la mano del Jugador 1:\n");
    for(int i = 0; i < jugador1.cantidadFichas; i++) {
        printf("%d|%d ", jugador1.mano[i].izquierda, jugador1.mano[i].derecha);
    }

    printf("\nFichas que sobraron en el banco: %d\n", banco.cantidadActual);

    return 0;
}