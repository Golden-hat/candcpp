#include <stdio.h>
#include <stdlib.h>

int main(){
    int status;

    for(int i = 1; i <= 5; i++){    

        int val_return = fork();
        if(val_return == 0){
            printf("Hijo creado en iteración=%d\n",i);
            sleep(5+i);
            exit(i);
        }
    }

    for(int i = 1; i <= 5; i++){
        int ret = wait();
        printf("Hijo esperado: %d\n", ret);
    }
    exit(0);
}
