#include <iostream>
using namespace std;

void hello() {
    cout << "Hello, World!" << endl;
}

int main() {
    void (*funcPtr)() = hello; 
    funcPtr();  
    return 0;
}
