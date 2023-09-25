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

class tile{
    public:
    int x;
    int y;
    sf::Color color;
    bool enablePhysics;

    tile(int x, int y, sf::Color color, bool enablePhysics){
        this->x = x;
        this->y = y;
        this->color = color;
        this->enablePhysics = enablePhysics;
    }

    void drawTile(){
        sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
        block.setPosition(x, y);
        block.setFillColor(color);

        window.draw(block);
    }
};

class board{
    public:
    float prevX;
    float prevY;

    float posX = WIDTH/2 - 2*TILE_SIZE;
    float posY = -160;
    sf::Clock clockDown;
    sf::Clock clockSides;
    sf::Clock clockRotate;

    figures f;
    int currentFigure = f.selectRandomFigure();

    std::vector<tile*> wall;

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

    void bringNewFigure(){
        prevY = posY;

        currentFigure = f.selectRandomFigure();
        posY = -160;
    }

    void moveFigureDown(){
        prevY = posY;

        if(clockDown.getElapsedTime().asSeconds() >= 0.3){
            posY += TILE_SIZE;
            clockDown.restart();
        }
    }

    void moveFigureDownFaster(){
        prevY = posY;

        if(clockDown.getElapsedTime().asSeconds() >= 0.075){
            posY += TILE_SIZE;
            clockDown.restart();
        }
    }

    void moveCurrentFigure(){
        bool checkLeft = true;
        bool checkRight = true;

        prevX = posX;
        prevY = posY;

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

        if(clockSides.getElapsedTime().asSeconds() >= 0.1){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && checkLeft)
            {
                posX -= TILE_SIZE;
                clockSides.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && checkRight)
            {
                posX += TILE_SIZE;
                clockSides.restart();
            }
        }

        if(clockRotate.getElapsedTime().asSeconds() >= 0.2){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                f.rotateFigure(currentFigure);
                clockRotate.restart();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            moveFigureDownFaster();
        }
    }

    void checkCollision(){
        for(int i = 0; i < 4; i++){
            if(f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY >= HEIGHT - TILE_SIZE){
                addFigureToWall();
                break;
            }
            for(int j = 0; j < wall.size(); j++){
                if(wall.at(j)->enablePhysics == true && 
                f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX == wall.at(j)->x &&
                f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY == wall.at(j)->y ){
                    posX = prevX;
                    posY = prevY;
                    addFigureToWall();
                    break;
                }
            }   
        }

    }

    void addFigureToWall(){
        for(int i = 0; i < 4; i++){
            int X = f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX;
            int Y = f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY;

            tile* t = new tile(X, Y, sf::Color::White, false);
            wall.push_back(t);
        }

        for(int i = 0; i < wall.size(); i++){
            int ex = wall.at(i)->x;
            int ey = wall.at(i)->y - TILE_SIZE;
            for(int j = 0; j < wall.size(); j++){
                if(ey == wall.at(j)->y + TILE_SIZE && ex == wall.at(j)->x){
                    wall.at(i)->enablePhysics = false;
                    wall.at(i)->color = sf::Color::Red;
                    break;
                }
                else{wall.at(i)->enablePhysics = true;}
            }
        }

        bringNewFigure();
    }

    void printWall(){
        for(int i = 0; i < wall.size(); i++){
            wall.at(i)->drawTile();
        }
    }

    board(){
        f.rotateFigure(currentFigure);
        while(window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }

            window.clear();

            f.drawFigure(currentFigure, posX, posY);
            printWall();

            moveCurrentFigure();
            moveFigureDown();

            checkCollision();

            renderGrid();
            
            window.display();
        }
    }
};

int main(){
    window.setFramerateLimit(60);
    board b;
    return 0;
}
