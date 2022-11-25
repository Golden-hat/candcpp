#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc,char *argv[]) {
    int fd;
    char *arch = "ls_output.txt";
    mode_t fd_mode = S_IRWXU;// file premissions
 
    fd = open(arch,O_RDONLY | O_CREAT,fd_mode); //open create has no effect in this case, as file already exists.
    if (dup2(fd,STDOUT_FILENO) == -1) { 
        printf("Error calling dup2\n");
        exit(-1);
    }

    fprintf(stdout, execl("/bin/cat","cat",NULL));
    fprintf(stderr,"error: not redirected\n");
    fprintf(stderr,"Check file %s\n",arch);
    close(fd);
    return(0);
}

