#include "Node.cpp"
// #include <bits/stdc++.h>
#include <iostream>
// #include <SFML/Graphics.hpp>
#include <string>

int HEIGHT = 800;
int WIDTH = 1000;
int nodeL = 10;

// sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tree");
// sf::View View2(sf::FloatRect(0, 0, WIDTH, HEIGHT));

template<class T>
class Tree{

    public:
    std::string name
    Node<T> root;
    Tree(std::string name){
        this->name = name;
    }

    void addChildren(T data, Node<T>* parent){
        Node<T>* n = new Node<T>;
        n->data = data;

        parent->children.push_back(n);
    }

	/* PRECONDITION. max must be initialized to 0  
	   PRECONDITION. node must be initialized to root */
	int numberOfLevels(int max, Node<T>* root){
        std::vector<int> reg;
		for(int i = 0; i < root->children.size(); i++){
			int j = numberOfLevels(max+1, root->children.at(i));
            reg.push_back(j);
		}
        for(int i = 0; i < reg.size(); i++){
            if(max < reg.at(i)) max = reg.at(i);
        }
        printf("max: %d\n", max);
		return max;
	}
    
//	void drawTree(Node<T>* curr, double segWidth, int j, double middlePoint){
//		int divisionHeight = (HEIGHT) / (10 + numberOfLevels(0, &root));
//
//        if(j == 0){
//            sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(nodeL, nodeL));
//            node.setFillColor(sf::Color::White);
//
//            node.setPosition((WIDTH)/2, divisionHeight);
//            window.draw(node);
//            j++;
//        }
//
//        double divisionWidth = segWidth/2;
//        std::vector<double> middlePoints;
//        for(int i = 0; i < curr->children.size(); i++){
//		    double divisionWidth = (segWidth) / (curr->children.size());
//
//            sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(nodeL, nodeL));
//            node.setFillColor(sf::Color::White);
//            double startingPoint = middlePoint - segWidth/2;
//            node.setPosition(startingPoint + divisionWidth*(i), divisionHeight*(j+1));
//            window.draw(node);
//
//            middlePoints.push_back(startingPoint + divisionWidth*(i));
//        }
//
//        j++;
//        for(int i = 0; i < curr->children.size(); i++){
//            drawTree(curr->children.at(i), divisionWidth, j, middlePoints.at(i));
//        }
//	}
//
//    void renderLoop(){
//        window.setView(View2);
//        while(window.isOpen())
//        {   window.clear();
//            sf::Event event;
//            while (window.pollEvent(event))
//            {
//                if (event.type == sf::Event::Closed){
//                    window.close();
//                }
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//                    View2.zoom(1.1f);
//                    window.setView(View2);
//                }
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//                    View2.zoom(0.9f);
//                    window.setView(View2);
//                }
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
//                    View2.move(-25.f, 0);
//                    window.setView(View2);
//                }
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
//                    View2.move(25.f, 0);
//                    window.setView(View2);
//                }
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
//                    View2.move(0, -25.f);
//                    window.setView(View2);
//                }
//                if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
//                    View2.move(0, 25.f);
//                    window.setView(View2);
//                }
//            }
//            drawTree(&root, WIDTH, 0, WIDTH/2);
//            window.display();
//        }
//    }
};

// int main(){
//    Tree<int> t;
//	t.root.data = 1;
//    t.addChildren(3, &t.root);
//    t.addChildren(3, t.root.children.at(0));
//    t.addChildren(3, t.root.children.at(0));
//    t.addChildren(3, t.root.children.at(0));
//    t.renderLoop();
//
//	std::cout << t.numberOfLevels(0, &t.root) << std::endl;
// }
