#include <iostream>

void printElem(void* elem, char type){
    switch(type){
        /*
            el puntero de tipo void no distingue el tipo de
            punteros. Por ello, hay que coercionarlo al utilizarse.

            con (char*) / (int*) coercionamos el puntero void a que
            sea de tipo int* o char*. Al puntero void se le asigna 
            el nombre de variable elem. Finalmente, se dereferencia
            este puntero con un *(...)
        */
        case 'c': std::cout << *((char*)elem) << std::endl; break;
        case 'i': std::cout << *((int*)elem) << std::endl; break;
    }
}

void returnMaxAndMinElement(int* array, int size, int* min, int* max){
    for(int i = 0; i < size; i++){
        if(*max < array[i]){
            *max = array[i];
        }
        if(*min > array[i]){ 
            *min = array[i];
        }
    }
    std::cout << "min is: " << *min << std::endl;
    std::cout << "max is: " << *max << std::endl;
}

int main(){
    int x = 10;
    char z = 'a';
    printElem(&x, 'i');
    printElem(&z, 'c');

    int size = 6;
    int array[size]  = {1,5,321,-34,54,1425};
    int min = array[0];
    int max = array[0];

    returnMaxAndMinElement(array, size, &min, &max);

    return 0;
}