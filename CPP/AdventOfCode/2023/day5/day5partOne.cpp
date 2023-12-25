#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include "Tree.cpp"

bool isContained(std::string t, char a){
    for(int i = 0; i < t.length(); i++){
        if(t.at(i) == a){return true;}
    }
    return false;
}

template <class T>
void printArr(std::vector<T>* arr){
    if(arr->size() == 0){ std::cout << "{}" << std::endl; return;}
    if(arr->size() == 1){ std::cout << "{" << arr->at(0) << "}" << std::endl; return;}
    std::cout << "{" << arr->at(0) << ",";
    for(int i = 1; i < arr->size() - 1; i++){
        std::cout << arr->at(i) << ",";
    }
    std::cout << arr->at(arr->size()-1) << "}";
}

bool isEmptyString(std::string line){
    if(line == "") return true;
    for(int i = 0; i < line.length(); i++){
        if(line.at(i) != ' '){return false;}
    }
    return true;
}

std::vector<std::string>* stringToArray(std::string line, char a){
    line = a+line+a;
    std::vector<std::string>* arr = new std::vector<std::string>;
    std::vector<int> spots;
    for(int i = 0; i < line.length(); i++){
        if(line.at(i) == a){
            spots.push_back(i);
        }
    }
    for(int i = 0; i < spots.size()-1; i++){
        if(!isEmptyString(line.substr(spots.at(i)+1, (spots.at(i+1) - (spots.at(i)+1)))))
            arr->push_back(line.substr(spots.at(i)+1, (spots.at(i+1) - (spots.at(i)+1))));
    }
    return arr;
}

std::vector<int>* saveSeeds(std::string line){
    std::vector<int>* seeds = new std::vector<int>;
    std::vector<std::string>* arr = stringToArray(line, ' ');
    printArr<std::string>(arr);
    std::cout << std::endl;
    for(int i = 1; i < arr->size(); i++){
        seeds->push_back(std::stoi(arr->at(i)));
    }
    return seeds;
}

int operation(int number, std::vector<std::string>* arr){
    int source = std::stoi(arr->at(1));
    int destination = std::stoi(arr->at(0));
    int range = std::stoi(arr->at(2));

    if(number >= source && number <= source + range){
        return number-source + destination;
    }
    return number;
}

int whichLevel(std::string line){
    if(line == "seed-to-soil map:") return 0;
    if(line == "soil-to-fertilizer map:") return 1;
    if(line == "fertilizer-to-water map:") return 2;
    if(line == "water-to-light map:") return 3;
    if(line == "light-to-temperature map:") return 4;
    if(line == "temperature-to-humidity map:") return 5;
    if(line == "humidity-to-location map:") return 6;
    return 0;
}

int main(){
    std::ifstream file;
    file.open("input.txt");

    std::string line;
    std::vector<int>* seeds;
    std::vector<std::string> input;

    while(getline(file, line)){
        input.push_back(line);
        std::vector<std::string>* array = stringToArray(line, ' ');
        if(array->size() != 0 && array->at(0) == "seeds:"){
            seeds = saveSeeds(line);
        }
    }
    file.close();
     
    std::cout << std::endl;
    return 0;
} 
