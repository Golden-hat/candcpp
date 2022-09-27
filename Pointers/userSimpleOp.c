#include <stdio.h>
int main(){

    double n;
    double p;
    printf("Please introduce the values to be multiplied:\n");
    scanf("%lf", &n);
    scanf("%lf", &p);
    mult(n, p);
    return 0;
    
}

void mult(double n, double p){
    double x = n*p;
    printf("THE RESULT OF THE OPERATION IS = %lf", x);
}
