#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

std::vector<std::string>* stringToArray(std::string line, char a){
    std::vector<std::string>* retArray = new std::vector<std::string>();
    int last_location = 0;
    retArray->push_back(line.substr(last_location,1));
    for(int i = 0; i < line.length()-1; i++){
        if(line.at(i) == a){
            retArray->push_back(line.substr(last_location+1, (i-last_location-1)));
            last_location = i; 
        }
    }
    retArray->push_back(line.substr(last_location+1, line.length()-1));
    for(int i = 0; i < retArray->size(); i++){
        std::cout << retArray->at(i)<< ",";
    }
    return retArray;
}

bool isValid(int red, int green, int blue, std::string line){
    std::vector<std::string>* array = stringToArray(line, ' ');
    for(int i = 2; i < array->size(); i = i+2){
        int x = std::stoi(array->at(i));
        std::cout << x <<", '"<< array->at(i+1) <<"' ?"<< std::endl;
        if(array->at(i+1) == "r" && x > red ){ return false; }
        if(array->at(i+1) == "g" && x > green ){ return false; }
        if(array->at(i+1) == "b" && x > blue ){ return false; }
    }
    return true;
}

int main(int argc, char *argv[]){
    if(argc != 4){
        std::cout << "Please, provide the needed arguments: (red) (green) (blue)" << std::endl;
        return 0;
    }
    int IDsum = 0;

    std::ifstream file;
    file.open("input.txt");
    std::string line;

    int nGame = 1;
    while(getline(file, line)){
        bool valid = isValid(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), line);
        if(valid) IDsum += nGame;
        std::cout << line << ", " << valid << "\n";
        nGame++;
    }
    file.close();

    std::cout << "The sum of ID's of all valid games is: " << IDsum << std::endl;
    
    return 0;
}
