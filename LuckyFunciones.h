#ifndef LUCKYFUNCIONES_H
#define LUCKYFUNCIONES_H

typedef struct {
    int izquierda;
    int derecha;
} Ficha;

typedef struct {
    Ficha lista[91];
    int cantidadActual;
} Banco;

typedef struct {
    Ficha mano[28];
    int cantidadFichas;
    int paresFormados;
} Jugador;

typedef struct {
    Banco banco;
    Jugador jugador;
} EstadoReparto;

typedef struct {
    char nombre[50];
    int paresFormados;
    char fecha[15];
} RegistroGanador;

typedef struct {
    int numeroJugador;
    Ficha ficha1;
    Ficha ficha2;
} RegistroMovimiento;

Banco setDomino(int maximoDomino);
Banco mezclarSet(Banco banco);
EstadoReparto repartirSeisCartas(Banco bancoActual, Jugador jugadorActual);
EstadoReparto pedirCuatroFichas(Banco bancoActual, Jugador jugadorActual);

int validarPar(Ficha f1, Ficha f2);
Jugador removerFichas(Jugador jugador, int indiceJUno, int indiceJDos);
void guardarGanador(char nombreGanador[], int pares);

void inicializarArchivoPartida();
void guardarMovimiento(int numJugador, Ficha f1, Ficha f2);

#endif