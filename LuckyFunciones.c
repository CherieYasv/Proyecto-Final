#include "LuckyFunciones.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

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

EstadoReparto repartirModoPrueba(Banco bancoActual, Jugador jugadorActual) {
    EstadoReparto resultado;
    resultado.banco = bancoActual;
    resultado.jugador = jugadorActual;

    Ficha fichasTrampa[6] = {{6, 6}, {3, 5}, {5, 6}, {4, 5}, {4, 6}, {5, 5}};

    for (int k = 0; k < 6; k++) {
        for (int i = 0; i < resultado.banco.cantidadActual; i++) {
            if (resultado.banco.lista[i].izquierda == fichasTrampa[k].izquierda &&
                resultado.banco.lista[i].derecha == fichasTrampa[k].derecha) {

                int indiceMano = resultado.jugador.cantidadFichas;
                resultado.jugador.mano[indiceMano] = resultado.banco.lista[i];
                resultado.jugador.cantidadFichas++;

                resultado.banco.lista[i] = resultado.banco.lista[resultado.banco.cantidadActual - 1];
                resultado.banco.cantidadActual--;
                break;
            }
        }
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

ResultadoFecha obtenerFechaActual() {
    ResultadoFecha resultado;
    resultado.consultaExitosa = 0;
    strcpy(resultado.fechaCadena, "DD/MM/AAAA");
    time_t tiempoActual;
    tiempoActual = time(NULL);

    if (tiempoActual == -1) {
        return resultado;
    }

    struct tm tiempoLocal = localtime(&tiempoActual)[0];

    int dia = tiempoLocal.tm_mday;
    int mes = tiempoLocal.tm_mon + 1;
    int anio = tiempoLocal.tm_year + 1900;

    if (dia < 10 && mes < 10) {
        sprintf(resultado.fechaCadena, "0%d/0%d/%d", dia, mes, anio);
    }
    else if (dia < 10 && mes >= 10) {
        sprintf(resultado.fechaCadena, "0%d/%d/%d", dia, mes, anio);
    }
    else if (dia >= 10 && mes < 10) {
        sprintf(resultado.fechaCadena, "%d/0%d/%d", dia, mes, anio);
    }
    else {
        sprintf(resultado.fechaCadena, "%d/%d/%d", dia, mes, anio);
    }

    resultado.consultaExitosa = 1;
    return resultado;
}

void guardarGanador(char nombreGanador[], int pares) {
    RegistroGanador nuevoGanador;

    strcpy(nuevoGanador.nombre, nombreGanador);
    nuevoGanador.paresFormados = pares;

    ResultadoFecha fechaHoy = obtenerFechaActual();
    strcpy(nuevoGanador.fecha, fechaHoy.fechaCadena);

    FILE *archivo = fopen("ganadores.bin", "ab");

    if (archivo != NULL) {
        fwrite(&nuevoGanador, sizeof(RegistroGanador), 1, archivo);
        fclose(archivo);
        printf("\nEl registro de tu victoria se ha guardado correctamente en 'ganadores.bin'.\n");
    } else {
        printf("\nERROR\nNo se pudo crear o abrir el archivo de ganadores.\n");
    }
}

void inicializarArchivoPartida() {
    FILE *archivo = fopen("partida.bin", "wb");
    if (archivo != NULL) {
        fclose(archivo);
    }
}

void guardarMovimiento(int numJugador, Ficha f1, Ficha f2) {
    RegistroMovimiento mov;
    mov.numeroJugador = numJugador;
    mov.ficha1 = f1;
    mov.ficha2 = f2;
    FILE *archivo = fopen("partida.bin", "ab");
    if (archivo != NULL) {
        fwrite(&mov, sizeof(RegistroMovimiento), 1, archivo);
        fclose(archivo);
    }
}

void guardarPartidaFinal() {
    ResultadoFecha fecha = obtenerFechaActual();
    char nombreBase[50];
    char nombreFinal[50];

    char dia[3] = { fecha.fechaCadena[0], fecha.fechaCadena[1], '\0' };
    char mes[3] = { fecha.fechaCadena[3], fecha.fechaCadena[4], '\0' };
    char anio[5] = { fecha.fechaCadena[6], fecha.fechaCadena[7], fecha.fechaCadena[8], fecha.fechaCadena[9], '\0' };

    sprintf(nombreBase, "partida%s%s%s", dia, mes, anio);
    sprintf(nombreFinal, "%s.bin", nombreBase);

    int contador = 1;
    FILE *verificador = fopen(nombreFinal, "rb");
    while (verificador != NULL) {
        fclose(verificador);
        sprintf(nombreFinal, "%s-%d.bin", nombreBase, contador);
        contador++;
        verificador = fopen(nombreFinal, "rb");
    }

    FILE *origen = fopen("partida.bin", "rb");
    if (origen == NULL) {
        printf("\nERROR: No se encontro la informacion de la partida.\n");
        return;
    }

    FILE *destino = fopen(nombreFinal, "wb");
    if (destino != NULL) {
        RegistroMovimiento mov;
        while (fread(&mov, sizeof(RegistroMovimiento), 1, origen) == 1) {
            fwrite(&mov, sizeof(RegistroMovimiento), 1, destino);
        }
        fclose(destino);
        printf("\nLa partida ha sido guardada exitosamente bajo el nombre: %s\n", nombreFinal);
    } else {
        printf("\nERROR: No se pudo crear el archivo final.\n");
    }
    fclose(origen);
}

void mostrarRepeticion() {
    char nombreArchivo[50];

    printf("\nIngrese el nombre del archivo de la partida a consultar (ej. partida18052026.bin): ");

    fgets(nombreArchivo, sizeof(nombreArchivo), stdin);
    nombreArchivo[strcspn(nombreArchivo, "\n")] = '\0';

    FILE *archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("\nERROR\nEl archivo '%s' no existe o no se pudo abrir.\n", nombreArchivo);
        return;
    }

    RegistroMovimiento movimientos;
    printf("\n=== REPETICION DE JUGADAS ===\n");
    while (fread(&movimientos, sizeof(RegistroMovimiento), 1, archivo) == 1) {
        printf("Jugador %d: [%d|%d] + [%d|%d]\n",
               movimientos.numeroJugador, movimientos.ficha1.izquierda, movimientos.ficha1.derecha,
               movimientos.ficha2.izquierda, movimientos.ficha2.derecha);
    }
    fclose(archivo);
}

void mostrarGanadores() {
    FILE *archivo = fopen("ganadores.bin", "rb");
    if (archivo == NULL) {
        printf("\nEl apartado de ganadores esta vacio por ahora.\n");
        return;
    }
    RegistroGanador registro;
    printf("\n=== GANADORES ===\n");
    printf("%-20s | %-10s | %-10s\n", "NOMBRE", "PARES", "FECHA");
    while (fread(&registro, sizeof(RegistroGanador), 1, archivo) == 1) {
        printf("%-20s | %-10d | %-10s\n", registro.nombre, registro.paresFormados, registro.fecha);
    }
    fclose(archivo);
}