#include <stdlib.h>
#include <stdio.h>

typedef struct node_int{
    int x;
    struct node_int* next;
}node;

typedef struct linkedList_int{
    node* head;
}linkedList;

void printNode(node* n){
    printf("%d",n->x);
}

void initializeList(linkedList* l){
    node* head = (node*) malloc(sizeof(node));
    head = NULL;
    head->next = NULL;
}

void printList(linkedList* l){
    node* aux = l->head;
    if(aux == NULL){printf("{}"); return;}

    printf("{");

    while(aux->next != NULL){
        printNode(aux);
        printf("-> ");
        aux = aux->next;
    }
    printNode(aux);
    printf("} \n");
}

void add(linkedList* l, int val) {
    node* new_node;
    new_node = (node*) malloc(sizeof(node));

    new_node->x = val;
    new_node->next = l->head;
    l->head = new_node;
}

int main(){
    /*
        The question of why one cannot make a linked list with
        stack memory is due to the scope rules and automatic memory
        management on the stack. 
        
        The basic idea of a linked list is to link nodes together based on their memory address. 
        If each node is created on the stack then those nodes will be deleted after
        hey go out of scope, so even if the user keeps pointers to their 
        memory address it is not safe to assume that they won’t be overwritten by something else.

        ...

        The code won’t work if we write the logic of the creation of a linked list 
        in a separate function and the logic of printing the elements of the linked 
        list in a separate function.
    */

    linkedList* l = (linkedList*) malloc(sizeof(linkedList)); 
    add(l, 1);
    add(l, 1423);
    add(l, 112);
    add(l, 4);
    printList(l);
    
    return 0;
}
