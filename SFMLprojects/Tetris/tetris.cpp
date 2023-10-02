#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>

const int WIDTH = 400;
const int HEIGHT = 800;

const int TILE_SIZE = 40;

const int horizontal = WIDTH/TILE_SIZE;
const int vertical = HEIGHT/TILE_SIZE;

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
        sf::Color color;
        switch(index){
            case 0:
                color = sf::Color::Blue;
            break;
            case 1:
                color = sf::Color::Red;
            break;
            case 2:
                color = sf::Color::Yellow;
            break;
            case 3:
                color = sf::Color::Green;
            break;
            case 4:
                color = sf::Color::White;
            break;
            case 5:
                color = sf::Color::Cyan;
            break;
            case 6:
                color = sf::Color::Magenta;
        }
        for(int i = 0; i < 4; i++){
            sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            block.setFillColor(color);

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
    bool active;
    sf::Color color;

    tile(int x, int y, sf::Color color, bool active){
        this->x = x;
        this->y = y;
        this->color = color;
        this->active = active;
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
    float prevX = 0;
    float prevY = 0;

    float posX = WIDTH/2 - TILE_SIZE;
    float posY = -200;

    sf::Clock clockDown;
    sf::Clock clockSides;
    sf::Clock clockRotate;

    figures f;
    int currentFigure = f.selectRandomFigure();

    std::vector<tile> physics;
    std::vector<std::vector<tile*>*> wall;

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

    void savePosition(){
        prevX = posX;
        prevY = posY;
    }

    void restorePosition(){
        posX = prevX;
        posY = prevY;
    }

    void bringNewFigure(){
        currentFigure = f.selectRandomFigure();
        posY = -200;
        posX = WIDTH/2 - 2*TILE_SIZE;
    }

    void initializeWall(){
        for(int j = 0; j < vertical; j++){
            std::vector<tile*>* v1 = new std::vector<tile*>;
            wall.push_back(v1);
            for(int i = 0; i < horizontal; i++){
                tile* t = new tile(i*TILE_SIZE, j*TILE_SIZE, sf::Color::Transparent, false);
                wall.at(j)->push_back(t);
            }
        }
    }

    void getPhysics(){
        physics.clear();
        for(int i = 0; i < horizontal; i++){
            bool toggle = false;
            for(int j = 0; j < vertical; j++){
                if (wall.at(j)->at(i)->active && !toggle){
                    tile t(wall.at(j)->at(i)->x, wall.at(j)->at(i)->y - TILE_SIZE, sf::Color::Red, false);
                    physics.push_back(t);
                    toggle = true;
                }
                if(wall.at(j)->at(i)->active == false){
                    toggle = false;
                }
            }
        }
    }

    void checkCollision(){

        for(int i = 0; i < 4; i++){
            if(
                (WIDTH == f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX) ||
                (0 > f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX)       
            )
            {
                posX = prevX;
            }

            for(int j = 0; j < horizontal; j++){
                for(int k = 0; k < vertical; k++){
                    if(
                    (wall.at(k)->at(j)->active == true) &&
                    (wall.at(k)->at(j)->x == f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX) &&
                    (wall.at(k)->at(j)->y == f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY)
                    )
                    {
                        posX = prevX;
                        return;
                    }
                }
            }
        }

        for(int i = 0; i < 4; i++){
            
            if(f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY == HEIGHT){
                restorePosition();
                addFigureToWall();
                return;
            }

            
            for(int j = 0; j < physics.size(); j++){
                if(
                f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX == physics.at(j).x &&
                f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY == physics.at(j).y
                ){
                    addFigureToWall();
                    return;
                }
            }
       }
    }

    void line(){
        for(int j = 0; j < vertical; j++){
            int counter = 0;
            for(int i = 0; i < horizontal; i++){
                if (wall.at(j)->at(i)->active){
                    counter++;
                }
            }
            if(counter == 10){
                for(int z = j; z < vertical - j){
                    
                }
                for(int i = 0; i < horizontal; i++){
                    wall.at(j)->at(i)->y = sf::Color::Red;
                }       
            }
        }
    }

    void moveFigureDown(){
        if(clockDown.getElapsedTime().asSeconds() >= 0.3){
            posY += TILE_SIZE;
            clockDown.restart();
        }
    }

    void moveFigureDownFaster(){
        if(clockDown.getElapsedTime().asSeconds() >= 0.1){
            posY += TILE_SIZE;
            clockDown.restart();
        }
    }

    void valid(){
        for(int i = 0; i < 4; i++){
            for(int j = 0; j < horizontal; j++){
                for(int k = 0; k < vertical; k++){
                    if(
                    (wall.at(k)->at(j)->active == true) &&
                    (wall.at(k)->at(j)->x == f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX) &&
                    (wall.at(k)->at(j)->y == f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY)
                    )
                    {
                        f.rotateFigure(currentFigure);
                        f.rotateFigure(currentFigure);
                        f.rotateFigure(currentFigure);
                        return;
                    }
                }
            }
        }       
    }

    void moveCurrentFigure(){

        if(clockSides.getElapsedTime().asSeconds() >= 0.1){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            {
                posX -= TILE_SIZE;
                clockSides.restart();
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            {
                posX += TILE_SIZE;
                clockSides.restart();
            }
        }

        if(clockRotate.getElapsedTime().asSeconds() >= 0.2){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            {
                f.rotateFigure(currentFigure);
                valid();
                clockRotate.restart();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            moveFigureDownFaster();
        }
    }
    
    void addFigureToWall(){
        sf::Color color;
        switch (currentFigure)
        {
            case 0:
                color = sf::Color::Blue;
            break;
            case 1:
                color = sf::Color::Red;
            break;
            case 2:
                color = sf::Color::Yellow;
            break;
            case 3:
                color = sf::Color::Green;
            break;
            case 4:
                color = sf::Color::White;
            break;
            case 5:
                color = sf::Color::Cyan;
            break;
            case 6:
                color = sf::Color::Magenta;
        }

        for(int i = 0; i < 4; i++){
            int arrayX = f.figures.at(currentFigure).at(i).at(0) + posX/TILE_SIZE;
            int arrayY = f.figures.at(currentFigure).at(i).at(1) + posY/TILE_SIZE;

            wall.at(arrayY)->at(arrayX)->active = true;
            wall.at(arrayY)->at(arrayX)->color = color;
        }

        bringNewFigure();
    }

    void printWall(){
        for(int i = 0; i < horizontal; i++){
            for(int j = 0; j < vertical; j++){
                if(wall.at(j)->at(i)->active == true) wall.at(j)->at(i)->drawTile();
            }
        }
    }

    void printPhysics(){
        for(int i = 0; i < physics.size(); i++){
            physics.at(i).drawTile();
        }
    }

    board(){
        f.rotateFigure(currentFigure);
        initializeWall();
        while(window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }
            getPhysics();

            window.clear();
            savePosition();
            f.drawFigure(currentFigure, posX, posY);

            moveCurrentFigure();
            checkCollision(); 
            moveFigureDown();
            line();

            checkCollision();

            printWall();
            renderGrid();
            
            window.display();
        }
    }
};

int main(){
    window.setFramerateLimit(120);
    board b;
    return 0;
}
