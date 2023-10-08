#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>
#include <queue>
#include <random>

int grid[9][9] = {
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
    {1,2,3,4,5,6,7,8,9},
};

void printGrid(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            std::cout << grid[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

int main(){
    printGrid();
    return 0;
}




