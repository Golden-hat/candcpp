#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>
#include <queue>
#include <random>

const int WIDTH = 200;
const int HEIGHT = 520;

const int TILE_SIZE = 20;

const int horizontal = WIDTH/TILE_SIZE;
const int vertical = HEIGHT/TILE_SIZE;

sf::RenderWindow window(sf::VideoMode(WIDTH+275, HEIGHT+200), "Tetris");

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

    void drawFigure(int index, int posX, int posY, int size){
        sf::Color color;
        switch (index)
        {
            case 0:
                color = sf::Color(154, 214, 170);
            break;
            case 1:
                color = sf::Color(157, 154, 214);
            break;
            case 2:
                color = sf::Color(126, 247, 99);
            break;
            case 3:
                color = sf::Color(255, 163, 77);
            break;
            case 4:
                color = sf::Color(101, 101, 247);
            break;
            case 5:
                color = sf::Color(61, 226, 245);
            break;
            case 6:
                color = sf::Color(250, 117, 206);
        }
        for(int i = 0; i < 4; i++){
            sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(size, size));
            block.setFillColor(color);
            block.setOutlineColor(sf::Color(75,75,75));
            block.setOutlineThickness(1);

            block.setPosition(figures.at(index).at(i).at(0) * size + posX, 
                              figures.at(index).at(i).at(1) * size + posY);
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
        std::random_device rd;
        std::uniform_int_distribution<int> dist (0, 6);
        return dist(rd);
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

class menu{
    public:
    void overlay(int score){
        sf::Text text;

        sf::Font font;
        if (!font.loadFromFile("LiberationMono-Regular.ttf"))
        {
            // error...
        }
        text.setFont(font);
        text.setString("Score: "+std::to_string(score));
        text.setCharacterSize(20);
        text.setFillColor(sf::Color::White);

        sf::FloatRect textRect1 = text.getLocalBounds();
        text.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
        text.setPosition(sf::Vector2f(WIDTH/2.0f - 55, HEIGHT/2.0f + 300));

        window.draw(text);

        sf::Text next;

        next.setFont(font);
        next.setString("NEXT:");
        next.setCharacterSize(20);
        next.setFillColor(sf::Color::White);

        sf::FloatRect textRect2 = text.getLocalBounds();
        next.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
        next.setPosition(sf::Vector2f(WIDTH + 107, 30));

        window.draw(next);
    }

    void rectangles(){
        sf::RectangleShape leftBig = sf::RectangleShape(sf::Vector2f(125, HEIGHT));
        leftBig.setPosition(WIDTH + 25, 0);
        leftBig.setOutlineColor(sf::Color::White);
        leftBig.setOutlineThickness(2.0f);
        leftBig.setFillColor(sf::Color::Transparent);
        window.draw(leftBig);

        sf::RectangleShape leftBottom = sf::RectangleShape(sf::Vector2f(125, HEIGHT-400));
        leftBottom.setPosition(WIDTH + 25, 400);
        leftBottom.setOutlineColor(sf::Color::White);
        leftBottom.setOutlineThickness(2.0f);
        leftBottom.setFillColor(sf::Color::Transparent);
        window.draw(leftBottom);
    }

    void drawQueue(std::queue<int> queue, int hold){
        figures f;
        for(int i = 4; i > 0; i--){
            sf::RectangleShape leftBottom = sf::RectangleShape(sf::Vector2f(60, 60));
            leftBottom.setPosition(WIDTH + 57, 380 - 80*i);
            leftBottom.setOutlineColor(sf::Color::White);
            leftBottom.setOutlineThickness(1.0f);
            leftBottom.setFillColor(sf::Color::Transparent);
            window.draw(leftBottom);

            int figure = queue.front();
            queue.pop();

            if(figure == 0)
                f.drawFigure(figure, WIDTH + 57, 380 - 80*i + 25, 10);
            else if(figure == 1)
                f.drawFigure(figure, WIDTH + 57 + 20, 380 - 80*i + 5, 10);
            else if(figure == 2)
                f.drawFigure(figure, WIDTH + 57 + 9, 380 - 80*i + 3, 10);
            else if(figure == 3)
                f.drawFigure(figure, WIDTH + 57 + 20, 380 - 80*i + 20, 10);
            else if(figure == 4)
                f.drawFigure(figure, WIDTH + 57 + 15, 380 - 80*i + 15, 10);
            else if(figure == 5)
                f.drawFigure(figure, WIDTH + 57 + 20, 380 - 80*i + 15, 10);
            else if(figure == 6)
                f.drawFigure(figure, WIDTH + 57 + 20, 380 - 80*i + 15, 10);
            queue.push(figure);
        }

            sf::RectangleShape leftBottom = sf::RectangleShape(sf::Vector2f(60, 60));
            leftBottom.setPosition(WIDTH + 57, 430);
            leftBottom.setOutlineColor(sf::Color::White);
            leftBottom.setOutlineThickness(1.0f);
            leftBottom.setFillColor(sf::Color::Transparent);

            if(hold == 0)
                f.drawFigure(hold, WIDTH + 57, 430 + 25, 10);
            else if(hold == 1)
                f.drawFigure(hold, WIDTH + 57 + 20, 430 + 5, 10);
            else if(hold == 2)
                f.drawFigure(hold, WIDTH + 57 + 9, 430 + 3, 10);
            else if(hold == 3)
                f.drawFigure(hold, WIDTH + 57 + 20, 430 + 20, 10);
            else if(hold == 4)
                f.drawFigure(hold, WIDTH + 57 + 15, 430 + 15, 10);
            else if(hold == 5)
                f.drawFigure(hold, WIDTH + 57 + 20, 430 + 15, 10);
            else if(hold == 6)
                f.drawFigure(hold, WIDTH + 57 + 20, 430 + 15, 10);
            queue.push(hold);

            window.draw(leftBottom);
    }
};

class board{
    public:
    float prevX = 0;
    float prevY = 0;
    int score = 0;
    int hold = -1;
    bool disableHold = false;
    std::queue<int> figureList;
    float speed = 0.25;

    float posX = WIDTH/2 - TILE_SIZE;
    float posY = -80;

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

    void populateFigureList(){
        while(figureList.size() < 4){    
            figureList.push(f.selectRandomFigure());
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
        disableHold = false;
        currentFigure = figureList.front();
        figureList.pop();
        posY = -80;
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

    void putOnHold(){
        if(hold == -1){
            hold = currentFigure;
            bringNewFigure();
        }
        else{
            int cpCur = currentFigure;
            currentFigure = hold;
            hold = cpCur;
            posY = -80;
            posX = WIDTH/2 - 2*TILE_SIZE;
        }
        disableHold = true;
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
            
            if(f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY + TILE_SIZE == HEIGHT){
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
        for(int j = vertical-1; j >= 0; j--){
            int counter = 0;
            for(int i = 0; i < horizontal; i++){
                if (wall.at(j)->at(i)->active){
                    counter++;
                    if(counter % 10 == 0 && speed != 0.1) speed -= 0.01;
                }
            }
            if(counter == WIDTH/TILE_SIZE){
                score++;
                for(int i = 0; i < horizontal; i++){
                    wall.at(j)->at(i)->color = sf::Color::Transparent;
                    wall.at(j)->at(i)->active = false;
                }

                for(int z = j; z >= 1; z--){
                    for(int i = 0; i < horizontal; i++){
                        sf::Color copyC =  wall.at(z)->at(i)->color;
                        bool copyA =  wall.at(z)->at(i)->active;

                        wall.at(z)->at(i)->color = wall.at(z-1)->at(i)->color; 
                        wall.at(z)->at(i)->active = wall.at(z-1)->at(i)->active; 

                        wall.at(z-1)->at(i)->color = copyC;
                        wall.at(z-1)->at(i)->active = copyA;
                    }
                }
            }
        }
    }

    void moveFigureDown(){
        if(clockDown.getElapsedTime().asSeconds() >= speed){
            posY += TILE_SIZE;
            clockDown.restart();
        }
    }

    void moveFigureDownFaster(){
        if(clockDown.getElapsedTime().asSeconds() >= speed/2){
            posY += TILE_SIZE;
            clockDown.restart();
        }
    }

    void hardDrop(){
        int least = 10000000;

        for(int i = 0; i < 4; i++){
            int arrayY = f.figures.at(currentFigure).at(i).at(1) + posY/TILE_SIZE;
            int arrayX = f.figures.at(currentFigure).at(i).at(0) + posX/TILE_SIZE;

            if(arrayX > horizontal){return;}
            if(arrayX < 0){return;}
            if(arrayY < 0){return;}
        }

        for(int i = 0; i < 4; i ++){
            int arrayX = f.figures.at(currentFigure).at(i).at(0) + posX/TILE_SIZE;
            int arrayY = f.figures.at(currentFigure).at(i).at(1) + posY/TILE_SIZE;

            for(arrayY; arrayY < vertical; arrayY++){
                if(wall.at(arrayY)->at(arrayX)->active){
                    int diff = wall.at(arrayY)->at(arrayX)->y - 
                    (f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY);

                    if(diff < least) least = diff;
                }
            }
        }

        for(int i = 0; i < 4; i++){
            int diff = HEIGHT - (f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY);
            if(diff < least) least = diff;
        }

        posY += least - TILE_SIZE;
    }

    void valid(){
        for(int i = 0; i < 4; i++){
            if((WIDTH == f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX))
            {
                posX -= 40;
            }
        }

        for(int i = 0; i < 4; i++){
            if(0 > f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX)
            {
                posX += 40;
            }  
        }

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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            hardDrop();
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E) && disableHold != true)
        {
            putOnHold();
        } 
    }
    
    void addFigureToWall(){
        sf::Color color;
        switch (currentFigure)
        {
            case 0:
                color = sf::Color(154, 214, 170);
            break;
            case 1:
                color = sf::Color(157, 154, 214);
            break;
            case 2:
                color = sf::Color(126, 247, 99);
            break;
            case 3:
                color = sf::Color(255, 163, 77);
            break;
            case 4:
                color = sf::Color(101, 101, 247);
            break;
            case 5:
                color = sf::Color(61, 226, 245);
            break;
            case 6:
                color = sf::Color(250, 117, 206);
        }

        for(int i = 0; i < 4; i++){
            int arrayX = f.figures.at(currentFigure).at(i).at(0) + posX/TILE_SIZE;
            int arrayY = f.figures.at(currentFigure).at(i).at(1) + posY/TILE_SIZE;

            wall.at(arrayY)->at(arrayX)->active = true;
            wall.at(arrayY)->at(arrayX)->color = color;

            wall.at(arrayY)->at(arrayX)->x = f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX;
            wall.at(arrayY)->at(arrayX)->y = f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY;
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

    void printShadow(){
        int least = 10000000;

        for(int i = 0; i < 4; i ++){
            int arrayX = f.figures.at(currentFigure).at(i).at(0) + posX/TILE_SIZE;
            int arrayY = f.figures.at(currentFigure).at(i).at(1) + posY/TILE_SIZE;

            if(arrayY < 0){return;}

            for(arrayY; arrayY < vertical; arrayY++){
                if(wall.at(arrayY)->at(arrayX)->active){
                    int diff = wall.at(arrayY)->at(arrayX)->y - 
                    (f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY);

                    if(diff < least) least = diff;
                }
            }
        }

        for(int i = 0; i < 4; i++){
            int diff = HEIGHT - (f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + posY);
            if(diff < least) least = diff;
        }

        int shadowY = posY + least - TILE_SIZE;

        sf::Color color;
        switch (currentFigure)
        {
            case 0:
                color = sf::Color(154, 214, 170);
            break;
            case 1:
                color = sf::Color(157, 154, 214);
            break;
            case 2:
                color = sf::Color(126, 247, 99);
            break;
            case 3:
                color = sf::Color(255, 163, 77);
            break;
            case 4:
                color = sf::Color(101, 101, 247);
            break;
            case 5:
                color = sf::Color(61, 226, 245);
            break;
            case 6:
                color = sf::Color(250, 117, 206);
        }

        for(int i = 0; i < 4; i++){
            sf::RectangleShape tile = sf::RectangleShape(sf::Vector2f(TILE_SIZE-2, TILE_SIZE-2));
            tile.setOutlineColor(color);
            tile.setOutlineThickness(2.0f);

            tile.setFillColor(sf::Color::Transparent);

            tile.setPosition(f.figures.at(currentFigure).at(i).at(0) * TILE_SIZE + posX, 
            f.figures.at(currentFigure).at(i).at(1) * TILE_SIZE + shadowY);

            window.draw(tile);
        }
    }

    board(){
        f.rotateFigure(currentFigure);
        populateFigureList();
        
        initializeWall();
        menu m;
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
            populateFigureList();

            window.clear();
            savePosition();
            f.drawFigure(currentFigure, posX, posY, TILE_SIZE);

            moveCurrentFigure();
            checkCollision(); 
            moveFigureDown();
            checkCollision();

            line();
            printWall();
            printShadow();
            renderGrid();

            m.overlay(score);
            m.rectangles();
            m.drawQueue(figureList, hold);
            
            window.display();
        }
    }
};



int main(){
    sf::Vector2u size = window.getSize();
    sf::View view(sf::Vector2f(170, 240), sf::Vector2f(size.x, size.y));
    window.setView(view);
    window.setFramerateLimit(120);
    board b;
    menu m;
    return 0;
}
