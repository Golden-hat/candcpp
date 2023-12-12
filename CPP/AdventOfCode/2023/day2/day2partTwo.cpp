#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>

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

int getMinimum(){
    std::vector<std::string>* array = stringToArray(line, ' ');
    int redMin = 10000;
    int greenMin = 10000;
    int blueMin = 10000;
    for(int i = 2; i < array->size(); i = i+2){
        int x = std::stoi(array->at(i));
        // std::cout << x <<", '"<< array->at(i+1) <<"' ?"<< std::endl;
        if(array->at(i+1) == "r" && x < redMin ){ redMin = x; }
        if(array->at(i+1) == "g" && x < greenMin ){ greenMin = x; }
        if(array->at(i+1) == "b" && x < blueMin ){ blueMin = x; }
    }
    delete(array);
    return redMin * greenMin * blueMin;
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
        int valid = isValid(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]), line);
        IDsum += valid;
        std::cout << line << ", " << valid << "\n";
        nGame++;
    }
    file.close();

    std::cout << "The sum of ID's of all valid games is: " << IDsum << std::endl;
    
    return 0;
}
