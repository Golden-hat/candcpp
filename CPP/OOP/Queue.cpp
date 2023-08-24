#include <iostream>
#include "Node.cpp"

template <class T>
class Queue{
    private:
        Node<T>* head;
        Node<T>* tail;

        int size;
    public:
        Queue(){
            head, tail = NULL;
            size = 0;
        }

        int getSize(){
            return size;
        }

        Node<T>* getTail(){
            return tail;
        }

        Node<T>* getHead(){
            return head;
        }

        void enqueue(T t){
            if(size == 0){
                head = new Node<T>;
                head->data = t;
                head->next = NULL;

                tail = head;
                size++;
            }
            else{
                Node<T>* aux = new Node<T>;
                aux->data = t;
                aux->next = NULL;

                tail->next = aux;
                tail = aux;
                size++;
            }
        }

        void dequeue(){
            if(size == 0){
                return;
            }
            else{
                Node<T>* aux = head;
                head = head->next;
                size--;
                delete(aux);
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
