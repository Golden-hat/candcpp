#include <stdio.h>
#include <stdlib.h>

int main(){
    for(int i = 1; i <= 5; i++){
        int val_return = fork();
        if(val_return == 0){
            printf("Hijo creado en iteración=%d\n",i);
            exit(i);
        }
    }
    wait();
    exit(0);
}
