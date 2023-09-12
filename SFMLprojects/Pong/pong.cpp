#include <iostream>
#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <chrono>
#include <thread>

const int WIDTH = 800;
const int HEIGHT = 800;

const int BAR_LENGTH = 200;
const int COORDS_SPAWN_P1_X = 40;
const int COORDS_SPAWN_P1_Y = 300;

const int COORDS_SPAWN_P2_X = WIDTH - 40;
const int COORDS_SPAWN_P2_Y = 300;

const int WIDTH_BAR = 10;
const int WIDTH_BALL = 10;
const int X_VEL = 10;

bool GAME_OVER = false;
bool backToMenu = false;
bool playerScored = true;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "PONG");

class player{
    public:
    int side;
    int score;

    sf::RectangleShape playerRect;

    player(){}

    player(int j, int k, int width, int height, int s, int score){
        this->playerRect = sf::RectangleShape(sf::Vector2f(width, height));
        this->side = s;
        this->score = score;

        playerRect.move(j, k);
        playerRect.setFillColor(sf::Color::White);
    }

    int getSide(){
        return side;
    }

    int getScore(){
        return this->score;
    }

    void updateScore(){
        this->score++;
    }

    void playerMovementOne(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && 0 <= playerRect.getPosition().y)
        {
            playerRect.move(0, -8);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && HEIGHT - BAR_LENGTH > playerRect.getPosition().y)
        {
            playerRect.move(0, +8);
        }
    }

    void playerMovementTwo(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && 0 <= playerRect.getPosition().y)
        {
            playerRect.move(0, -8);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && HEIGHT - BAR_LENGTH > playerRect.getPosition().y)
        {
            playerRect.move(0, +8);
        }
    }

    void resetPlayerPosition(){
        playerRect.setPosition(playerRect.getPosition().x, 300);
    }

    void renderPlayer(){
        window.draw(playerRect);
    }

    int positionX(){
        return (int) playerRect.getPosition().x;
    }

    int positionY(){
        return (int) playerRect.getPosition().y;
    }
};

class ball{
    public:
    sf::CircleShape ballShape;

    float directionY;
    float directionX;

    bool TRIGGER_UP = false;
    bool TRIGGER_DOWN = false;

    ball(){
        srand(time(0));
        directionY = (((float)rand()/RAND_MAX) - 0.5) * 5; 
        if((rand()%2) == 0){
            directionX = -X_VEL;
        }
        else{
            directionX = X_VEL; 
        }

        ballShape = sf::CircleShape(WIDTH_BALL/2);
        ballShape.setPosition(WIDTH/2, HEIGHT/2);
        ballShape.setFillColor(sf::Color::White);
    }

    void renderBall(){
        window.draw(ballShape);
    }

    void animation(){
        for(int i = 1; i < 3000; i += 40){
            sf::CircleShape circle = sf::CircleShape(i);
            int x = positionX() - i;
            int y = positionY() - i;
            circle.setPosition(x, y);
            circle.setFillColor(sf::Color::White);
            window.draw(circle);
            window.display();

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    GAME_OVER = true;
                    window.close();
                }
            }
        }   
    }

    void ballMovement(player* p1, player* p2){
        ballShape.move(directionX, directionY);
        if(ballShape.getPosition().y >= HEIGHT || ballShape.getPosition().y <= 0){
            directionY *= -1;
        }

        if(ballShape.getPosition().x >= WIDTH){
            p1->updateScore();
            playerScored = true;
            TRIGGER_UP, TRIGGER_DOWN = false;
            animation();
        }
        if(ballShape.getPosition().x <= - WIDTH_BALL){
            p2->updateScore();
            playerScored = true;
            TRIGGER_UP, TRIGGER_DOWN = false;
            animation();
        }
    }

    void checkCollision(player p){
        if(p.getSide() == 1){
            if(p.positionX() + WIDTH_BAR == ballShape.getPosition().x && 
               p.positionY() - WIDTH_BALL < ballShape.getPosition().y && 
               p.positionY() + BAR_LENGTH + WIDTH_BALL >= ballShape.getPosition().y){
                srand(time(NULL));
                directionY = (((float)rand()/RAND_MAX) - 0.5) * 22; 
                directionX *=-1;
            }
        }
        else{
            if(p.positionX() - WIDTH_BALL == ballShape.getPosition().x && 
               p.positionY() - WIDTH_BALL < ballShape.getPosition().y && 
               p.positionY() + BAR_LENGTH >= ballShape.getPosition().y){
                srand(time(NULL));
                directionY = (((float)rand()/RAND_MAX) - 0.5) * 22; 
                directionX *=-1;
            }
        }
    }

    void cpuMovement(player* p){
        if((p->positionY() - positionY() + BAR_LENGTH/2 <= -90 || TRIGGER_UP) && (HEIGHT - BAR_LENGTH > p->playerRect.getPosition().y)){
            TRIGGER_DOWN = false;
            TRIGGER_UP = true;
            p->playerRect.move(0, 8);
            if(p->positionY() <= positionY() + 75 && p->positionY() + BAR_LENGTH - 75 >= positionY()){
                TRIGGER_UP = false;
                TRIGGER_DOWN = false;
            }
        }

        if((p->positionY() - positionY() + BAR_LENGTH/2 >= 90 || TRIGGER_DOWN) && (0 <= p->playerRect.getPosition().y)){
            TRIGGER_UP = false;
            TRIGGER_DOWN= true;
            p->playerRect.move(0, -8);
            if(p->positionY() <= positionY() + 75  && p->positionY() + BAR_LENGTH - 75 >= positionY()){
                TRIGGER_UP = false;
                TRIGGER_DOWN = false;
            }
        }
    }

    void resetBallPosition(){
        srand(time(0));
        directionY = (((float)rand()/RAND_MAX) - 0.5) * 5; 
        if((rand()%2) == 0){
            directionX = -X_VEL;
        }
        else{
            directionX = X_VEL; 
        }
        ballShape.setPosition(WIDTH/2, HEIGHT/2);
    }

    int positionX(){
        return (int) ballShape.getPosition().x;
    }

    int positionY(){
        return (int) ballShape.getPosition().y;
    }
};

