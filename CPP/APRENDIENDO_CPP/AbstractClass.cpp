#include <iostream>
using namespace std;

class S {
    /*
        Identificador public: hace que los métodos definidos públicos
        puedan ser accedidos y visibles a otras clases. Ocurre lo mismo con
        variables
    */
    public:
        /*
            en esta clase se declara un método "virtual",
            también llamado abstracto, que puede ser sobre
            escrito (implementado) por clases que hereden la clase S

            el = 0; solo puede existir en métodos int que hayan sido declarados
            con la keyword "virtual". Esta keyword indica que el método no
            tiene implementación;
        */
        virtual int Area() = 0;

        /*
            Además, la clase s implementa los métodos setter propios de la
            altura y la anchura de una figura, que son heredados por las 
            clases triángulo y rectángulo mediante: 

            class Rectangle: public S
        */
        void setWidth(int a) {
            wid = a;
        }
        void setHeight(int b) {
            hght = b;
        }  
    
    /*
        Identificador protected: protected - members cannot be accessed
        from outside the class, however, they can be accessed in inherited 
        classes.
    */
    protected:
        int wid;
        int hght;
};
/* Notice the ; after a class "class s {};" */

class Rectangle: public S {
    public:
        /*
            Aquí vemos como el método area(), definido en la clase pública S
            es redefinido en la clase Rectangle, con los atributos propios de 
            la clase S.
        */
        int Area() {
            return (wid * hght);
        }
};

class Triangle: public S {
    public:
        /*
            Aquí vemos como el método area(), definido en la clase pública S
            es redefinido en la clase Triangle, con los atributos propios de 
            la clase S.
        */
        int Area() {
            return (wid * hght)/2;
      }
};

int main() {
    /*
        Invocamos una instancia de las clases Rectangle y Triangle,
        sobre las cuales podemos operar mediante los métodos que 
        poseen.

        Cabe destacar que, como tanto Triangle como Rectangle extienden 
        la clase S, tienen acceso a estos mismos métodos.
    */
    Rectangle Rec;
    Triangle Tri;
    Rec.setWidth(15);
    Rec.setHeight(50);
    Tri.setWidth(70);
    Tri.setHeight(88);
    cout << "The calculated area of the required rectangle: " << Rec.Area() << endl;
    cout << "The calculated area of the required triangle: " << Tri.Area() << endl;
}  