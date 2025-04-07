#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <ctime>
#include <iomanip>

using namespace std;
class Book {
public:
    int bookID;
    string title;
    string author;
    bool isAvailable;
    time_t dueDate;

    Book(int id, string t, string a) : bookID(id), title(t), author(a), isAvailable(true), dueDate(0) {}
};
