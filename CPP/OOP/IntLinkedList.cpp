#include <iostream>
#include "IntNode.cpp"

class LinkedList{
    public:
        Node* head;

        LinkedList(){
            head = new Node();
        }

        void addElement(int n){
            if(head->data == NULL){
                head->data = n;
                head->next = NULL;
            }
            else{
                Node* elem = new Node();    
                elem->data = n;
                elem->next = head;

                head = elem;
            }
        }

        void printList(){
            if(head->data == NULL){std::cout << "{}"; return;}
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
    LinkedList list = LinkedList();
    list.addElement(0);
    list.printList();

    return 0;
}