class menu{
    private:
    bool singlePlayer;

    public:
    void mainMenuScreen(){
        sf::Text text;
        sf::Text gamemodeSelect;

        sf::Font font;
        if (!font.loadFromFile("LiberationMono-Regular.ttf"))
        {
            // error...
        }
        text.setFont(font);

        text.setString("PONG!");

        text.setCharacterSize(100);

        text.setFillColor(sf::Color::White);

        sf::FloatRect textRect1 = text.getLocalBounds();
        text.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
        text.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f - 100));

        gamemodeSelect.setFont(font);

        gamemodeSelect.setString("Press M to play local VS, or S to play against the machine");

        gamemodeSelect.setCharacterSize(20); // in pixels, not points!

        // set the color
        gamemodeSelect.setFillColor(sf::Color::White);

        sf::FloatRect textRect2 = gamemodeSelect.getLocalBounds();
        gamemodeSelect.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
        gamemodeSelect.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f + 100));
        
        window.draw(text);
        window.draw(gamemodeSelect);
        window.display();

        bool wait = true;
        while(wait && window.isOpen()){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::M)){
                singlePlayer = false;
                wait = false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                singlePlayer = true;
                wait = false;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    GAME_OVER = true;
                    window.close();
                }
            }   
        }
    }

    menu(){
        mainMenuScreen();
    }

    bool getGamemode(){
        return singlePlayer;
    }
};

class board{
    public:
    ball b;

    player p1 = player(COORDS_SPAWN_P1_X, COORDS_SPAWN_P1_Y, WIDTH_BAR, BAR_LENGTH, 1, 0);
    player p2 = player(COORDS_SPAWN_P2_X, COORDS_SPAWN_P2_Y, WIDTH_BAR, BAR_LENGTH, 2, 0);

    void renderScore(){
        sf::Text p1Sc;
        sf::Text p2Sc;

        sf::Font font;
        if (!font.loadFromFile("LiberationMono-Regular.ttf"))
        {
            // error...
        }
        p1Sc.setFont(font); // font is a sf::Font
        p2Sc.setFont(font); // font is a sf::Font

        // set the string to display
        p1Sc.setString(std::to_string(p1.getScore()));
        p2Sc.setString(std::to_string(p2.getScore()));

        // set the character size
        p1Sc.setCharacterSize(30); // in pixels, not points!
        p2Sc.setCharacterSize(30); // in pixels, not points!

        // set the color
        p1Sc.setFillColor(sf::Color::White);
        p2Sc.setFillColor(sf::Color::White);

        sf::FloatRect textRect1 = p1Sc.getLocalBounds();
        p1Sc.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
        p1Sc.setPosition(sf::Vector2f(WIDTH/4,HEIGHT-50));

        sf::FloatRect textRect2 = p2Sc.getLocalBounds();
        p2Sc.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
        p2Sc.setPosition(sf::Vector2f(3*(WIDTH/4),HEIGHT-50));
        
        window.draw(p1Sc);
        window.draw(p2Sc);
    }

