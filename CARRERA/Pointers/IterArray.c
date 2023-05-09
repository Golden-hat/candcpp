#include <stdio.h>

int main(){

    int Data[5] = {2,3,4,5,6};
    double sumaTot = 0;

    for(int i = 0; i < 5; i++){
        printf("The number in position %d is: %d\n", i, Data[i]);
        sumaTot += Data[i];
    }
    printf("The total sum of your array elements is: %f\n", sumaTot);
    return 0;
}