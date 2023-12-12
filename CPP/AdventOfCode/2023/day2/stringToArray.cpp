#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

/*
std::vector<std::string>* stringToArray(std::string line, char a){
    line = "P"+line;
    std::vector<std::string>* retArray = new std::vector<std::string>();
    int last_location = 0;
    for(int i = 0; i < line.length()-1; i++){
        if(line.at(i) == a){
            retArray->push_back(line.substr(last_location + 1, (i-last_location-1)));
            last_location = i; 
        }
    }
    retArray->push_back(line.substr(last_location+1, line.length()-1));
    return retArray;
}
*/

std::vector<int>* stringToArray(std::string line, char a){
    std::vector<int>* spots = new std::vector<int>;
    for(int i = 0; i < line.length(); i++){
        if(i == 0 && line.at(i+1) != ' '){
            spots->push_back(i);
        }
        else if(i == line.length() - 1 && line.at(i-1) != ' '){
            spots->push_back(i);
        }
        else if(line.at(i) == a && (line.at(i-1) != ' ' && line.at(i+1) != ' ')){
            spots->push_back(i);
        }
    }
    return spots;
}

template <class T>
void printArr(std::vector<T>* arr){
    std::cout << "{" << arr->at(0) << ",";
    for(int i = 1; i < arr->size() - 1; i++){
        std::cout << arr->at(i) << ",";
    }
    std::cout << arr->at(arr->size()-1) << "}";
}

int main(){
    std::vector<int>* arr = stringToArray("aaaaaa",  ' ');
    printArr<int>(arr);
    delete(arr);
    return 0;
}

