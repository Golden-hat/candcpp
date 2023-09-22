#include <iostream>
#include <stdio.h>

const int LINE = 0;
const int CROSS = 1;
const int L = 2;
const int COLUMN = 3;
const int SQUARE = 4;

class rock{
    private:
    char rockType[4][4];

    public:
    rock(int rockType){
        switch(rockType){
            case LINE:
                this->rockType = {{'#','#','#','#'},{'#','#','#','#'},{'#','#','#','#'},{'#','#','#','#'}};
                break;
            case CROSS:
                this->rockType = ".#..###..#......";
                break;
            case L:
                this->rockType = "..#...#.###.....";
                break;
            case COLUMN:
                this->rockType = "#...#...#...#...";
                break;
            case SQUARE:
                this->rockType = "##..##..........";
                break;
        }
    }
};