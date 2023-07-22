#include <iostream>

int main(){
    int t = 12;
    int* n = &t;
    std::cout << *n << std::endl;
    std::cout << &t << std::endl;
    int x = 98314;
    // No podemos asignarle un valor a un puntero dereferenciado si este puntero no adquiere
    // previamente una address. En este caso, n contiene la address que &t le proporciona
    *n = 10;
    std::cout << *n << std::endl;
    return 0;
}