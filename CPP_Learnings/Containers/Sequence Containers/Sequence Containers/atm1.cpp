#include <iostream>
#include <map>
#include <vector>

using namespace std;

class Transaction {
public:
    string tranc_type;
    double amount;
    Transaction(string type, double amount) : tranc_type(type), amount(amount) {}
};

class Account {
private:
    int accountNumber;
    string userName;
    int pin;
    double balance;
    vector<Transaction> transactions;

public:
    Account() = default;

    Account(int accNum, string uName, int p, double bal)
        : accountNumber(accNum), userName(uName), pin(p), balance(bal) {}

    bool authenticate(int p) {
        if (pin == p) {
            return true;
        }
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount! Must be greater than 0.\n";
            return;
        }
        balance += amount;
        transactions.emplace_back("Deposit", amount);
        cout << "Deposit successful!\n";
    }

    bool withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid amount! Must be greater than 0.\n";
            return false;
        }
        if (amount > balance) {
            cout << "Insufficient balance!\n";
            return false;
        }
        balance -= amount;
        transactions.emplace_back("Withdraw", amount);
        cout << "Withdrawal successful!\n";
        return true;
    }

    void displayBalance() {
        cout << "Current Balance: $" << balance << endl;
    }

    void displayTransactions() {
        if (transactions.empty()) {
            cout << "No transactions available.\n";
            return;
        }
        cout << "Transaction History:\n";
        for (auto& t : transactions)
            cout << t.tranc_type << ": $" << t.amount << endl;
    }

    string getUserName() const { return userName; }
};

class ATM {
private:
    map<int, Account> accounts;

public:
    ATM() {
        accounts.emplace(1010, Account(1010, "Shivaramakrishnan", 1, 1000.0));
        accounts.emplace(2020, Account(2020, "Dhisha Vijay", 2, 1000.0));
        accounts.emplace(3030, Account(3030, "Kaniskaran", 3, 1000.0));
        accounts.emplace(4040, Account(4040, "Tony Doss", 4, 1000.0));
    }

    void run() {
        int accountNumber, pin;
        cout << "Welcome to ATM!\n";
        cout << "Enter Account Number: ";
        cin >> accountNumber;
        cout << "Enter PIN: ";
        cin >> pin;

        auto it = accounts.find(accountNumber);
        if (it == accounts.end() || !it->second.authenticate(pin)) {
            cout << "Invalid Credentials!\n";
            return;
        }

        Account& acc = it->second;
        cout << "Welcome, " << acc.getUserName() << "!\n";

        while (true) {
            int choice;
            cout << "\n1. Deposit\n2. Withdraw\n3. Display Balance\n4. Transaction History\n5. Logout\n";
            cout << "Choose an option: ";
            cin >> choice;

            if (choice == 1) {
                double amount;
                cout << "Enter deposit amount: ";
                cin >> amount;
                acc.deposit(amount);
            }
            else if (choice == 2) {
                double amount;
                cout << "Enter withdrawal amount: ";
                cin >> amount;
                acc.withdraw(amount);
            }
            else if (choice == 3) {
                acc.displayBalance();
            }
            else if (choice == 4) {
                acc.displayTransactions();
            }
            else {
                cout << "Logging out...\n";
                break;
            }
        }
    }
};

int main() {
    ATM atm;
    atm.run();
    return 0;
}
