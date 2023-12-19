#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>
#include <map>

std::map<std::string, int> nCards;

bool isEmptyString(std::string line, char a){
    if(line == "") return true;
    for(int i = 0; i < line.length(); i++){
        if(line.at(i) != a){return false;}
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
        if(!isEmptyString(line.substr(spots.at(i)+1, (spots.at(i+1) - (spots.at(i)+1))), ' '))
            arr->push_back(line.substr(spots.at(i)+1, (spots.at(i+1) - (spots.at(i)+1))));
    }
    return arr;
}

void initializeDeck(std::vector<std::string>* array){
    nCards[array->at(0)+" "+array->at(1)] = 1;
}

void addCardToDeck(std::vector<std::string>* array){
    for(int k = 0; k < nCards[array->at(0)+" "+array->at(1)] += count; k++){
        int count = 0;
        for(int i = 2; i <= 11; i++){
            for(int j = 13; j < array->size(); j++){
                if(array->at(i) == array->at(j)) count++;
            }
        }
        nCards[array->at(0)+" "+array->at(1)] += count;
    }
}

int getNumCards(){
    
}

int main(){
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    int sum = 0;

    while(getline(file, line)){
        std::vector<std::string>* array = stringToArray(line, ' '); 
        initializeDeck(array);
        delete(array);
    }
    file.close();
    file.open("input.txt");
    while(getline(file, line)){
        std::vector<std::string>* array = stringToArray(line, ' ');
        addCardToDeck(array);
        delete(array);
    }

    sum += getNumCards();
    std::cout << "The total amount of cards is: " << sum << "." << std::endl;
    file.close();   
    return 0;
}
