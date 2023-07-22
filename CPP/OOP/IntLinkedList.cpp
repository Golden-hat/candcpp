#include <iostream>
#include "IntNode.cpp"

class LinkedList{
    public:
        Node* head;

        LinkedList(int headElement){
            head = new Node();
            head->data = headElement;
            head->next = NULL;
        }

        void addElement(int n){
            Node* elem = new Node();    
            elem->data = n;
            elem->next = head;

            head = elem;
        }

        void printList(){
            Node* dummy = head;
            /*
                Prints first character
                in a {1, ... fashion

                If there is only ONE element, it just prints out that one and returns
            */
            if(dummy->next == NULL){std::cout << "{" << dummy->data << "}"; return;}
            std::cout << "{" << dummy->data << ", ";
            dummy = dummy->next;
            /*
                Prints the rest of the body except the last character
                in a 7, 9, 12, 432... fashion
            */
            while(dummy->next != NULL){
                std::cout << dummy->data << ", ";
                dummy = dummy->next;
            }
            /*
                Prints last character
                in a , 120} ... fashion
            */
            std::cout << dummy->data << "}";
        }
};

int main(){
    LinkedList list = LinkedList(4);
    list.addElement(123);
    list.printList();

    return 0;
}