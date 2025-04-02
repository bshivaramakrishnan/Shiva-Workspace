#include <iostream>
using namespace std;
class Number {
private:
    int a, b;

public:
    
    Number(int x, int y) : a(x), b(y) {}

    int gcd() {
        int x = a, y = b;
        while (y != 0) {
            int temp = y;
            y = x % y;
            x = temp;
        }
        return x;
    }

    bool isPrime(int n) {
        if (n <= 1) return false;
        if (n == 2) return true; 
        if (n % 2 == 0) return false; 

        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) return false;
        }
        return true;
    }
};

class MyPrimeException {
public:
    string message;
    MyPrimeException(string msg) : message(msg) {}
};

int main() {
    int x = 13, y = 56;
    Number num1(x, y);

    cout << "GCD is = " << num1.gcd() << endl;

    if (num1.isPrime(x))
        cout << x << " is a prime number" << endl;

    if (num1.isPrime(y))
        cout << y << " is a prime number" << endl;

    if (num1.isPrime(x) || num1.isPrime(y)) {
        try {
            throw MyPrimeException("Prime number detected!");
        }
        catch (const MyPrimeException& e) {
            cout << "Caught exception: " << e.message << endl;
        }
    }

    return 0;`
}
