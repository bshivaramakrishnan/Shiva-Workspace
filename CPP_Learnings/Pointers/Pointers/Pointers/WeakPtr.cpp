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
    shared_ptr<MyClass> sp = make_shared<MyClass>(100);
    weak_ptr<MyClass> wp = sp;  
    cout << "Reference count: " << sp.use_count() << endl;

    if (auto shared = wp.lock()) { 
        cout << "Weak pointer is valid, data: ";
        shared->show();
    }
    else {
        cout << "Weak pointer is expired!" << endl;
    }

    sp.reset(); 

    if (wp.expired()) {
        cout << "Weak pointer is now expired!" << endl;
    }

    return 0;
}