    void roundPause(){
        sf::Text text;

        sf::Font font;
        if (!font.loadFromFile("LiberationMono-Regular.ttf"))
        {
            // error...
        }
        text.setFont(font); // font is a sf::Font

        // set the string to display
        text.setString("Press space or move players (W/D, UP/DOWN) to begin the round.");

        // set the character size
        text.setCharacterSize(20); // in pixels, not points!

        // set the color
        text.setFillColor(sf::Color::White);

        sf::FloatRect textRect = text.getLocalBounds();
        text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
        text.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
        text.setPosition(sf::Vector2f(WIDTH/2, 50));
        
        window.draw(text);
        window.display();

        bool wait = true;
        while(wait && window.isOpen()){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)
            || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
                wait = false;
            }

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    GAME_OVER = true;
                    window.close();
                }
            }   
        }
    }

   void pauseMenu(){
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
            bool pause = true;

            sf::Text text;
            sf::Text gamemodeSelect;

            sf::Font font;
            if (!font.loadFromFile("LiberationMono-Regular.ttf"))
            {
                // error...
            }
            text.setFont(font);

            text.setString("PAUSE");

            text.setCharacterSize(100);

            text.setFillColor(sf::Color::White);

            sf::FloatRect textRect1 = text.getLocalBounds();
            text.setOrigin(textRect1.left + textRect1.width/2.0f, textRect1.top  + textRect1.height/2.0f);
            text.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f - 100));

            gamemodeSelect.setFont(font);

            gamemodeSelect.setString("Press X to exit the game, R to resume it, or B to go back to the menu.");

            gamemodeSelect.setCharacterSize(15); // in pixels, not points!

            // set the color
            gamemodeSelect.setFillColor(sf::Color::White);

            sf::FloatRect textRect2 = gamemodeSelect.getLocalBounds();
            gamemodeSelect.setOrigin(textRect2.left + textRect2.width/2.0f, textRect2.top  + textRect2.height/2.0f);
            gamemodeSelect.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f + 100));
            
            window.draw(text);
            window.draw(gamemodeSelect);
            window.display();

            while(pause){
                if(sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
                    pause = false;
                }

                sf::Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed){
                        pause = false;
                        GAME_OVER = true;
                        window.close();
                    }
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::X)){
                    GAME_OVER = true;
                    pause = false;
                    window.close();
                }

                if(sf::Keyboard::isKeyPressed(sf::Keyboard::B)){
                    pause = false;
                    backToMenu = true;

                    b.resetBallPosition();
                    p1.resetPlayerPosition();
                    p2.resetPlayerPosition();

                    p1.score = 0;
                    p2.score = 0;

                    playerScored = true;
                }
            }
        }
    }


    void singlePlayerLoop(){
        if(playerScored){
            b.resetBallPosition();
            p1.resetPlayerPosition();
            p2.resetPlayerPosition();

            p1.renderPlayer();
            p2.renderPlayer();
            b.renderBall();
            renderScore();

            window.display();

            roundPause();

            playerScored = false;
        }

        renderScore();

        p1.playerMovementOne();
        b.cpuMovement(&p2);

        p1.renderPlayer();
        p2.renderPlayer();
        b.renderBall();

        b.checkCollision(p1);
        b.checkCollision(p2);
        b.ballMovement(&p1, &p2);

        pauseMenu();
    }

    void localVSLoop(){
        if(playerScored){
            b.resetBallPosition();
            p1.resetPlayerPosition();
            p2.resetPlayerPosition();

            p1.renderPlayer();
            p2.renderPlayer();
            b.renderBall();
            renderScore();

            window.display();

            roundPause();

            playerScored = false;
        }

        renderScore();

        p1.playerMovementOne();
        p2.playerMovementTwo();

        p1.renderPlayer();
        p2.renderPlayer();
        b.renderBall();

        b.checkCollision(p1);
        b.checkCollision(p2);
        b.ballMovement(&p1, &p2);

        pauseMenu();
    }

    board(bool singlePlayer){

        while(window.isOpen() && !backToMenu)
        {
            window.setFramerateLimit(60);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                    GAME_OVER = true;
                }
            }

            window.clear();
        
            if(singlePlayer){
                singlePlayerLoop();
            }else{
                localVSLoop();
            }   

            window.display();
        }

        backToMenu = false;
    }
};

int main(){
    while(!GAME_OVER){
        window.clear();
        menu m;
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
        board b(m.getGamemode());
    }
    return 0;
};