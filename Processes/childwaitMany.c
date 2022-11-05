#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define NPROCESSES 4

int main(){
    pid_t pid[NPROCESSES];
    int i, status;

    for(int i = 0; i < NPROCESSES; i++){
        pid[i] = fork();
        if(pid[i] == 0){
            printf("Soy el hijo %d, del padre %d.\n",getpid(), getppid());
            sleep(2*i+5);
            exit(0);
            break;
        }
    }

    printf("Soy el proceso padre con PID: %d.\n", getpid());
    
    int is = 1;
    while(wait(&status) > 0){
        printf("Mi %dº hijo ya ha terminado.\n", is);
        is++;
    }
    exit(0);
    return 0;
}