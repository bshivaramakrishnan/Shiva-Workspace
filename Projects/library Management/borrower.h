#pragma once
#include "transaction.h"
#include "book.h"
using namespace std;

class Borrower {
private:
    vector<Transaction> transactions;
    unordered_map<int, Book*> borrowedBooks;

public:
    int userID;
    string name;
    string pin;
    double balance;

    Borrower(int id, string n, string p, double b) : userID(id), name(n), pin(p), balance(b) {}

    bool borrowBook(Book* book) {
        if (book->isAvailable && balance >= 10.0) {
            book->isAvailable = false;
            time_t now = time(nullptr);
            book->dueDate = now + 7 * 24 * 60 * 60;
            borrowedBooks[book->bookID] = book;
            transactions.emplace_back("Borrowed", book->bookID);
            balance -= 10.0;
            return true;
        }
        return false;
    }

    bool returnBook(int bookID) {
        if (borrowedBooks.find(bookID) != borrowedBooks.end()) {
            Book* book = borrowedBooks[bookID];
            book->isAvailable = true;
            time_t now = time(nullptr);
            if (now > book->dueDate) {
                double fine = difftime(now, book->dueDate) / (24 * 60 * 60) * 5.0;
                balance -= fine;
                cout << "Book is overdue. Fine of " << fine << " units applied.\n";
            }
            transactions.emplace_back("Returned", bookID);
            borrowedBooks.erase(bookID);
            return true;
        }
        return false;
    }

    void topUpBalance(double amount) {
        balance += amount;
    }

    void displayTransactions() const {
        for (const auto& transaction : transactions) {
            transaction.display();
        }
    }
    void displayBorrowedBooks() const {
        for (const auto& pair : borrowedBooks) {
            char buffer[26]; // ctime_s needs a buffer of at least 26 bytes
            ctime_s(buffer, sizeof(buffer), &pair.second->dueDate);
            cout << "Book ID: " << pair.second->bookID
                << ", Title: " << pair.second->title
                << ", Due Date: " << buffer;
        }
    }
};
