#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

int main(){
    int status;
    pid_t pid = fork();

    char* argumentos[] = {"ls", "-l", 0};
    
    switch(pid){
        case -1:
            printf("No se ha podido crear un subproceso\n");
            break;
        case 0:
            printf("Soy el hijo con PID: %d, y voy a ejecutar la siguiente función: ", getpid());
            printf("%s\n", argumentos[0]);
            if(execvp("ls", argumentos)==-1){
                printf("Error al ejecutar la orden.\n");
                exit(0);
            }
            exit (0);
            break;
        default:
            printf("Soy el proceso padre, con PID: %d\n", getpid());
            exit(0);
            break;
    }
    return 0;
}