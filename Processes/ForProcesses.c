#include <stdio.h>

int main(){
    
    printf("Hello, im the parent process with %d\n", (long)getpid());
    int nProcess = 5;
    int pid;
    for(int i = 0; i < nProcess; i++){
        pid = fork();
        if(pid != 0){
            break;
        }
        printf("Hello, im the child process with %d. My parent is: %d\n", (long)getpid(), (long)getppid());
    }
    wait(10);
    return 0;
}