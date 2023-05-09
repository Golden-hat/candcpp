#include <stdio.h>
#define TAM_CADENA 200 

int main(){

    //Leeremos una cadena de consola mediante scanf.
    char cadena[TAM_CADENA];
    char cadenaResult[TAM_CADENA];

    //El operador & devuelve la dirección de memoria de una variable.
    
    /*Con esto, entonces, estamos guardando una cadena input en la dirección de memoria de
    nuestro array, poniendo así cada carácter en una celda de memoria.
    Pongamos que el almacenamiento empieza en 0x0010. El primer carácter está en 10, el segundo
    en 14, el tercero en 1C... y así sucesivamente*/

    scanf("%s", &cadena);

    //Puntero de caracteres que almacenará la posición de memoria en la que estemos.
    char *pc;
    char *pcR;

    //Ahora, copiamos la dirección de memoria de estas cadenas a los punteros previamente declarados.
    pc = cadena;
    pcR = cadenaResult;

    //El asterisco aplicado a un puntero ya declarado sirve para referirnos al DATO almacenado en esa posición de memoria (indirección).
    while(*pc != '\0'){
        printf("The character in address position %d is: %c.\n", pc ,*pc);
        *pcR = *pc;
        //Aumentamos la dirección de memoria para pillar los siguientes valores de la cadena.
        pc++;
        pcR++;
    }
    // Acordarse de poner el cero final en cadena2.
    *pcR = '\0';
    printf("The String is: %s.\n", cadenaResult);
    return 0;
};
