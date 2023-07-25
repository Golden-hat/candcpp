#include <iostream>
#include "Node.cpp"

template<class T>
class LinkedList{
    private:
        int size;
    public:
        Node<T>* head;

        LinkedList(){
            size = 0;
            head = NULL;
        }

        void reset(){
            head = NULL;
            size = 0;
        }

        void add(T n){
            if(head == nullptr){
                head = new Node<T>;
                head->data = n;
                head->next = NULL;
                size++;
            }
            else{
                Node<T>* elem = new Node<T>;    
                elem->data = n;
                elem->next = head;

                head = elem;
                size++;
            }
        }

        void addMultiple(T t[], int s){
            for(int i = 0; i < s; i++){
                if(head == nullptr){
                    head = new Node<T>;
                    head->data = t[i];
                    head->next = NULL;
                }
                else{
                    Node<T>* elem = new Node<T>;    
                    elem->data = t[i];
                    elem->next = head;

                    head = elem;
                }
                size++;
            }
        }

        void sortAscending(){
            LinkedList<T> l;
            int storeSize = size;
            while(size != 0){
                Node<T>* dummy = head;
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
            LinkedList<T> l;
            int storeSize = size;
            while(size != 0){
                Node<T>* dummy = head;
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

        Node<T>* find(T n){
            Node<T>* dummy = head;
            while(dummy != NULL){
                if(dummy->data == n){
                    return dummy;
                }
                dummy = dummy->next;
            }
            std::cout << "The element ("<< n <<") does not seem to exist in the list." << std::endl;
            return NULL;
        }

        void remove(T n){
            Node<T>* dummy = head;
            Node<T>* previous = NULL;
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
        
        void removeHead(){
            if(head != nullptr){
                Node<T>* headC = head;
                head = head->next;
                delete headC;
                size--;
            }
        }

        void movetoHead(T n){
            if(find(n) != NULL){
                Node<T>* dummy = find(n);
                Node<T>* copy = new Node<T>;
                copy->data = dummy->data;
                
                remove(dummy->data);
                copy->next = head;
                head = copy;
            }
        }

        void printList(){
            if(head == nullptr){std::cout << "{}" <<std::endl; return;}
            Node<T>* dummy = head;
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