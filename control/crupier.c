#include "control.h"


int main(void){
    //Variables a usar
    int carta = NO_HAYCARTA; 
    int sumaCartaCrupier = 0; // Variable para almacenar la suma de las cartas del crupier
    int interaccion = 0; 

    //Parametros semaforos
    semID = sem_open("mutex", 0);
    //parametros de memoria
    clave = ftok(".",'S');

    if((shmid = shmget(clave, sizeof(CartasMemoria), 0)) == -1){
        printf("Error al acceder a la memoria compartida.\n");
    }else{
        if((seg = shmat(shmid, NULL, 0)) != (CartasMemoria *)-1){
            sem_wait(semID); //Bloqueamos el semaforo
            while (sumaCartaCrupier < 17) { // El crupier debe seguir pidiendo cartas hasta que su suma sea al menos 17
                //si hay dos interacciones hay dos cartas
                carta = obtenerCartas(seg);
                
                if (sumaCartaCrupier == 0) {
                    seg->cartaCrupier = carta; // Actualizamos la carta que muestra el crupier en la memoria compartida
                }
                sumaCartaCrupier += carta; // Actualizamos la suma de las cartas del crupier
                interaccion++;
            }

            carta = obtenerCartas(seg);
            sem_post(semID); //Desbloqueamos el semaforo
            printf("Carta uno: %d\n", seg->cartaCrupier);
            shmdt(seg); //Cerramos la memoria compartida

            if(interaccion == 2 && sumaCartaCrupier == 21){
                printf("El crupier tiene un blackjack.\n");
                
        }else
            printf("Error al mapear la memoria compartida.\n");
        
    }
    sem_close(semID); //Cerramos el semaforo
        
    return 0;
}