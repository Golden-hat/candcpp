#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int status;
    pid_t pid = fork();

    char* argumentos[] = {"ps", 0};

    if(pid == 0){   
        printf("Soy el hijo con PID %ld y mi padre es %ld\n", (long)getpid(), (long)getppid());
        sleep(4);
        printf("Ya he terminado\n");
    }
    else{
        printf("Soy el proceso padre, con PID: %d\n", getpid());
        if(wait(&status) != -1){
            printf("Proceso ejecutado correctamente\n");
        }
    }
    return 0;
}