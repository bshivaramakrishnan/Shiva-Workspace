#include <iostream>
#include <memory>  

using namespace std;

class MyClass {
public:
    MyClass(int val) : data(val) {
        cout << "Constructor: Object created with value " << data << endl;
    }

    ~MyClass() {
        cout << "Destructor: Object destroyed" << endl;
    }

    void show() {
        cout << "Data: " << data << endl;
    }

private:
    int data;
};

int main() {
    
    unique_ptr<MyClass> ptr1 = make_unique<MyClass>(10);

    ptr1->show(); 
    unique_ptr<MyClass> ptr2 = move(ptr1);

    if (!ptr1) {
        cout << "ptr1 is now empty!" << endl;
    }

    ptr2->show();  

    return 0;
}
