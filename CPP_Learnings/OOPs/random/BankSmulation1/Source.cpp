#include<iostream>
#include<math.h>
#include<string>
using namespace std;
//Abstract class 
class BankAccount {
protected:
	string account_holder;
	int account_number;
	double balance;
public:
	BankAccount(string holder, int number, double b) :account_holder(holder), account_number(number), balance(b) {};

	virtual void displayinfo() {
		cout << "Account Holder info: " << account_holder;
		cout << "Account Number : " << account_number;
	}
	virtual void calculateInterest() = 0;

	void deposit(double x) {
		if (x > 0) {
			balance += x;
			cout << "deposited amount :\t" << x << "\tNew Balance :\t" << balance;
		}
		else {
			cout << "Invalid Deposit ";
		}
	}

	void withdraw(double y) {
		if (balance >= y && y >= 0) {
			balance -= y;
			cout << "Withdrawal Amount :\t" << y << "\tNew Balance :\t" << balance;
		}
		else if (balance < y) {
			cout << "insufficient balance";
		}
		else {
			cout << "invald input";
		}
	}

};
class Savings_Account : public BankAccount {
protected:
	double interest;
public:
	Savings_Account(string holder, int number, double b, double interest = 0) :BankAccount(holder, number, b) { }

	void calculateInterest()override
	{
		interest = balance * (0.07 / 12);
		balance + interest;
		cout << "Monthly Interest :\t" << interest;
	}
	void displayinfo() override {
		cout << "\nAccount Holder info  : \t" << account_holder << endl;
		cout << "Account Number         : \t" << account_number << endl;
		cout << "Balance                :\t" << balance << endl;
	}
};
int main() {
	string name;
	double id;
	double balance;
	cout << "Enter Client Name: ";
	cin >> name;
	cout << "Enter Client Account Number : ";
	cin >> id;
	cout << "Enter Balance : ";
	cin >> balance;
	Savings_Account s1(name, id, balance);
	s1.deposit(24000);
	cout << "\n";
	s1.withdraw(10000);
	cout << "\n";
	s1.calculateInterest();
	cout << "\n";
	s1.displayinfo();


}