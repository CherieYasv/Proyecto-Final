#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "LuckyFunciones.c"
int main() {
    int setDominos = 0;
    int cantidadJugadores = 0;
    srand(time(NULL));

    printf("     ==== LUCKY 20 ====");
    printf("\n\n¡Hola!, vamos a jugar Lucky 20.\n¿Con que set de domino desea jugar?\nDoble ");
    scanf("%d", &setDominos);

    do {
        printf("\n¿Cuantos jugadores desean jugar? (1 a 4 jugadores): ");
        scanf("%d", &cantidadJugadores);

        if (cantidadJugadores < 1 || cantidadJugadores > 4) {
            printf("\n=== Error. La cantidad de jugadores debe ser entre 1 y 4 ===\n");
        }
    } while (cantidadJugadores < 1 || cantidadJugadores > 4);


    Banco banco = setDomino(setDominos);
    banco = mezclarSet(banco);
    printf("\nFichas totales: %d\n", banco.cantidadActual);


    Jugador jugadores[4];

    for (int i = 0; i < cantidadJugadores; i++) {
        jugadores[i].cantidadFichas = 0;

        EstadoReparto paquete = repartirSeisCartas(banco, jugadores[i]);

        banco = paquete.banco;
        jugadores[i] = paquete.jugador;
    }

    printf("\n=== REPARTO FINALIZADO ===\n");
    printf("Fichas que sobraron en el banco: %d\n", banco.cantidadActual);


    int juegoTerminado = 0;
    char opcionMenu;

    printf("\n\n====== COMIENZO DEL JUEGO ======\n");

    while (juegoTerminado == 0) {

        for (int i = 0; i < cantidadJugadores; i++) {
            printf("\nTURNO DEL JUGADOR %d", i + 1);
            printf("\nFichas disponibles en el banco: %d", banco.cantidadActual);

            printf("\nTu mano: ");
            for(int j = 0; j < jugadores[i].cantidadFichas; j++) {
                printf("[%d|%d] ", jugadores[i].mano[j].izquierda, jugadores[i].mano[j].derecha);
            }

            printf("\n\n¿Que deseas hacer?\n");
            printf("a) Formar un par (sumar 20)\n");
            printf("b) Pedir 4 fichas del banco\n");
            printf("c) Retirarse de la partida\n");
            printf("Elige una opcion: ");

            scanf(" %c", &opcionMenu);
            if (opcionMenu == 'a' || opcionMenu == 'A') {
                printf("\n--> Elegiste formar un par.\n");

            }
            else if (opcionMenu == 'b' || opcionMenu == 'B') {
                printf("\n--> Elegiste pedir 4 fichas.\n");

            }
            else if (opcionMenu == 'c' || opcionMenu == 'C') {
                printf("\n--> El Jugador %d se ha retirado de la partida.\n", i + 1);
                juegoTerminado = 1;
                break;
            }
            else {
                printf("\n--> Opcion no valida. Pierdes tu turno.\n");
            }
        }
    }

    printf("\n=== GRACIAS POR JUGAR ===\n");
    return 0;
}