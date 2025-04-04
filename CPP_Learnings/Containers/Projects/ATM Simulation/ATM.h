#include"account.h"
#ifndef ATM_H
#define ATM_H   

class ATM 
{
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
#endif // !ATM_H
