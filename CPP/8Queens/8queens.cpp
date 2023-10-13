#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>
#include <queue>
#include <random>
#include <unistd.h>

int grid[8][8] = {0};
int numQueens = 0;

void printGrid(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++){
            if(grid[i][j] == 0) std::cout << " , ";
            else std::cout << grid[i][j] << ", ";
        }
        std::cout << std::endl;
    }
}

bool fits(int posX, int posY){
    for(int i = 0; i < 8; i++){
        if(grid[i][posY] == 1){
            return false;
        }
    }

    for(int i = 0; i < 8; i++){
        if(grid[posX][i] == 1){
            return false;
        }
    }

    for(int i = 0; i < 8; i++){
        if(posX+i > 8 || posY-i < 0) break;
        if(grid[posX+i][posY-i] == 1){
            return false;
        }
    }

    for(int i = 0; i < 8; i++){
        if(posX-i < 0 || posY+i >8) break;
        if(grid[posX-i][posY+i] == 1){
            return false;
        }
    }

    for(int i = 0; i < 8; i++){
        if(posX-i < 0 || posY-i < 0) break;
        if(grid[posX-i][posY-i] == 1){
            return false;
        }
    }

    for(int i = 0; i < 8; i++){
        if(posX+i > 8 || posY+i >8) break;
        if(grid[posX+i][posY+i] == 1){
            return false;
        }
    }

    return true;
}

void randSetup(){
    std::vector<std::vector<int>> list;

    for(int k = 0; k < 2; k++){
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 7);

        int i = dist(rd);
        int j = dist(rd);

        if(fits(i, j)){grid[i][j] = 1; numQueens++;}
        else{k--;}
    }
}

bool generateSolution(){
    if(numQueens == 8){return true;}

    for(int i = 0; i < 64; i++){
        if(fits(i/8, i%8)){
            grid[i/8][i%8] = 1;
            numQueens++;
            
            printGrid();
            std::cout << std::endl;

            if(generateSolution()){return true;}
            grid[i/8][i%8] = 0;
            numQueens--;
        }
    }

    return false;
}

int main(){
    randSetup();
    generateSolution();
    
    if(numQueens != 8){
        std::cout << "The initial state doesn't allow for a solution with 8 queens.\nThe maximum nº of possible queens will appear in the last iteration right above." << std::endl;
    }
    else{
        std::cout << "\n------------------------\n" << std::endl;
        std::cout << "\n------------------------\n" << std::endl;
        std::cout << "\n-----FINAL SOLUTION-----\n" << std::endl;
        std::cout << std::endl;
        printGrid();
    }
    return 0;
}