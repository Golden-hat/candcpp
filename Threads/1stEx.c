#include <pthread.h>
#include <stdio.h>

void funcion(void *p) {
    printf("Soy un hilo feliz!\n");
    sleep(10);
}

int main(void){
    pthread_t id_hilo;
    pthread_attr_t atributos;
    printf("Hilo principal: principio\n");

    pthread_attr_init(&atributos);
    pthread_create(&id_hilo, &atributos, *funcion, NULL);

    printf("Hilo principal: He creado un hermano\n");

    pthread_join(id_hilo, NULL);

    printf("Hilo principal: Acabo!\n");
} 