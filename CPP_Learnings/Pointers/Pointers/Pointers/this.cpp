#include <iostream>
using namespace std;

class MyClass {
public:
    void show() {
        cout << "Address of this object: " << this << endl;
    }
};

int main() {
    MyClass obj;
    obj.show(); 

    return 0;
}
