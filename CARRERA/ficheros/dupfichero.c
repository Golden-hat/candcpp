#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int arg, char *argv[]){
    int fd; // al fichero se le asigna un descriptor de archivo de valor int, por el que se identifica.
    
    //open = abre descriptor de archivos ("nombre de archivo", Permisos | Crear , Modo de archivo)
    fd = open ("output.txt", O_RDWR | O_CREAT, S_IRWXU);
    if(dup2(fd, STDOUT_FILENO) == -1){
        printf("Error llamando a dup2");
        exit(-1);
    }
    execl("/bin/ls","ls","-la",NULL);
    close(fd);
    return 0;
}