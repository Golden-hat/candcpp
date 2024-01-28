#include "Node.cpp"
#include <iostream>
#include <string>

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
   
    int numberOfLevels(){
        return numberOfLevels(0, &root);
    }

	void drawTree(Node<T>* current, std::string margin){
        bool found = false;
        for(int j = margin.length()-1; j > 0; j--)
        {
            if(found) margin[j] = ' ';
            if('|' == margin[j] && !found){
                found = true;
            }
        }
        for(int i = 0; i < current->children.size(); i++){
            std::cout << margin << current->children.at(i)->data << std::endl;
            drawTree(current->children.at(i), margin+"|--");
        }
	}

    void drawTree(){
        std::cout << root.data << std::endl;
        drawTree(&root, "|--");
    }
};

int main(){
    Tree<int> t;
	t.root.data = 1;
    t.addChildren(3, &t.root);
    t.addChildren(3, t.root.children.at(0));
    t.addChildren(3, t.root.children.at(0));
    t.addChildren(3, t.root.children.at(0));
    t.addChildren(2, &t.root);
    t.addChildren(6, &t.root);
    t.addChildren(10, &t.root);
    t.addChildren(24, &t.root);

    t.addChildren(3452, t.root.children.at(2));
    t.addChildren(31, t.root.children.at(2));
    t.addChildren(1233, t.root.children.at(2));

    t.addChildren(1233, t.root.children.at(2)->children.at(0));
    t.addChildren(11233, t.root.children.at(2)->children.at(0));
    t.addChildren(12, t.root.children.at(2)->children.at(0)->children.at(0));

    t.drawTree();
    return 0;
}
