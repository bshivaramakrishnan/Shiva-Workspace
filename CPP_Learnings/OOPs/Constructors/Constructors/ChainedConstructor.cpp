#include <iostream>
using namespace std;

class ChainedConstructor {
private:
    int a, b, c;

public:
   
    ChainedConstructor(int x) : ChainedConstructor(x, 0) {
        cout << "Constructor with 1 parameter called.\n";
    }

    
    ChainedConstructor(int x, int y) : ChainedConstructor(x, y, 0) {
        cout << "Constructor with 2 parameters called.\n";
    }

    
    ChainedConstructor(int x, int y, int z) {
        a = x; b = y; c = z;
        cout << "Constructor with 3 parameters called.\n";
    }

    void display() {
        cout << "Values: " << a << ", " << b << ", " << c << endl;
    }
};

int main() {
    ChainedConstructor obj(5); 
    obj.display();

    return 0;
}
