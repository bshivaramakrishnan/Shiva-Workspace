#include<iostream>
#include<map>
#include<vector>
#include<string>

using namespace std;

class Transaction {
public:
	string type;
	double amount;
	Transaction(string type, double amount) :type(type), amount(amount) {}
};
class Account {
private:
	int account_num;
	double balance;
	int pin;
	vector<Transaction>transactions;

public: 
	Account() = default;

	Account(int accNum, int p, double bal)
		: account_num(accNum), pin(p), balance(bal) {}

	bool authenticate(int pin_e) {
		if (pin == pin_e) {
			return true;

		}
	}
	void deposit(double dep_amt) {
		if (dep_amt < 0) {
			cout << "Invalid Deposit";
		}
		balance += dep_amt;
		transactions.emplace_back("Deposited", dep_amt);
		cout << "Money Deposited Sucessfully -> " << dep_amt;
	}
	void withdraw(double with_amt) {
		if (with_amt > balance) {
			cout << "Insufficient Balance \n";
		}
		if (with_amt <= 0) {
			cout << "Invalid Input \n";
		}
		balance -= with_amt;
		transactions.emplace_back("Withdrawal", with_amt);
	}
	void display_balance() {
		cout << "Account Available Balance: " << balance;
	}
	void display_transactions() {
		if (transactions.empty()) {
			cout << "No Transactions Available";
		}
		for (const auto& t : transactions) {
			cout << "Transactions :";
			cout << ".............................................................";
			cout << t.type << " : " << t.amount;
		}
	}
};
class ATM{
private:
	map<int, Account> accounts;

public:
	ATM() {
		accounts.emplace(1010, Account(1010, 1, 1000.0));
		accounts.emplace(2020, Account(2020, 2, 1000.0));
		accounts.emplace(3030, Account(3030, 3, 1000.0));
		accounts.emplace(4040, Account(4040, 4, 1000.0));
	}
};