#include <iostream>
#include "IntNode.cpp"

class LinkedList{
    public:
        Node* head;

        LinkedList(){
            head = NULL;
        }

        void add(int n){
            if(head == nullptr){
                head = new Node();
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

        void addMultiple(int t[], int size){
            for(int i = 0; i < size; i++){
                if(head == nullptr){
                head = new Node();
                head->data = t[i];
                head->next = NULL;
                }
                else{
                    Node* elem = new Node();    
                    elem->data = t[i];
                    elem->next = head;

                    head = elem;
                }
            }
        }

        Node* find(int n){
            Node* dummy = head;
            while(dummy != NULL){
                if(dummy->data == n){
                    return dummy;
                }
                dummy = dummy->next;
            }
            std::cout << "The element ("<< n <<") does not seem to exist in the list." << std::endl;
            return NULL;
        }

        void remove(int n){
            Node* dummy = head;
            Node* previous = NULL;
            while(dummy != NULL){
                if(dummy->data == n){
                    if(previous == nullptr){removeHead(); return;}
                    previous->next = previous->next->next;
                    delete dummy;
                    return;
                }
                previous = dummy;
                dummy = dummy->next;
            }
            std::cout << "The element ("<< n <<") does not seem to exist in the list." << std::endl;
        }

        void removeHead(){
            if(head != nullptr){
                Node* headC = head;
                head = head->next;
                delete headC;
            }
        }

        void movetoHead(int n){
            Node* dummy = find(n);
            Node* copy = new Node();
            copy->data = dummy->data;
            
            remove(dummy->data);
            copy->next = head;
            head = copy;
        }

        void printList(){
            if(head == nullptr){std::cout << "{}"; return;}
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
    LinkedList list;
    int array[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    list.addMultiple(array, 20);
    list.movetoHead(19);
    list.movetoHead(10);
    list.remove(3);
    list.remove(14514);
    list.printList();

    return 0;
}