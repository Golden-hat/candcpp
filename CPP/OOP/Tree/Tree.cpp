#include "Node.cpp"
#include <bits/stdc++.h>
#include <iostream>
#include <SFML/Graphics.hpp>

int HEIGHT = 800;
int WIDTH = 1000;

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
    
	void drawTree(){
		int division = (HEIGHT - 200) / numberOfLevels();

        sf::RectangleShape block = sf::RectangleShape(sf::Vector2f(30, 30));
        block.setFillColor(sf::Color::White);
        block.setOutlineColor(sf::Color(75,75,75));
        block.setOutlineThickness(1);

        block.setPosition(50 ,50);
        window.draw(block);
	}
};

int main(){
    Tree<int> t;
	t.root.data = 1;

	std::cout << t.numberOfLevels(0, &t.root) << std::endl;
}
