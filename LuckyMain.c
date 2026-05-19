#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "LuckyFunciones.c"

int main() {
    int opcionPrincipal = 0;
    srand(time(NULL));

    printf("     ==== LUCKY 20 ====");
    printf("\n\n¡Hola!, vamos a jugar Lucky 20.\n");

    do {
        printf("\n===== MENU PRINCIPAL =====\n");
        printf("1. Jugar una partida\n");
        printf("2. Ver repeticion de una partida\n");
        printf("3. Ver historial de ganadores\n");
        printf("4. Salir\n");
        printf("Elige una opcion: ");

        scanf("%d", &opcionPrincipal);
        while(getchar() != '\n');

        if (opcionPrincipal == 1) {
            int setDominos = 0;
            int cantidadJugadores = 0;
            int modoPrueba = 0;
            char opcionPrueba;

            do {
                printf("\n¿Con que set de domino desea jugar? (6, 9 o 12)\nDoble: ");
                int lecturaExitosa = scanf("%d", &setDominos);
                while(getchar() != '\n');
                if (lecturaExitosa != 1 || (setDominos != 6 && setDominos != 9 && setDominos != 12)) {
                    printf("\nERROR\n=== Solo puedes escribir el numero 6, 9 o 12 ===\n");
                    setDominos = 0;
                }
            } while (setDominos != 6 && setDominos != 9 && setDominos != 12);

            do {
                printf("\n¿Cuantos jugadores desean jugar? (1 a 4 jugadores): ");
                int lecturaExitosa = scanf("%d", &cantidadJugadores);
                while(getchar() != '\n');
                if (lecturaExitosa != 1 || cantidadJugadores < 1 || cantidadJugadores > 4) {
                    printf("\nERROR\n=== Ingresa un numero valido entre 1 y 4 ===\n");
                    cantidadJugadores = 0;
                }
            } while (cantidadJugadores < 1 || cantidadJugadores > 4);

            do {
                printf("\n¿Deseas activar el Modo Prueba para el Jugador 1? (s/n): ");
                scanf(" %c", &opcionPrueba);
                while(getchar() != '\n');

                if (opcionPrueba == 's' || opcionPrueba == 'S') {
                    modoPrueba = 1;
                } else if (opcionPrueba == 'n' || opcionPrueba == 'N') {
                    modoPrueba = 0;
                } else {
                    printf("\nERROR\n=== Por favor ingresa unicamente la letra 's' para Si o 'n' para No ===\n");
                }
            } while (opcionPrueba != 's' && opcionPrueba != 'S' && opcionPrueba != 'n' && opcionPrueba != 'N');

            Banco banco = setDomino(setDominos);
            banco = mezclarSet(banco);
            printf("\nFichas totales mezcladas: %d\n", banco.cantidadActual);

            Jugador jugadores[4];
            for (int i = 0; i < cantidadJugadores; i++) {
                jugadores[i].cantidadFichas = 0;
                jugadores[i].paresFormados = 0;

                EstadoReparto paquete;
                if (modoPrueba == 1 && i == 0) {
                    paquete = repartirModoPrueba(banco, jugadores[i]);
                    printf("\nModo Prueba activado. Jugador 1 recibe mano ganadora.\n");
                } else {
                    paquete = repartirSeisCartas(banco, jugadores[i]);
                }

                banco = paquete.banco;
                jugadores[i] = paquete.jugador;
            }

            printf("\n=== REPARTO INICIAL FINALIZADO ===\n");
            int juegoTerminado = 0;
            char opcionMenu;

            printf("\n\n====== COMIENZA EL JUEGO ======\n");
            inicializarArchivoPartida();

            while (juegoTerminado == 0) {
                for (int i = 0; i < cantidadJugadores; i++) {
                    if (juegoTerminado == 1) {
                        break;
                    }

                    printf("\nTURNO DEL JUGADOR %d", i + 1);
                    printf("\nFichas disponibles en el banco: %d", banco.cantidadActual);
                    printf("\nTu mano: ");
                    for(int j = 0; j < jugadores[i].cantidadFichas; j++) {
                        printf("%d->[%d|%d] ", j + 1, jugadores[i].mano[j].izquierda, jugadores[i].mano[j].derecha);
                    }

                    printf("\n\n¿Que deseas hacer?\na) Formar un par (sumar 20)\nb) Pedir 4 fichas del banco\nc) Retirarse\nElige: ");
                    scanf(" %c", &opcionMenu);
                    while(getchar() != '\n');

                    if (opcionMenu == 'a' || opcionMenu == 'A') {
                        int eleccion1, eleccion2;
                        printf("Ficha 1: ");
                        scanf("%d", &eleccion1);
                        printf("Ficha 2: ");
                        scanf("%d", &eleccion2);
                        while(getchar() != '\n');

                        if(eleccion1 < 1 || eleccion1 > jugadores[i].cantidadFichas || eleccion2 < 1 || eleccion2 > jugadores[i].cantidadFichas || eleccion1 == eleccion2) {
                            printf("ERROR: Posiciones invalidas.\n");
                        } else {
                            Ficha ficha1 = jugadores[i].mano[eleccion1 - 1];
                            Ficha ficha2 = jugadores[i].mano[eleccion2 - 1];

                            if (validarPar(ficha1, ficha2) == 1) {
                                printf("Conseguiste formar un par de 20.\n");
                                jugadores[i].paresFormados++;
                                guardarMovimiento(i + 1, ficha1, ficha2);
                                jugadores[i] = removerFichas(jugadores[i], eleccion1 - 1, eleccion2 - 1);

                                if (jugadores[i].cantidadFichas == 0) {
                                    printf("\n=== JUGADOR %d GANA ===\n", i + 1);
                                    char nombreGanador[50];
                                    printf("Nombre para el record: ");
                                    fgets(nombreGanador, sizeof(nombreGanador), stdin);
                                    nombreGanador[strcspn(nombreGanador, "\n")] = '\0';
                                    guardarGanador(nombreGanador, jugadores[i].paresFormados);
                                    juegoTerminado = 1;
                                }
                            } else printf("ERROR: No suman 20.\n");
                        }
                    } else if (opcionMenu == 'b' || opcionMenu == 'B') {
                        if (banco.cantidadActual == 0) {
                            printf("Banco vacio.\n");
                        }
                        else {
                            EstadoReparto paquete = pedirCuatroFichas(banco, jugadores[i]);
                            banco = paquete.banco;
                            jugadores[i] = paquete.jugador;
                        }
                    } else if (opcionMenu == 'c' || opcionMenu == 'C') {
                        juegoTerminado = 1;
                        break;
                    }
                }
            }

            char opcionGuardar;
            do {
                printf("\n¿Deseas guardar el registro completo de movimientos de esta partida? (s/n): ");
                scanf(" %c", &opcionGuardar);
                while(getchar() != '\n');

                if (opcionGuardar == 's' || opcionGuardar == 'S') {
                    guardarPartidaFinal();
                } else if (opcionGuardar != 'n' && opcionGuardar != 'N') {
                    printf("\nERROR\n=== Por favor ingresa unicamente la letra 's' para Si o 'n' para No ===\n");
                }
            } while (opcionGuardar != 's' && opcionGuardar != 'S' && opcionGuardar != 'n' && opcionGuardar != 'N');

        } else if (opcionPrincipal == 2) {
            mostrarRepeticion();
        } else if (opcionPrincipal == 3) {
            mostrarGanadores();
        } else if (opcionPrincipal != 4) {
            printf("\nERROR\nOpcion no valida. Por favor ingresa un numero del 1 al 4.\n");
        }

    } while (opcionPrincipal != 4);

    printf("\n=== VUELVA PRONTO :D ===\n");
    return 0;
}