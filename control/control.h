#include <stdio.h> 
#include <sys/wait.h>
#include <sys/types.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
#include <string.h> 
#include <ctype.h>
#include <semaphore.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define NO_HAYCARTA 0

#define AS1 1
#define AS2 11

#define FIGURA 10

typedef struct{
    int buffer[4][13];
    int jugadores; 
    int apuestas[4]; //apuestas de cada jugador´
    int cartaCrupier;
    int sumCartaCrupier; 
}CartasMemoria; 

//Todo de Semaforos
sem_t *semID = NULL;

//Todo de Memoria C
key_t clave;
int shmid;
CartasMemoria  *seg = NULL;



//Esto lo usan todos los jugadores crupier incluido
int obtenerCartas(CartasMemoria *seg){
    int i = 0;
    int figuraUno = 0;
    int numeroDos = 0;
    while(i == 0){
        figuraUno = rand() % 4;
        numeroDos = rand() % 13;
        i = seg->buffer[figuraUno][numeroDos]; 
    }
    seg->buffer[figuraUno][numeroDos] = 0;
    return i;
}