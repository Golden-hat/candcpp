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
    
    printArr<int>(&spots);

    return arr;
}

int main(){
    std::vector<std::string>* arr = stringToArray();
    printArr<std::string>(arr);
    delete(arr);
    return 0;
}

