#include <stdio.h>

 int main(int argc, char *argv[])
{
     printf("El número de argumentos introducidos es: %d\n", argc);
     for(int i = 0; i < argc; i++){
        printf("El argumento %d el siguiente: ", i);
        printf("%s",argv[i]);
        printf("\n");
    }
}
