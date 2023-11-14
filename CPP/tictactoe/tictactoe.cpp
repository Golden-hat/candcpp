#include <iostream>
#include <random>

class board
{
public:
    char grid[3][3] = {'-'};
    char turn = '0';

    void initializeGrid()
    {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++)
            {
                grid[i][j] = '-';
            }
        }
    }

    board()
    {
        initializeGrid();
    }

    void printGrid()
    {
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++)
            {
                if (grid[i][j] == 'X')
                    std::cout << " X, ";
                else if (grid[i][j] = '-')
                    std::cout << "-,";
                else
                    std::cout << grid[i][j] << "0, ";
            }
            std::cout << std::endl;
        }
    }

    void generateStates()
    {
        if (turn == '0')
        {
            for (int i = 0; i < 3; i++)
            {
            }
        }
    }
};

int main()
{
    board b;
    b.printGrid();
}