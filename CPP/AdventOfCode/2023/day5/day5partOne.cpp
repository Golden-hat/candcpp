#include <iostream>
#include <stdio.h>
#include <string>
#include <fstream>
#include <vector>
#include <cmath>

int main(){
    std::ifstream file;
    file.open("input.txt");
    std::string line;
    int sum = 0;

    while(getline(file, line)){
        std::vector<std::string>* array = stringToArray(line, ' '); 
        sum += sumWinNum(array);
    }
    std::cout << "The total amount of points is: " << sum << "." << std::endl;
    file.close();
    return 0;
}
