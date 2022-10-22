#include <stdio.h>
#include <stdlib.h>

int main(){
    int status;

    for(int i = 1; i <= 5; i++){    

        int val_return = fork();
        if(val_return == 0){
            printf("Hijo creado en iteración=%d\n",i);
            sleep(20);
            exit(i);
        }
    }

    for(int i = 1; i <= 5; i++){
        wait(&status);
    }
    
    sleep(10);
    exit(0);
    return 1;
}
