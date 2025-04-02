#include <iostream>
using namespace std;

class Base {
public:
    virtual void show() { 
        cout << "Base class" << endl;
    }
};

class Derived : public Base {
public:
    void show() override {  
        cout << "Derived class" << endl;
    }
};

int main() {
    Base* ptr;
    Derived obj;
    ptr = &obj;  
    Base obj1 = Derived();
    obj1.show();

    ptr->show();  

    return 0;
}
