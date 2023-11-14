#include <vector>

template <class T>
class Node
{
public:
    T data;
    vector<Node*> children;
};