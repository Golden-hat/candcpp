#include <stdio.h>

#define PI 3.1416

float areaC(float radius){
    return (PI * (radius* radius));
}

int main() {
    float area, radio;
    radio = 10;
    area = areaC(radio);
    printf("Area del circulo de radio %f es %f\n", radio, area);
    return 0;
}
