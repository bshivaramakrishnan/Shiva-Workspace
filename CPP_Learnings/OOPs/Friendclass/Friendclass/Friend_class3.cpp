#include <iostream>
using namespace std;

class Rectangle {
private:
    int length, width;

public:
    Rectangle(int l, int w) : length(l), width(w) {}

    
    friend class Calculator;
};

class Calculator {
public:
    int calculateArea(Rectangle& r) {
       
        return r.length * r.width;
    }

    int calculatePerimeter(Rectangle& r) {
     
        return 2 * (r.length + r.width);
    }
};

int main() {
    Rectangle rect(10, 5);  
    Calculator calc;  

    cout << "Area of Rectangle: " << calc.calculateArea(rect) << endl;
    cout << "Perimeter of Rectangle: " << calc.calculatePerimeter(rect) << endl;

    return 0;
}
