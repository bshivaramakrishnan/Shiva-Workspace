#include"transactions.h"
#ifndef ACCOUNT_H
#define ACCOUNT_H

class Account 
{
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
        string getTimestamp() {
            time_t now = time(nullptr);
            tm localTime;  

            localtime_s(&localTime, &now);

            ostringstream oss;
            oss << localTime.tm_year + 1900 << "-"
                << localTime.tm_mon + 1 << "-"
                << localTime.tm_mday << " "
                << localTime.tm_hour << ":"
                << localTime.tm_min << ":"
                << localTime.tm_sec;

            return oss.str();
        }

        bool authenticate(int p) {
            if (pin == p) {
                return true;
            }
        }

        void deposit(double amount) {
            if (amount <= 0) {
                cout << "Invalid amount! Must be greater than 0.\n";

            }
            balance += amount;
            string timestamp = getTimestamp();
            transactions.emplace_back("Deposit", amount, balance, timestamp);
            cout << "Deposit successful!\n";
        }

        void withdraw(double amount) {
            if (amount <= 0) {
                cout << "Invalid amount! Must be greater than 0.\n";

            }
            if (amount > balance) {
                cout << "Insufficient balance!\n";

            }
            balance -= amount;
            string timestamp = getTimestamp();
            transactions.emplace_back("Withdraw", amount, balance, timestamp);
            cout << "Withdrawal successful!\n";

        }

        void displayBalance() {
            cout << "Current Balance: $" << balance << endl;
        }

        void displayTransactions() {
            if (transactions.empty()) {
                cout << "No transactions available.\n";

            }
            cout << "Transaction History:\n";
            for (auto& t : transactions)
                cout << t.tranc_type << ": $" << t.amount << "\tCurrent Balance :" << t.balance << "\tTransaction time: " << t.timestamp << endl;
        }

        string getUserName() const { return userName; }
};
#endif // !ACCOUNT_H