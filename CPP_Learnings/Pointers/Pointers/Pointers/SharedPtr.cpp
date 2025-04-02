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
    
    shared_ptr<MyClass> ptr1 = make_shared<MyClass>(10);
    cout << "Reference count: " << ptr1.use_count() << endl;

    {
        shared_ptr<MyClass> ptr2 = ptr1; 
        cout << "Reference count after ptr2: " << ptr1.use_count() << endl;
        ptr2->show();
    } 

    cout << "Reference count after ptr2 is out of scope: " << ptr1.use_count() << endl;

   

    return 0;
}
