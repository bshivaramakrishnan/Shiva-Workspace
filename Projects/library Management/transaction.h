#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iomanip>

using namespace std;
class Transaction {
public:
    string type;
    int bookID;
    time_t timestamp;

    Transaction(string t, int id) : type(t), bookID(id) {
        timestamp = time(nullptr);
    }

    void display() const {
        char buffer[26];
        ctime_s(buffer, sizeof(buffer), &timestamp);
        cout << type << " Book ID: " << bookID << " on " << buffer;;
    }
};