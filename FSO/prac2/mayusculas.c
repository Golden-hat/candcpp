#include <stdio.h>  
#define TAM_CADENA 200 

int main() {
    // Puntero a caracter para copiar las cadenas char *p1, *p2; 
    char *p1;
    char *p2;

    // A) Definir las variables cadena y cadena2  
    char cadena[TAM_CADENA];
    char cadena2[TAM_CADENA];

    // B) Leer cadena de consola
    scanf("%s", cadena);

    // C) Convertir a mayúsculas 
    p1 = cadena;     
    p2 = cadena2;
    int i = 0;
    while (p1[i] != '\0') { 
        if(p1[i] >= 'a' && p1[i] <= 'z') {
            p2[i] = p1[i] -32;
        }
        i++;
    }
    printf("%s", p2);
 
    // Acordarse de poner el cero final en cadena2 
    // D) Sacar por consola la cadena2. 
} 
