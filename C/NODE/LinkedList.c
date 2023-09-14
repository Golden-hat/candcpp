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

node* find(linkedList* l, int v){
    node* aux = l->head;
    while(aux != NULL){
        if(aux->x == v){return aux;}
        aux = aux->next;
    }
    return NULL;
}

void insert(linkedList* l, int v, int s){
    node* elem = find(l, s);
    
    if(elem != NULL){
        node* aux = elem->next;

        node* new_node = (node*) malloc(sizeof(node));
        new_node->x = v;
        new_node->next = aux;
        elem->next = new_node;
    }
}

void removeHead(linkedList* l){
    if(l->head != NULL){
        node* aux = l->head->next;
        free(l->head);
        l->head = aux;
    }
}

void deleteElement(linkedList* l, int v){
    node* aux = l->head;
    node* prev;

    while(aux != NULL){
        if(aux->x == v){break;}
        prev = aux;
        aux = aux->next;
    }

    if(aux == NULL){return;}
    
    node* nextAux = aux->next;
    free(aux);
    prev->next = nextAux;
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
    insert(l, 15, 1);
    deleteElement(l, 15);
    printList(l);
    
    return 0;
}
