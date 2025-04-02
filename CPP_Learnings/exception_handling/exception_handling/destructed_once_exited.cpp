#include <iostream>
using namespace std;

class Error {
public:
    Error() {
        cout << "Constructor called\n";
    }
    ~Error() {
        cout << "Destructor called\n";
    }
};

int main() {
    try {
        Error e;
        cout << "Exception raised\n";
        throw 1;
    }
    catch (...) {
        cout << "Caught exception\n";
    }
}

/*

Output: 

Constructor called
Exception raised
Destructor called
Caught exception

*/
