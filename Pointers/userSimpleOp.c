#include <stdlib.h>
#include <math.h>

int main(){

    double n;
    double p;
    printf("Please introduce the values to be multiplied:\n");
    scanf("First value: ", &n);
    scanf("Second value: ", &p);
    multiplication(n, p);
    return 0;

}

void multiplication(double n, double p){
    double x = n*p;
    printf("THE RESULT OF THE OPERATION IS = %lf", x);
}
