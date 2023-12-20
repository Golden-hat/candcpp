#include <vector>
#include <iostream>

template <class T>
class Node
{
public:
    T data;
    std::vector<Node<T>*> children;
};
