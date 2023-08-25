#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Queue.cpp"
#include <time.h>

const int SIZE_OF_BODY = 40;
const int WIDTH = 800;
const int HEIGHT = 800;
int SCORE = 0;
bool GAME_OVER = false;
bool retryCheck = true;
std::string toggle;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake!");

void gameOver(){
    sf::Text text;

    sf::Font font;
    if (!font.loadFromFile("LiberationMono-Regular.ttf"))
    {
        // error...
    }

    // select the font
    text.setFont(font); // font is a sf::Font

    // set the string to display
    text.setString("GAME OVER");

    // set the character size
    text.setCharacterSize(50); // in pixels, not points!

    // set the color
    text.setFillColor(sf::Color::White);

    // set the text style
    text.setStyle(sf::Text::Bold);

    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width/2.0f, textRect.top  + textRect.height/2.0f);
    text.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/2.0f));
    text.setPosition(sf::Vector2f(400,75));

    sf::Text subtitle;
    subtitle.setFont(font);
    subtitle.setString("Press X to quit the game or R to retry.");
    subtitle.setCharacterSize(20);

    sf::FloatRect subRect = subtitle.getLocalBounds();
    subtitle.setOrigin(subRect.left + subRect.width/2.0f, subRect.top  + subRect.height/2.0f);
    subtitle.setPosition(sf::Vector2f(400,200));

    sf::Text score;
    score.setFont(font);
    score.setString("Score: "+std::to_string(SCORE));
    score.setCharacterSize(20);

    sf::FloatRect scoreRect = score.getLocalBounds();
    score.setOrigin(scoreRect.left + scoreRect.width/2.0f, scoreRect.top  + scoreRect.height/2.0f);
    score.setPosition(sf::Vector2f(WIDTH/2.0f, HEIGHT/3.0f));

    window.clear();
    window.draw(text);
    window.draw(subtitle);
    window.draw(score);
    window.display();

    while(retryCheck){

        sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    SCORE = 0; GAME_OVER = true; retryCheck = false;
                    window.close();
                }
            }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            SCORE = 0; GAME_OVER = false; retryCheck = false; toggle="";}
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::X)) {
            SCORE = 0; GAME_OVER = true; retryCheck = false;
            window.close();
        }
    }
}

struct BodyPart{
    public:
    int x;
    int y;
};

class Snake{
    private:
    Queue<BodyPart> body = Queue<BodyPart>();

    public:
    Snake(){
        BodyPart initialBP;
        initialBP.x = 400;
        initialBP.y = 400;
        body.enqueue(initialBP);
    }

    void drawBody(){
        Node<BodyPart>* aux = body.getHead();
        while(aux!= nullptr){
            sf::RectangleShape bodyPart(sf::Vector2f(40, 40));
            bodyPart.move(aux->data.x, aux->data.y);
            bodyPart.setFillColor(sf::Color::Green);
            window.draw(bodyPart);

            aux = aux->next;
        }
    }

    void growth(){
        if(SCORE+1 < body.getSize()){
            body.dequeue();
        }
    }

    Node<BodyPart>* getHeadOfSnake(){
        return body.getTail();
    }

    void controls(){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && toggle != "right")
            toggle = "left";
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && toggle != "left")
            toggle = "right";     
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && toggle != "down")
            toggle = "up";               
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && toggle != "up")
            toggle = "down";              

        if (toggle == "left")
        {
            BodyPart newBodyPart;
            newBodyPart.x = body.getTail()->data.x - 40;
            newBodyPart.y = body.getTail()->data.y - 0;
            body.enqueue(newBodyPart);
        }
        else if (toggle == "right")
        {
            BodyPart newBodyPart;
            newBodyPart.x = body.getTail()->data.x + 40;
            newBodyPart.y = body.getTail()->data.y - 0;
            body.enqueue(newBodyPart);
        }
        else if (toggle == "up")
        {
            BodyPart newBodyPart;
            newBodyPart.x = body.getTail()->data.x - 0;
            newBodyPart.y = body.getTail()->data.y - 40;
            body.enqueue(newBodyPart);
        }
        else if (toggle == "down")
        {
            BodyPart newBodyPart;
            newBodyPart.x = body.getTail()->data.x - 0;
            newBodyPart.y = body.getTail()->data.y + 40;
            body.enqueue(newBodyPart);           
        }
    }

    bool collision(){
        Node<BodyPart>* aux = body.getHead();
        while(aux!= nullptr && aux != getHeadOfSnake()){
            if(getHeadOfSnake()->data.x == aux->data.x && getHeadOfSnake()->data.y == aux->data.y){
                GAME_OVER = true;
                return true;
            }
            aux = aux->next;
        }
        return false;
    }

    void tp(){
        if(getHeadOfSnake()->data.x < 0){getHeadOfSnake()->data.x = WIDTH;}
        else if(getHeadOfSnake()->data.y < 0){getHeadOfSnake()->data.y = HEIGHT;}
        else if(getHeadOfSnake()->data.x >= WIDTH){getHeadOfSnake()->data.x = 0;}
        else if(getHeadOfSnake()->data.y >= HEIGHT){getHeadOfSnake()->data.y = 0;}
    }
};

class Board{
    private:
    int fruitX;
    int fruitY;

    public:
    void render(){
        retryCheck = true;
        Snake s;
        while (window.isOpen() && !GAME_OVER)
        {
            window.setFramerateLimit(13);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    SCORE = 0; GAME_OVER = true; retryCheck = false;
                    window.close();
                }
            }

            //rendering is done inside here
            window.clear();

            drawFruit();
            scoreUp(s);
            s.controls();
            s.growth();
            s.drawBody();
            s.tp();
            s.collision();
            drawScore();

            window.display();
        }
    }

    Board(){
        srand(time(0));

        fruitX = (rand()%(WIDTH/SIZE_OF_BODY))*40;
        fruitY = (rand()%(HEIGHT/SIZE_OF_BODY))*40;

        std::cout << fruitX << ", " << fruitY << std::endl;
    }

    void drawFruit(){
        sf::RectangleShape fruit(sf::Vector2f(40, 40));
        fruit.move(fruitX, fruitY);
        fruit.setFillColor(sf::Color::Red);
        window.draw(fruit);
    }

    void recalculate(){
        srand(time(0));
        
        fruitX = (rand()%(WIDTH/SIZE_OF_BODY))*40;
        fruitY = (rand()%(HEIGHT/SIZE_OF_BODY))*40;
    }

    void scoreUp(Snake s){
        if(s.getHeadOfSnake()->data.x == fruitX && s.getHeadOfSnake()->data.y == fruitY){
            SCORE++;
            recalculate();
        }
    }

    void drawScore(){
         sf::Text text;

        sf::Font font;
        if (!font.loadFromFile("LiberationMono-Regular.ttf"))
        {
            // error...
        }

        // select the font
        text.setFont(font); // font is a sf::Font

        sf::Text score;
        score.setFont(font);
        score.setString("Score: "+std::to_string(SCORE));
        score.setCharacterSize(20);
        score.setPosition(sf::Vector2f(25, 25));

        window.draw(score);
    }
};

int main()
{   
    do{
        Board b;
        b.render();
        gameOver();
    }while(!GAME_OVER);
    window.close();

    return 0;
}