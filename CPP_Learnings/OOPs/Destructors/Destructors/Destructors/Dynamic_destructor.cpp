#include <iostream>
using namespace std;

class Base {
public:
    virtual ~Base() { 
        cout << "Base Destructor Called\n";
    }
};

class Derived : public Base {
private:
    int* data; 
public:
    Derived(int value) {
        data = new int(value);
        cout << "Derived Constructor: Allocated memory for data = " << *data << endl;
    }

    ~Derived() override { 
        cout << "Derived Destructor: Releasing memory for data = " << *data << endl;
        delete data; 
    }
};

int main() {
    Base* obj = new Derived(42); 
    delete obj; 

    return 0;
}
