#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>
#include <queue>
#include <random>
#include <unistd.h>

//ADVANTAGES AND DISADVANTAGES OF THE DAO PATTERN

int grid[9][9] = 
{0};

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

void randSetup(){
    std::vector<std::vector<int>> list;

    for(int k = 0; k < 8; k++){
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 8);
        std::uniform_int_distribution<int> num(0, 9);

        int i = dist(rd);
        int j = dist(rd);
        int number = num(rd);

        if(k == 0){grid[0][0] = number;}
        
        if(fits(number, i, j)){grid[i][j] = number;}
        else{k--;}
    }
}

void eraseSomeTiles(int n){
    for(int k = 0; k < n; k++){
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 8);

        int i = dist(rd);
        int j = dist(rd);

        if(grid[i][j] != 0){grid[i][j] = 0;}
        else{k--;}
    }
}

bool solveSudoku(){
    int col;
    int row;

    if(!foundFirstEmpty(&col, &row)) return true;

    for(int i = 0; i <= 9; i++){
        if(fits(i, col, row)){
            grid[col][row] = i;
            if(solveSudoku()){
                return true;
            }
            grid[col][row] = 0;
        }
    }
    return false;
}

void randSudoku(){
    randSetup();
    solveSudoku();
    eraseSomeTiles(45);
}

int main(){
    std::cout << std::endl;
    randSudoku();
    printGrid();

    std::cout << "\n------------------------\n" << std::endl;
    std::cout << "\n------------------------\n" << std::endl;
    std::cout << "\n-----FINAL SOLUTION-----\n" << std::endl;
    std::cout << std::endl;

    solveSudoku();
    printGrid();
    return 0;
}




