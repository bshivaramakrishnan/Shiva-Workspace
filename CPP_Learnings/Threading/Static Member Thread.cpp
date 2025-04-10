#include <iostream>
#include <thread>
using namespace std;

class MyClass {
public:
    static void staticFunc() {
        cout << "Thread running using static member function\n";
    }
};

int main() {
    thread thread1(MyClass::staticFunc);
    thread1.join();
}
