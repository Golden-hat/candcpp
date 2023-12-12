#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <stdlib.h>

bool contains(std::string number, std::string line){
    if(line.length() < number.length()) return false;
    // std::cout << number << ", " << line << std::endl;
    if(line.find(number) != std::string::npos){ return true; }
    return false;
}

bool isContained(std::string t, char a){
    for(int i = 0; i < t.length(); i++){
        if(t.at(i) == a){return true;}
    }
    return false;
}

std::string nameToNumber(std::string number){
    if(number == "one")
        return "1";
    if(number == "two")
        return "2";
    if(number == "three")
        return "3";
    if(number == "four")
        return "4";
    if(number == "five")
        return "5";
    if(number == "six")
        return "6";
    if(number == "seven")
        return "7";
    if(number == "eight")
        return "8";
    if(number == "nine")
        return "9";
    return "";
}

int calibrationNumber(std::string text){
    std::string firstNum = "";
    std::string lastNum = "";
    
    std::string numbers[9] = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    
    bool notFound = true;

    for(int i = 0; i < text.length() && notFound; i++){
        if(isContained("1234567890", text.at(i))){
            firstNum = text.at(i);
            notFound = false;
            break;
        }
        else{
            for(int j = 0; j < 9; j++){
                if(contains(numbers[j], text.substr(0, i+1))){
                    firstNum = nameToNumber(numbers[j]);
                    notFound = false;
                    break;
                }
            }
        }
    }

    notFound = true;

    for(int i = text.length()-1; i >= 0 && notFound; i--){
        if(isContained("1234567890", text.at(i))){
                lastNum = text.at(i);
                notFound = false;
                break;
        }
        else{
            for(int j = 0; j < 9 && notFound; j++){
                if(contains(numbers[j], text.substr(i, text.length()-1))){
                    lastNum = nameToNumber(numbers[j]);
                    notFound = false;
                    break;
                }
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
        int num = calibrationNumber(line);
        std::cout << line << ", " << num << "\n";
        total += num;
    }
    file.close();

    std::cout << "The sum of all calibration numbers is: " << total << std::endl;

    return 0;
}
