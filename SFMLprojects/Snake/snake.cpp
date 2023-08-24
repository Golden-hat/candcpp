#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "Queue.cpp"
#include <time.h>

const int SIZE_OF_BODY = 40;
const int WIDTH = 800;
const int HEIGHT = 800;
int SCORE = 0;
bool GAME_OVER = false;
std::string toggle;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Snake!");

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
                window.close();
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
        Snake s;
        while (window.isOpen())
        {
            window.setFramerateLimit(13);

            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
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

    void recalculate(Snake s){
        srand(time(0));
        
        fruitX = (rand()%(WIDTH/SIZE_OF_BODY))*40;
        fruitY = (rand()%(HEIGHT/SIZE_OF_BODY))*40;

        Node<BodyPart>* aux = s.getHeadOfSnake();
        bool validSpawn = true;
        while(aux!= nullptr && validSpawn){
            if(aux->data.x == fruitX && aux->data.y == fruitY){
                validSpawn = false;
                fruitX = (rand()%(WIDTH/SIZE_OF_BODY))*40;
                fruitY = (rand()%(HEIGHT/SIZE_OF_BODY))*40;
            }
            else{
                validSpawn = true;
                return;
            }
        }
    }

    void scoreUp(Snake s){
        if(s.getHeadOfSnake()->data.x == fruitX && s.getHeadOfSnake()->data.y == fruitY){
            SCORE++;
            recalculate(s);
        }
    }
};

int main()
{
    Board b;
    b.render();
    return 0;
}