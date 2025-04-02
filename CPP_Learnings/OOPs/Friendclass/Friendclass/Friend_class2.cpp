#include <iostream>
using namespace std;

class Customer {
private:
    string name;
    double balance;

public:
    Customer(string n, double b) : name(n), balance(b) {}

   
    friend class Bank;
};

class Bank {
public:
    void showCustomerDetails(Customer& c) {
        
        cout << "Customer Name: " << c.name << endl;
        cout << "Account Balance: $" << c.balance << endl;
    }
};

int main() {
    Customer customer("John Doe", 5000.75);  
    Bank bank;  
    bank.showCustomerDetails(customer);  

    return 0;
}
