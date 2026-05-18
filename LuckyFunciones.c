#include "LuckyFunciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Banco setDomino(int maximoDomino) {
    Banco banco;
    banco.cantidadActual = 0;

    for (int i = 0; i <= maximoDomino; i++) {
        for (int j = i; j <= maximoDomino; j++) {

            if (i + j <= 20) {
                banco.lista[banco.cantidadActual].izquierda = i;
                banco.lista[banco.cantidadActual].derecha = j;
                banco.cantidadActual++;
            }

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

int validarPar(Ficha f1, Ficha f2) {
    int ceros = 0;

    if (f1.izquierda == 0) {
        ceros++;
    }
    if (f1.derecha == 0) {
        ceros++;
    }
    if (f2.izquierda == 0) {
        ceros++;
    }
    if (f2.derecha == 0) {
        ceros++;
    }

    int suma = f1.izquierda + f1.derecha + f2.izquierda + f2.derecha;

    if (ceros == 0) {
        if (suma == 20) {
            return 1;
        }
        return 0;
    } else {
        if (suma <= 20) {
            return 1;
        }
        return 0;
    }
}

Jugador removerFichas(Jugador jugador, int indiceJUno, int indiceJDos) {
    if (indiceJUno < indiceJDos) {
        int temp = indiceJUno;
        indiceJUno = indiceJDos;
        indiceJDos = temp;
    }

    for (int i = indiceJUno; i < jugador.cantidadFichas - 1; i++) {
        jugador.mano[i] = jugador.mano[i + 1];
    }
    jugador.cantidadFichas--;

    for (int i = indiceJDos; i < jugador.cantidadFichas - 1; i++) {
        jugador.mano[i] = jugador.mano[i + 1];
    }
    jugador.cantidadFichas--;

    return jugador;
}

EstadoReparto pedirCuatroFichas(Banco bancoActual, Jugador jugadorActual) {
    EstadoReparto resultado;
    resultado.banco = bancoActual;
    resultado.jugador = jugadorActual;

    int cantidadATomar = 4;
    if (resultado.banco.cantidadActual < 4) {
        cantidadATomar = resultado.banco.cantidadActual;
    }

    int indiceCima = 0;
    int indiceMano = 0;

    for (int i = 0; i < cantidadATomar; i++) {
        indiceCima = resultado.banco.cantidadActual - 1;
        Ficha fichaTomada = resultado.banco.lista[indiceCima];

        indiceMano = resultado.jugador.cantidadFichas;
        resultado.jugador.mano[indiceMano] = fichaTomada;

        resultado.banco.cantidadActual--;
        resultado.jugador.cantidadFichas++;
    }

    return resultado;
}

void guardarGanador(char nombreGanador[], int pares) {
    RegistroGanador nuevoGanador;

    strcpy(nuevoGanador.nombre, nombreGanador);
    nuevoGanador.paresFormados = pares;

    strcpy(nuevoGanador.fecha, "DD/MM/AAAA");

    FILE *archivo = fopen("ganadores.bin", "ab");

    if (archivo != NULL) {
        fwrite(&nuevoGanador, sizeof(RegistroGanador), 1, archivo);
        fclose(archivo);
        printf("\nEl registro de tu victoria se ha guardado correctamente en 'ganadores.bin'.\n");
    } else {
        printf("\nERROR\nNo se pudo crear o abrir el archivo de ganadores.\n");
    }
}