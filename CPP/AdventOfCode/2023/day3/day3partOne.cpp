#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

std::vector<std::vector<char>>* convertToArray (std::string fileName){
    std::vector<std::vector<char>>* array = new std::vector<std::vector<char>>;

    std::ifstream file;
    file.open(fileName);
    std::string line;
    
    int j = 0;
    while(getline(file, line)){
        std::vector<char> newLine;
        array->push_back(newLine);
        for(int i = 0; i < line.length(); i++){
            array->at(j).push_back(line.at(i)); 
        }
    }
    file.close();

    return array;
}

int main(){
    std::vector<std::vector<char>>* array = convertToArray("input.txt");
    return 0;
}

