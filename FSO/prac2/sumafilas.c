#include <stdio.h>
#define TAM_FILA 100
#define NUM_FILAS 10

struct FILA {
    float datos[TAM_FILA];
    float suma;
};

// A)Defina variable filas como un vector de FILA de tamaño NUM_FILAS
struct FILA filas[NUM_FILAS];

void suma_fila(struct FILA *pf) {
    float total = 0;
    for (int i = 0; i < TAM_FILA; i++) {
        total += pf->datos[i];
    }
    pf->suma = total;
    printf("La suma final es %f\n", total);
}

// Inicie las filas con el valor i*j
void inicia_filas() {
    int i, j;
    for (i = 0; i < NUM_FILAS; i++) {
        for (j = 0; j < TAM_FILA; j++) {
            filas[i].datos[j] = (float)i*j;
        }
    }       
}

int main() {
    int i;
    float suma_total;

    inicia_filas();
    // C) Complete bucle
    suma_total = 0;
    for (i = 0; i < NUM_FILAS; i++) {
        suma_fila(&filas[i]);
            printf("La suma de la fila %u es %f\n", i, filas[i].suma);
        suma_total += filas[i].suma;
    }
    printf("La suma final es %f\n", suma_total);
    return 0;
}