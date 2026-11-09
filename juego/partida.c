
#include "../control/control.h"


int main(void){
    //semaforo variables

    //Memoria compartida variables en .h
    clave = ftok(".",'S');
    //Memoria C
    if((shmid = shmget(clave, sizeof(CartasMemoria), IPC_CREAT | IPC_EXCL|0660)) == -1){
        printf("La mesa ya está creada. \n");
    }else{
        printf("Se ha creado la mesa.\n");

    }

    if((seg = shmat(shmid, NULL, 0)) != (CartasMemoria *)-1){ //Inicializa la baraja, las apuestas y el numero de jugadores
        printf("Mapeada.\n");
        for(int i = 0; i < 4; i++){
	        seg->apuestas[i] = 0;
            for (int j = 0; j < 13; j++){
                seg->buffer[i][j] = j+1;
            }
        } 
        seg->jugadores = 0;
        shmdt(seg); //cerramos memoria

    }else{
        printf("Error al mapear la partida.\n");

    }

    //Semaforos
    semID = sem_open("mutex", O_CREAT, 0660, 1);
    if (semID != SEM_FAILED) {
        printf("Semaforo creado correctamente.\n");
        sem_close(semID); // Cierra el semáforo después de crearlo
    }else
        printf("Error al crear el semaforo.\n");

    //Proceso de crupier
    int estado;
    pid_t pid = fork(); 
    
    switch(pid){
        case -1:
            perror("fork error.\n");
            break;
        case 0:
	    execlp("./crupier","", NULL);
	    perror("exec");
            while(1); //espera señales
            break;
        default:
            wait(&estado); // espera a que acabe el hijo
    }
return 0; 
}
