#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>

bool isContained(std::string t, char a){
    for(int i = 0; i < t.length(); i++){
        if(t.at(i) == a){return true;}
    }
    return false;
}

int calibrationNumber(std::string text){
    std::string firstNum = "";
    std::string lastNum = "";
    for(int i = 0; i < text.length(); i++){
        if(isContained("1234567890", text.at(i))){
            if(firstNum == ""){
                firstNum = text.at(i);
                lastNum = text.at(i);
            }
            else{
                lastNum = text.at(i);
            }
        }
    }
    std::string Result = firstNum + lastNum;
    return std::stoi(Result, nullptr, 10);
}


int main(){
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    int total = 0;

    while(getline(file, line)){
        std::cout << line;
        int num = calibrationNumber(line);
        std::cout << line << ", " << num << "\n";
        total += num;
    }
    file.close();

    std::cout << "The sum of all calibration numbers is: " << total << std::endl;

    return 0;
}
