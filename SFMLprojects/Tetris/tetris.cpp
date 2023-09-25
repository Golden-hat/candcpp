#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>

const int WIDTH = 400;
const int HEIGHT = 800;

const int TILE_SIZE = 40;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PONG");

class figures{
    public:
    std::vector<std::vector<std::vector<int>>> figures = 
    {
        {
            { 1, 0 }, { 2, 0 }, { 3, 0 }, { 4, 0 } // Recta
        },
        {
            { 1, 1 }, { 1, 2 }, { 1, 3}, { 0, 3 } // L invertida
        },
        {
            { 2, 3 }, { 1, 2}, { 1, 1 }, { 1, 3 } // L 
        },
        {
            { 0, 0 }, { 1, 0 }, { 0, 1}, { 1, 1 } // Cuadrado
        },
        {
            { 1, 0 }, { 1, 1 }, { 2, 1}, { 0, 1 } // T
        },
        {
            { 1, 0 }, { 1, 1 }, { 0, 1}, { 0, 2 } // Z
        },
        {
            { 0, 0 }, { 1, 1 }, { 0, 1 }, { 1, 2 } // Z invertida
        }
    };

    void drawFigure(int index, int posX, int posY){
        for(int i = 0; i < 4; i++){
            sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            block.setFillColor(sf::Color::White);

            block.setPosition(figures.at(index).at(i).at(0) * TILE_SIZE + posX, 
                              figures.at(index).at(i).at(1) * TILE_SIZE + posY);
            window.draw(block);
        }
    }

    void rotateFigure(int index){
        if(index == 3){return;}
        std::vector<int> centerOfRotation = figures.at(index).at(1);
        for(int i = 0; i < 4; i++){
            int xDiff = figures.at(index).at(i).at(1) - centerOfRotation.at(1);
            int yDiff = figures.at(index).at(i).at(0) - centerOfRotation.at(0);
            figures.at(index).at(i).at(0) = centerOfRotation.at(0) - xDiff;
            figures.at(index).at(i).at(1) = centerOfRotation.at(0) + yDiff;
        }
    }

    int selectRandomFigure(){
        srand(time(0));
        return rand()%7;
    }
};

class board{
    public:
    int posX = 120;
    int posY = 240;

    figures f;

    int currentFigure = f.selectRandomFigure();

    void renderGrid(){
        for(int i = 0; i < WIDTH; i += TILE_SIZE){
            for(int j = 0; j < HEIGHT; j += TILE_SIZE){
                sf::RectangleShape tile = sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setOutlineColor(sf::Color(75,75,75));
                tile.setOutlineThickness(1);

                tile.setFillColor(sf::Color::Transparent);
                tile.setPosition(i, j);
                
                window.draw(tile);
            }
        }
    }

    void moveCurrentFigure(){
        bool checkLeft = true;
        bool checkRight = true;

        posY += 10;

        for(int i = 0; i < 4; i++){
            if(f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX <= 0){
                checkLeft = false;
                break;
            }
            else if(f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX >= WIDTH - TILE_SIZE){
                checkRight = false;
                break;
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && checkLeft)
        {
            posX -= TILE_SIZE;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && checkRight)
        {
            posX += TILE_SIZE;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            f.rotateFigure(currentFigure);
        }
    }

    board(){
        f.rotateFigure(currentFigure);
        while(window.isOpen())
        {
            window.setFramerateLimit(15);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }

            window.clear();

            f.drawFigure(currentFigure, posX, posY);
            moveCurrentFigure();
            renderGrid();
            
            window.display();
        }
    }
};

int main(){
    board b;
    return 0;
}
