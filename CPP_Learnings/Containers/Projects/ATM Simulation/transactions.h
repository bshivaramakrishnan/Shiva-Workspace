#include <iostream>
#include <map>
#include <vector>
#include<chrono>
#include<ctime>
#include<sstream>
#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

using namespace std;

class Transaction {
    
    public:
        string tranc_type;
        double amount;
        double balance;
        string timestamp;
        Transaction(string type, double amount, double balance, string timestamp) : tranc_type(type), amount(amount), balance(balance), timestamp(timestamp) {}
};
#endif  