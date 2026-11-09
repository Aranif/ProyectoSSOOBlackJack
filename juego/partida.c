
#include "../control/control.h"

typedef struct{
    buffer[4][13];
    int jugadores; 
    int aputas[4]; //apuestas de cada jugador
}CartasMemoria; 


int main(void){

    //Memoria compartida 
    key_t clave;
    int shmid;
    CartasMemoria  *seg = NULL;
    clave = ftok(".",'S');

    if((shmid = shmget(clave, sizeof(CartaMemoria), IPC_CREAT | IPC_EXCL|0660)) == -1){
        printf("La mesa ya está creada. \n");
    }else{
        printf("Se ha creado la mesa.\n");

    }

    if((seg = shmat(shmid, NULL, 0)) != (CartaMemoria *)-1){
        printf("Mapeada.\n");
        for(int i = 0; i < 4; i++){
            for (int j = 0; j < 13; j++){
                seg->buffer[i]][j] = j+1;
            }
        } 
        seg->jugadores = 0;
        seg->apuestas ={0}; 
        shmdt(seg); //cerramos memoria

    }else{
        printf("Error al mapear la partida.\n");

    }

    //Proceso de crupier
    pid_t pid = fork(); 
    int estado;
    switch(pid){
        case -1:
            perror("fork error.\n");
            break;
        case 0:
            while(1); //espera señales
            break;
        default:
            wait(&estado); // espera a que acabe el hijo
    }
return 0; 
}