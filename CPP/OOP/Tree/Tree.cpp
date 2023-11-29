#include "Node.cpp"
#include <bits/stdc++.h>
#include <iostream>
#include <SFML/Graphics.hpp>

int HEIGHT = 800;
int WIDTH = 1000;
int nodeL = 10;

sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Tree");

template<class T>
class Tree{

    public:
    Node<T> root;
    Tree(){

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
    
	void drawTree(Node<T>* curr, double segWidth, int j){
        int divisionHeight = 10;
		divisionHeight = (HEIGHT) / (divisionHeight + numberOfLevels(0, &root));

        if(j == 0){
            sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(nodeL, nodeL));
            node.setFillColor(sf::Color::White);

            node.setPosition((WIDTH)/2, divisionHeight);
            window.draw(node);
            j++;
        }

		double divisionWidth = segWidth/2;
        for(int i = 0; i < curr->children.size(); i++){
		    divisionWidth = (segWidth) / curr->children.size();
            
            sf::RectangleShape node = sf::RectangleShape(sf::Vector2f(nodeL, nodeL));
            node.setFillColor(sf::Color::White);

            node.setPosition(divisionWidth*(i+1), divisionHeight*(j+1));
            window.draw(node);
        }
        j++;
        for(int i = 0; i < curr->children.size(); i++){
            drawTree(curr->children.at(i), divisionWidth, j);
        }
	}

    void renderLoop(){
        while(window.isOpen())
        {   window.clear();
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed){
                    window.close();
                }
            }
            drawTree(&root, WIDTH-200, 0);
            window.display();
        }
    }
};

int main(){
    Tree<int> t;
	t.root.data = 1;
    t.addChildren(3, &t.root);    t.addChildren(3, &t.root);
        t.addChildren(3, &t.root);    t.addChildren(3, &t.root);    t.addChildren(3, &t.root);
        t.addChildren(3, t.root.children.at(0));
        t.addChildren(3, t.root.children.at(2));
        t.addChildren(3, t.root.children.at(3));
        t.addChildren(3, t.root.children.at(1));
        t.addChildren(3, t.root.children.at(1));
        t.addChildren(3, t.root.children.at(1));
        t.addChildren(13, t.root.children.at(1)->children.at(0));
        t.addChildren(13, t.root.children.at(1)->children.at(0));
        t.addChildren(13, t.root.children.at(1)->children.at(0));
    t.renderLoop();

	std::cout << t.numberOfLevels(0, &t.root) << std::endl;
}
