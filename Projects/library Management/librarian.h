#pragma once
#include "borrower.h"

class Librarian {
public:
    void viewAllBorrowers(const unordered_map<int, Borrower*>& borrowers) const {
        for (const auto& pair : borrowers) {
            cout << "User ID: " << pair.second->userID << ", Name: " << pair.second->name << ", Balance: " << fixed << setprecision(2) << pair.second->balance << endl;
            pair.second->displayBorrowedBooks();
            cout << "-----------------------" << endl;
        }
    }

    void addBook(unordered_map<int, Book*>& books, int id, string title, string author) {
        books[id] = new Book(id, title, author);
    }

    void modifyBook(Book* book, string newTitle, string newAuthor) {
        book->title = newTitle;
        book->author = newAuthor;
    }

    void deleteBook(unordered_map<int, Book*>& books, int id) {
        delete books[id];
        books.erase(id);
    }
};
