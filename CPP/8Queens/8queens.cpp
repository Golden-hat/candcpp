#include <iostream>
#include <time.h>
#include <chrono>
#include <thread>
#include <queue>
#include <random>
#include <unistd.h>

int grid[8][8] = {0};
int numQueens = 0;
std::vector<std::tuple<int, int>> queenList;

void printGrid()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      if (grid[i][j] == 0)
        std::cout << " , ";
      else
        std::cout << grid[i][j] << ", ";
    }
    std::cout << std::endl;
  }
}

bool fits(int posX, int posY)
{
  for (int i = 0; i < numQueens; i++)
  {
    int queenX = std::get<0>(queenList.at(i));
    int queenY = std::get<1>(queenList.at(i));

    if (abs(queenX - posX) == abs(queenY - posY) || queenX == posX || queenY == posY)
    {
      return false;
    }
  }
  return true;
}

void randSetup()
{
  std::vector<std::vector<int>> list;

  for (int k = 0; k < 2; k++)
  {
    std::random_device rd;
    std::uniform_int_distribution<int> dist(0, 7);

    int i = dist(rd);
    int j = dist(rd);

    if (fits(i, j))
    {
      grid[i][j] = 1;
      numQueens++;
      queenList.push_back(std::make_tuple(i, j));
    }
    else
    {
      k--;
    }
  }
}

bool generateSolution()
{
  if (numQueens == 8)
  {
    return true;
  }

  for (int i = 0; i < 64; i++)
  {
    if (fits(i / 8, i % 8))
    {
      grid[i / 8][i % 8] = 1;
      numQueens++;
      queenList.push_back(std::make_tuple(i / 8, i % 8));

      printGrid();
      std::cout << std::endl;

      if (generateSolution())
      {
        return true;
      }
      grid[i / 8][i % 8] = 0;
      numQueens--;
      queenList.pop_back();
    }
  }
  return false;
}

int main(int argc, char *argv[])
{
  randSetup();
  generateSolution();

  if (numQueens != 8)
  {
    std::cout << "The initial state doesn't allow for a solution with 8 queens.\nLast iteration yielded the result right above." << std::endl;
  }
  else
  {
    std::cout << "\n------------------------\n";
    std::cout << "\n------------------------\n";
    std::cout << "\n-----FINAL SOLUTION-----\n";
    printGrid();
    std::cout << std::endl;
  }
  return 0;
}