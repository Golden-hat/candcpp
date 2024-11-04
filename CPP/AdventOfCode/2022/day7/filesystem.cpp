#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>
#include "LinkedList.cpp"

class directory{
    public:
    long size;
    std::string name;
    directory* parentFolder;

    directory(std::string name, int size, directory* parent){
        this->name = name;
        this->size = size;
        this->parentFolder = parent;
    }

    void updateSize(int n){
        size += n;
    }
};

class filesystem{
    public:
    directory* currentDir;
    LinkedList<directory*> list;

    filesystem(){
        currentDir = new directory("/", 0, nullptr);
        list.add(currentDir);
    }

    void cdIn(std::string dirName){
        directory* dir = new directory(dirName, 0, currentDir);
        this->currentDir = dir;
        list.add(dir);
    }

    void cdOut(){
        std::cout << "Total size of ("<< currentDir->name <<"): "<< currentDir->size << std::endl;
        this->currentDir = this->currentDir->parentFolder;
    }

    void updateSizeUpwards(long updateFactor){
        directory* aux = currentDir;
        while(aux->parentFolder != nullptr){
            aux->parentFolder->updateSize(updateFactor);
            aux = aux->parentFolder;
        }
    }

    void fsParser(){
        std::string text;
        std::ifstream file("input.txt");

        while(std::getline(file, text)){

            std::cout << text << std::endl;
            if(text == "$ cd .."){
                cdOut();
            }
            else if(text.substr(0, 4) == "$ cd"){
                std::string textReturn[3];
                adv_tokenizer(text, " ", textReturn);
                cdIn(textReturn[2]);
            }
            else{
                std::string textReturn[2];
                adv_tokenizer(text, " ", textReturn);
                if(textReturn[0] != "dir" && textReturn[0] != "$"){
                    this->currentDir->updateSize(stoi(textReturn[0]));
                    updateSizeUpwards(stoi(textReturn[0]));
                }      
            }
        }
        file.close();
    }

    void adv_tokenizer(std::string s, const char* del, std::string t[]){
        std::stringstream ss(s);
        std::string word;
        int i = 0;
        while (!ss.eof()) {
            std::getline(ss, word, *del);
            t[i++] = word;
        }
    }

    long calculateTotalSum(){
        long totalSum = 0;

        Node<directory*>* aux = list.head;
        while(aux->next != nullptr){
            if(aux->data->size <= 100000){
                totalSum += aux->data->size;
            }
            aux = aux->next;
        }
        return totalSum;
    }

    long deleteBiggestPossible(long int spaceOccupied){
        long int availableSpace = 70000000 - spaceOccupied; 
        long int best = 70000000; 
        long int store = 0;

        Node<directory*>* aux = list.head;
        while(aux->next != nullptr){
            long int approx = aux->data->size;
            if(availableSpace + approx > 30000000 && availableSpace + approx - 30000000 < best){
                best = availableSpace + approx - 30000000;
                store = approx;
            }
            aux = aux->next;
        }
        return store;
    }
};

int main(){
    filesystem f = filesystem();
    directory* slash = f.currentDir;
    f.fsParser();
    std::cout << "Total size of ("<< slash->name <<"): "<< slash->size << std::endl;
    std::cout << f.calculateTotalSum() << std::endl;
    std::cout << f.deleteBiggestPossible(slash->size);

    return 0;
}