#include "Node.cpp"
#include <iostream>

template<class T>
class Tree{
public:
    Node<T> root;

    void addChildren(Node<T> node, Node<T> parent){
        parent.children.push_back(&node);
    }
};