#include<iostream>
using namespace std;

class DivisionByZeroException {
public:
    const char* what() {
        return "Error: Division by zero is not allowed!";
    }
};

class MemoryAllocationException {
public:
    const char* what() {
        return "Error: Memory allocation failed!";
    }
};

class Divide
{
private:
    int* num1;
    int* num2;

public:
    Divide()
    {
        try
        {
           
            num1 = new int();
            num2 = new int();

            cout << "Enter first number: ";
            cin >> *num1;

            cout << "Enter second number: ";
            cin >> *num2;

          
            if (*num2 == 0)
                throw DivisionByZeroException();  

            cout << "Result: " << *num1 / *num2 << endl;
        }
        catch (const DivisionByZeroException& e)
        {
            cout << e.what() << endl;
        }
        catch (const MemoryAllocationException& e)
        {
            cout << e.what() << endl;
        }
    }

    ~Divide()
    {
        try
        {
            delete num1;
            delete num2;
        }
        catch (...)
        {
            cout << "Exception in destructor: Memory could not be freed properly!" << endl;
        }
    }

    void divide()
    {
        try
        {
            if (*num2 == 0)
                throw DivisionByZeroException();
            cout << "Division Result: " << *num1 / *num2 << endl;
        }
        catch (const DivisionByZeroException& e)
        {
            cout << e.what() << endl;
        }
    }
};

int main()
{
    try
    {
        Divide d; 
        d.divide(); 
    }
    catch (...)
    {
        cout << "An unexpected error occurred in main." << endl;
    }
    return 0;
}
