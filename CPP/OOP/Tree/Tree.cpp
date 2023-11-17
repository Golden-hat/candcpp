#include "Node.cpp"
#include <iostream>

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
		int j = 0;
		for(int i = 0; i < root->children.size(); i++){
			j = numberOfLevels(max+1, root->children.at(0));
		}
		if(j > max) max = j;
		return max;
	}
	
	void drawTree(){
			
	}
};

int main(){
    Tree<int> t;
	t.root.data = 1;
    t.addChildren(2, &t.root);
    t.addChildren(6, &t.root);
    t.addChildren(9, &t.root);
    t.addChildren(3, t.root.children.at(0));
    t.addChildren(4, t.root.children.at(1));
    t.addChildren(5, t.root.children.at(2));
    t.addChildren(2, t.root.children.at(2)->children.at(0));
	std::cout << t.numberOfLevels(0, &t.root) << std::endl;
}
