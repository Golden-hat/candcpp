#include <stdio.h>
#include <stdlib.h>

int main(){
    for(int i = 1; i <= 5; i++){
        int val_return = fork();
        if(val_return == 0){
            printf("%d\n",val_return);
            printf("Hijo creado en iteración=%d\n",i);
            exit(i);
            break;
        }
    }
    sleep(10);
    exit(0);

    return 0;
}