#include <iostream>
using namespace std;

class S {
   public:
      virtual int Area() = 0;
      void setWidth(int a) {
         wid = a;
      }
      void setHeight(int b) {
         hght = b;
      }  
   protected:
      int wid;
      int hght;
};

class Rectangle: public S {
   public:
      int Area() {
         return (wid * hght);
      }
};

class Triangle: public S {
   public:
      int Area() {
         return (wid * hght)/2;
      }
};

int main() {
  Rectangle Rec;
  Triangle Tri;
  Rec.setWidth(15);
  Rec.setHeight(50);
  Tri.setWidth(70);
  Tri.setHeight(88);
  cout << "The calculated area of the required rectangle: " << Rec.Area() << endl;
  cout << "The calculated area of the required triangle: " << Tri.Area() << endl;
}