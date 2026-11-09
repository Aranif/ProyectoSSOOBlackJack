#include "../control/control.h"

int main(void){
        //Variables a usar
    int cartaUno = NO_HAYCARTA; 
    int cartaDos = NO_HAYCARTA; 

    //Parametros semaforos
    semID = sem_open("mutex", 0);
    //parametros de memoria
    clave = ftok(".",'S');

    if((shmid = shmget(clave, sizeof(CartasMemoria), 0)) == -1){
        printf("Error al acceder a la memoria compartida.\n");
    }else{
        if((seg = shmat(shmid, NULL, 0)) != (CartasMemoria *)-1){
            sem_wait(semID); //Bloqueamos el semaforo
            cartaUno = obtenerCartas(seg);
            cartaDos = obtenerCartas(seg);
            sem_post(semID); //Desbloqueamos el semaforo
            printf("Carta uno y dos: %d, %d\n", cartaUno, cartaDos);
            shmdt(seg); //Cerramos la memoria compartida
        }else
            printf("Error al mapear la memoria compartida.\n");
        
    }
    sem_close(semID); //Cerramos el semaforo

    //Interfaz jugador
    

    return 0; 
}