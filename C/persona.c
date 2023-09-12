#include <stdio.h>

struct persona{
    char* name;
    int age;
    char* surname;
    int favorite_number;
};

void printPersona(struct persona* p){
    char* t = p->name;
    printf("Name: %s.\n", t);
    t = p->surname;
    printf("Surname: %s.\n", t);
    
    printf("Age: %d. \n", p->age);
    printf("Favorite Number: %d. \n", p->favorite_number);
}

void setName(struct persona* p, char* name){
    p->name = name;
}

void setSurname(struct persona* p, char* surname){
    p->surname = surname;
}

void setAge(struct persona* p, int n){
    p->age = n;
}

void setFavoriteNumber(struct persona* p, int n){
    p->favorite_number = n;
}

int main(){
    struct persona p;
    setAge(&p, 19);
    setFavoriteNumber(&p, 23);

    char name[] = "Yassin";
    setName(&p, name);
    char surname[] = "Pellicer Lamla";
    setSurname(&p, surname);
    
    printPersona(&p);

    return 0;
}