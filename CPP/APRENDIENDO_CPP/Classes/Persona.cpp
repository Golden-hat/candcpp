#include <iostream>
using std::string;

class CelibateAnnouncer{
    public:
        virtual void announcer() = 0;
};

/*
    The "using" keyword can be used to:
        Bring a specific member from the namespace into the current scope.
        Bring all members from the namespace into​ the current scope.
        Bring a base class method ​or variable into the current class’s scope.

    In this case, we're only bringing the "string" type from the std library.
*/

string turnIntoText(int i){
    if(i > 0){
        return "Yes!";
    }
    else { return "No!"; }
}

class Persona: public CelibateAnnouncer{
    private:
        /*
            Atributos de persona.
            Una persona tiene:
                Edad.
                Nombre.
                Apellidos.
                Está soltero.
                ID.
        */
        int age;
        string name;
        string surname;
        bool isCelibate;
        string ID;

    public:
        Persona(string n, string sur, int a, bool isCel, string id){
            name = n;
            surname = sur;
            age = a;
            isCelibate = isCel;
            ID = id;
        }
        Persona(string n, string sur, int a){
            name = n;
            surname = sur;
            age = a;
        }

        string getID(){
            return ID;
        }
        string setID(string id){
            ID = id;
        }

        bool setCelibate(bool cel){
            isCelibate = cel;
        }
        bool getCelibate(){
            return isCelibate;
        }

        int getAge(){
            return age;
        }
        int setAge(int a){
            age = a;
        }

        void toString(){
            std::cout << "Name: "<<  name << "." << std::endl;
            std::cout << "Surname: "<<  surname << "." << std::endl;
            std::cout << "Age: "<<  age << "." << std::endl;
            std::cout << "Are they single?, " << turnIntoText(isCelibate) << "." << std::endl;
            std::cout << "Their ID is... " << ID << "." << std::endl; 
        }

        void announcer(){    
            if(getCelibate() == true){
                std::cout << "Attention chicks! This person IS SINGLE!";
            }
            else { std::cout << "Sorry y'all, this person is TAKEN!" << std::endl << std::endl;}
        }
};

/*
    Here, Student is a class that inherits the methods and constructor
    of the class Persona.

    Notice that Student declares a new constructor that adds a new parameter
    to that of Persona. In order to add it, we must pass the Student arguments
    to the Persona constructor with the following syntax.

    NOTICE THAT TO bring the public methods of a class we must use the keyword "public"
*/
class Student: public Persona{
    private:
        string Course;
    public: 
        Student(string n, string sur, int a, bool isCel, string id, string course)
            : Persona(n, sur, a, isCel, id){
                Course = course;
        }
        Student(string n, string sur, int a, string course)
            : Persona(n, sur, a){
                Course = course;
        }

        void toString() {
            Persona::toString();
            std::cout << "This person is studying the following course: " << Course << std::endl;
        }
};

