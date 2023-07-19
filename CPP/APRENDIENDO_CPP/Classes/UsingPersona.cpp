#include <iostream>
#include "Persona.cpp"

int main(){
    Persona persona1 = Persona("Yassin", "Pellicer Lamla", 19);
    Student student1 = Student("Blanca", "Pérez Esquiva", 19, "LTP");

    persona1.setID("20809zsfg6450B");
    persona1.setCelibate(false);

    persona1.toString();
    persona1.announcer();

    student1.setID("208096450B");
    student1.setCelibate(true);

    student1.toString();
    student1.announcer();
}