#include "Node.cpp"
#include <bits/stdc++.h>
#include <iostream>
#include <SFML/Graphics.hpp>

int HEIGHT = 800;
int WIDTH = 1000;

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

	}
};

int main(){
    Tree<int> t;
	t.root.data = 1;
    t.addChildren(2, &t.root);
    t.addChildren(3, t.root.children.at(0));
    t.addChildren(9, t.root.children.at(0)->children.at(0));
    t.addChildren(9, t.root.children.at(0)->children.at(0)->children.at(0));
    
    t.addChildren(6, &t.root);
    t.addChildren(7, &t.root);
    t.addChildren(8, &t.root);
    t.addChildren(4, t.root.children.at(1));
    t.addChildren(5, t.root.children.at(2));
    t.addChildren(5, t.root.children.at(2)->children.at(0));
	std::cout << t.numberOfLevels(0, &t.root) << std::endl;
}
