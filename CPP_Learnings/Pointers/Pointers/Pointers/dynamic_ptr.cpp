#include <iostream>
using namespace std;

class MyClass {
public:
    void display() {
        cout << "Dynamically allocated object!" << endl;
    }
};

int main() {
    MyClass* ptr = new MyClass();  

    ptr->display();  

    delete ptr;  
    return 0;
}
