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

    printf("\n\n====== ¡COMIENZA EL JUEGO! ======\n");

    while (juegoTerminado == 0) {

        for (int i = 0; i < cantidadJugadores; i++) {
            if (juegoTerminado == 1) break;

            printf("\nTURNO DEL JUGADOR %d", i + 1);
            printf("\nFichas disponibles en el banco: %d", banco.cantidadActual);

            printf("\nTu mano: ");
            for(int j = 0; j < jugadores[i].cantidadFichas; j++) {
                printf("%d-> [%d|%d] ", j + 1, jugadores[i].mano[j].izquierda, jugadores[i].mano[j].derecha);
            }

            printf("\n\n¿Que deseas hacer?\n");
            printf("a) Formar un par (sumar 20)\n");
            printf("b) Pedir 4 fichas del banco\n");
            printf("c) Retirarse de la partida\n");
            printf("Elige una opcion: ");

            scanf(" %c", &opcionMenu);

            if (opcionMenu == 'a' || opcionMenu == 'A') {
                int eleccion1, eleccion2;
                printf("\n--> Elegiste formar un par.\n");

                printf("Elige el numero de tu primera ficha (1 a %d): ", jugadores[i].cantidadFichas);
                scanf("%d", &eleccion1);
                printf("Elige el numero de tu segunda ficha (1 a %d): ", jugadores[i].cantidadFichas);
                scanf("%d", &eleccion2);

                if(eleccion1 < 1 || eleccion1 > jugadores[i].cantidadFichas || eleccion2 < 1 || eleccion2 > jugadores[i].cantidadFichas || eleccion1 == eleccion2) {
                    printf("¡Seleccion invalida! Pierdes tu turno.\n");
                } else {
                    int indiceJUno = eleccion1 - 1;
                    int indiceJDos = eleccion2 - 1;

                    Ficha ficha1 = jugadores[i].mano[indiceJUno];
                    Ficha ficha2 = jugadores[i].mano[indiceJDos];

                    if (validarPar(ficha1, ficha2) == 1) {
                        printf("¡EXCELENTE! Conseguiste formar un par de 20.\n");

                        jugadores[i] = removerFichas(jugadores[i], indiceJUno, indiceJDos);

                        if (jugadores[i].cantidadFichas == 0) {
                            printf("\n=============================================\n");
                            printf("   ¡EL JUGADOR %d SE QUEDO SIN FICHAS Y GANO!\n", i + 1);
                            printf("=============================================\n");
                            juegoTerminado = 1;
                        }
                    } else {
                        printf("¡Error! Esas fichas no suman 20. Pierdes tu turno.\n");
                    }
                }
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

    printf("\n=== VUELVA PRONTO :D ===\n");
    return 0;
}