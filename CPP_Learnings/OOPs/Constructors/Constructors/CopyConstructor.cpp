#include <iostream>
using namespace std;

class Sample {
private:
    int value;

public:
    Sample(int num) : value(num) {
        cout << "Constructor called!" << endl;
    }

    
    Sample(const Sample& source) {
        value = source.value;  
        cout << "Copy Constructor called!" << endl;
    }

    void display() {
        cout << "Value: " << value << endl;
    }
};

int main() {
    Sample objA(25);   
    objA.display();

    Sample objB = objA; 
    objB.display();

    return 0;
}
