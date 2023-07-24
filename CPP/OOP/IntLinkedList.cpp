#include <iostream>
#include "IntNode.cpp"

class LinkedList{
    public:
        Node* head;
        int size;

        LinkedList(){
            head = NULL;
            size = 0;
        }

        void add(int n){
            if(head == nullptr){
                head = new Node();
                head->data = n;
                head->next = NULL;
                size++;
            }
            else{
                Node* elem = new Node();    
                elem->data = n;
                elem->next = head;

                head = elem;
                size++;
            }
        }

        void sortAscending(){
            LinkedList l;
            int storeSize = size;
            while(size != 0){
                Node* dummy = head;
                int n = dummy->data;
                
                while(dummy != NULL){
                    if(n <= dummy->data){
                        n = dummy->data;
                    } 
                    dummy = dummy->next;
                }
                l.add(n);
                remove(n);
            }
            head = l.head;
            size = storeSize;
        }

        void sortDescending(){
            LinkedList l;
            int storeSize = size;
            while(size != 0){
                Node* dummy = head;
                int n = dummy->data;
                while(dummy != NULL){
                    if(n >= dummy->data){
                        n = dummy->data;
                    } 
                    dummy = dummy->next;
                }
                l.add(n);
                remove(n);
            }
            head = l.head;
            size = storeSize;
        }

        void addMultiple(int t[], int s){
            for(int i = 0; i < s; i++){
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
                size++;
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
                    size--;
                    return;
                }
                previous = dummy;
                dummy = dummy->next;
            }
            std::cout << "The element ("<< n <<") does not seem to exist in the list." << std::endl;
        }

        void reset(){
            head = NULL;
            size = 0;
        }

        void removeHead(){
            if(head != nullptr){
                Node* headC = head;
                head = head->next;
                delete headC;
                size--;
            }
        }

        void movetoHead(int n){
            if(find(n)!=NULL){
                Node* dummy = find(n);
                Node* copy = new Node();
                copy->data = dummy->data;
                
                remove(dummy->data);
                copy->next = head;
                head = copy;
            }
        }

        void printList(){
            if(head == nullptr){std::cout << "{}" <<std::endl; return;}
            Node* dummy = head;
            /*
                Prints first character
                in a {1, ... fashion

                If there is only ONE element, it just prints out that one and returns
            */
            if(dummy->next == NULL){std::cout << "{" << dummy->data << "}" << std::endl; return;}
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
            std::cout << dummy->data << "}" << std::endl;
        }
};

int main(){
    LinkedList list;
    int array[] = {9,1,7,5,6,90,123,52,6,53,74567,78,4,7456,743,62};
    list.addMultiple(array, 16);
    list.printList();
    list.sortDescending();
    list.printList();
    list.add(3);
    list.remove(74567);
    list.sortAscending();
    list.printList();
    return 0;
}