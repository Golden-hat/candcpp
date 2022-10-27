#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/*** final_state **/
int MAX_PROC = 4;

int main(){
    int i;
    int final_state;

    for(i=0; i<MAX_PROC; i++){
        int val_return= fork();
        if (val_return==0){
            printf("Son %ld created in iteration %d\n",(long) getpid(),i);
        }
        /*father out of the loop for */
        else{ 
            printf("Father %ld, iteration %d\n", (long)getpid(),i);
            printf("I have created a son %ld\n",(long) val_return);
            break;
        }
    }
    
    /*wait all my sons and make exit*/
    while(wait(&final_state)>0){
        printf("Father %ld iteration %d\n",(long) getpid(),i);
        printf( "My son said %d\n",WEXITSTATUS(final_state));
        printf( "My son said %f\n", final_state/256);
    }
    sleep(1);
    exit(i);
}
