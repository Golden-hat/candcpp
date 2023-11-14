#include "Node.cpp"
#include <iostream>

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
};

int main(){
    Tree<int> t;
    t.addChildren(2, &t.root);
    t.addChildren(3, t.root.children.at(0));
}