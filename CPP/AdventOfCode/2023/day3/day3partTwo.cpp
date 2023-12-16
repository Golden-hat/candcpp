#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <fstream>

class symbol{
    public:
        std::vector<int> list;
        int symbolX;
        int symbolY;
    
        symbol(int symbolX, int symbolY){
            this->symbolX = symbolX;
            this->symbolY = symbolY;
        }
        
        void addNumberToList(int number){
            list.push_back(number);
        }

        int returnMultList(){
            int sum = 1;
            for(int i = 0; i < list.size(); i++){
                sum *= list.at(i);
            }
            return sum;
        }

        bool isExactlyLenTwo(){
            return 2 == list.size();
        }
};

class symbolList{
    public:
        std::vector<symbol> list;
        
        symbol* findSymbol(int symbolX, int symbolY){
            for(int i = 0; i < list.size(); i++){
                if(list.at(i).symbolX == symbolX && list.at(i).symbolY == symbolY){
                    return &list.at(i);
                }
            }
            return nullptr;
        }
    
        void addToList(int symbolX, int symbolY, int value){
            symbol* s = findSymbol(symbolX, symbolY);
            if(s == nullptr){
                symbol symb(symbolX, symbolY);
                list.push_back(symb);
            }
            else{
                s->addNumberToList(value);
            }
        }

        int sumOfEqTwo(){
            int sum = 0;
            for(int i = 0; i < list.size(); i++){
                if(list.at(i).isExactlyLenTwo()){
                    sum += list.at(i).returnMultList();
                }
            }
            return sum;
        }
};

symbolList symb;

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
        j++;
    }
    file.close();

    return array;
}

void checkNeighbours(std::vector<int>* y, std::vector<int>* x, std::vector<std::vector<char>>* array, std::string number){
    for(int i = 0; i < x->size(); i++){
        for(int col = -1; col <= 1; col++){
            for(int row = -1; row <= 1; row++){
                if((y->at(i)+col != -1 && x->at(i)+row != -1) &&
                   (y->at(i)+col != array->size() && x->at(i)+row != array->at(i).size())){
                    if(!isContained("1234567890.", array->at(y->at(i)+col).at(x->at(i)+row))){
                       symb.addToList(x->at(i)+row, y->at(i)+col, std::stoi(number)); 
                    }
                }
            }
        }
    }
}

void sumNumbers(std::vector<std::vector<char>>* array){
    std::string numberString = "0123456789"; 
    int j = 0;
    std::vector<int>* y = new std::vector<int>;
    std::vector<int>* x = new std::vector<int>;

    for(int j = 0; j < array->size(); j++){
        std::string numString = "";
        for(int i = 0; i < array->at(j).size(); i++){
            if(isContained(numberString, array->at(j).at(i))){
                numString += array->at(j).at(i);
                y->push_back(j);
                x->push_back(i);
            }
            else if(numString != ""){
                checkNeighbours(y, x, array, numString);
                std::cout << numString << ", " << y->at(0) << std::endl;
                numString = "";
                y->clear();
                x->clear();
            }
        }
        /* Cuando se llega al eol, hay que "limpiar" */
        checkNeighbours(y, x, array, numString);
        numString = "";
        y->clear();
        x->clear();
    }
}

int main(){
    std::vector<std::vector<char>>* array = convertToArray("input.txt");
    sumNumbers(array);
    std::cout << symb.sumOfEqTwo() << std::endl;
    return 0;
}
