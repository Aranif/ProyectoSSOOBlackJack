#include "control.h"

int main(void){
    if(sem_unlink("mutex") == 0){
        printf("Semaforo eliminado correctamente.\n");
    }else{
        printf("Error al eliminar el semaforo.\n");
    }

    clave = ftok(".",'S');
    if((shmid = shmget(clave, sizeof(CartasMemoria), 0)) == -1){
        printf("Error al acceder a la memoria compartida.\n");
    }else{
        if(shmctl(shmid, IPC_RMID, NULL) == 0){
            printf("Memoria compartida eliminada correctamente.\n");
        }else{
            printf("Error al eliminar la memoria compartida.\n");   
        }
    }
return 0;
    
}