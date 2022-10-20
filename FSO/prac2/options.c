#include <stdio.h>

 int main(int argc, char *argv[])
{
     printf("El número de argumentos introducidos es: %d\n", argc);
     for(int i = 0; i < argc; i++){
        if(argv[i][0] == '-' && argv[i][1] == 'c'){
        printf("El argumento %d es: Compilar", i);
        printf("\n");
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'E'){
        printf("El argumento %d es: Preprocesar", i);
        printf("\n");
        }
        else if(argv[i][0] == '-' && argv[i][1] == 'i'){
        printf("El argumento %d es: Incluir%s", i, argv[i]+2);
        printf("\n");
        }
        else{
        printf("El argumento %d es: %s", i, argv[i]);
        printf("\n");
        }
    }
}
