#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>
#include <queue>
#include <random>

int grid[9][9] = 
{{ 8, 0, 7, 6, 0, 3, 0, 0, 9 },
{ 0, 0, 0, 0, 0, 0, 3, 0, 1 },
{ 5, 0, 0, 9, 0, 4, 0, 0, 0 },
{ 0, 9, 0, 0, 0, 0, 0, 1, 0 },
{ 2, 0, 0, 7, 4, 5, 0, 0, 0 },
{ 7, 5, 0, 0, 0, 0, 8, 2, 0 },
{ 0, 0, 0, 0, 0, 8, 0, 0, 0 },
{ 0, 0, 0, 0, 2, 0, 6, 7, 0 },
{ 0, 0, 4, 5, 6, 0, 0, 9, 0 }};

void printGrid(){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(grid[i][j] == 0) std::cout << " , ";
            else std::cout << grid[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

bool foundFirstEmpty(int* col, int* row){
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(grid[i][j] == 0){
                *col = i;
                *row = j;
                return true;
            }
        }
    }
    return false;
}

bool fits(int n, int posX, int posY){
    for(int i = 0; i < 9; i++){
        if(grid[i][posY] == n){
            return false;
        }
    }

    for(int i = 0; i < 9; i++){
        if(grid[posX][i] == n){
            return false;
        }
    }

    int quadrantX = posX / 3;
    int quadrantY = posY / 3;

    for(int i = quadrantX * 3; i < (quadrantX*3)+3; i++){
        for(int j = quadrantY * 3; j < (quadrantY*3)+3; j++){
            if(grid[i][j] == n){
                return false;
            }
        }
    }
    return true;
}

bool solveSudoku(){
    int col;
    int row;

    if(!foundFirstEmpty(&col, &row)) return true;

    for(int i = 0; i <= 9; i++){
        if(fits(i, col, row)){
            grid[col][row] = i;
            std::cout << "\n-------------------------\n" << std::endl;
            printGrid();
            if(solveSudoku()){
                return true;
            }
            grid[col][row] = 0;
        }
    }
    return false;
}

int main(){
    std::cout << std::endl;
    printGrid();
    solveSudoku();

    std::cout << "\n-------------------------\n" << std::endl;
    std::cout << "\n-------------------------\n" << std::endl;
    std::cout << "\n------FINAL SOLUTION-----\n" << std::endl;
    std::cout << std::endl;
    printGrid();
    return 0;
}




