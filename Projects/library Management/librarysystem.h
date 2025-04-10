#pragma once
#include "librarian.h"

class LibrarySystem {
private:
    unordered_map<int, Book*> books;
    unordered_map<int, Borrower*> borrowers;
    Librarian librarian;

public:
    ~LibrarySystem() {
        for (auto& pair : books) delete pair.second;
        for (auto& pair : borrowers) delete pair.second;
    }

    void addBorrower(int id, string name, string pin, double balance) {
        borrowers[id] = new Borrower(id, name, pin, balance);
    }

    Borrower* authenticateBorrower(int id, string pin) {
        if (borrowers.find(id) != borrowers.end() && borrowers[id]->pin == pin) {
            return borrowers[id];
        }
        return nullptr;
    }

    void borrowerMenu(Borrower* borrower) {
        int choice;
        do {
            cout << "\n1. View Available Books\n2. Borrow Book\n3. Return Book\n4. View Transactions\n5. Top-Up Balance\n6. Logout\nEnter choice: ";
            cin >> choice;
            switch (choice) {
            case 1:
                for (const auto& pair : books) {
                    if (pair.second->isAvailable) {
                        cout << "Book ID: " << pair.second->bookID << ", Title: " << pair.second->title << ", Author: " << pair.second->author << endl;
                    }
                }
                break;
            case 2: {
                int bookID;
                cout << "Enter Book ID to borrow: ";
                cin >> bookID;
                if (books.find(bookID) != books.end()) {
                    if (borrower->borrowBook(books[bookID])) {
                        cout << "Book borrowed successfully.\n";
                    }
                    else {
                        cout << "Unable to borrow book. Check availability or balance.\n";
                    }
                }
                else {
                    cout << "Invalid Book ID.\n";
                }
                break;
            }
            case 3: {
                int bookID;
                cout << "Enter Book ID to return: ";
                cin >> bookID;
                if (borrower->returnBook(bookID)) {
                    cout << "Book returned successfully.\n";
                }
                else {
                    cout << "You haven't borrowed this book.\n";
                }
                break;
            }
            case 4:
                borrower->displayTransactions();
                break;
            case 5: {
                double amount;
                cout << "Enter amount to top up: ";
                cin >> amount;
                borrower->topUpBalance(amount);
                cout << "Balance topped up successfully. New balance: " << fixed << setprecision(2) << borrower->balance << endl;
                break;
            }
            case 6:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 6);
    }

    void librarianMenu() {
        int choice;
        do {
            cout << "\n--- Librarian Menu ---\n";
            cout << "1. View All Borrowers\n2. Add Book\n3. Modify Book\n4. Delete Book\n5. Logout\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1:
                librarian.viewAllBorrowers(borrowers);
                break;
            case 2: {
                int id;
                string title, author;
                cout << "Enter Book ID: ";
                cin >> id;
                cin.ignore();
                cout << "Enter Title: ";
                getline(cin, title);
                cout << "Enter Author: ";
                getline(cin, author);
                librarian.addBook(books, id, title, author);
                cout << "Book added successfully.\n";
                break;
            }
            case 3: {
                int id;
                cout << "Enter Book ID to modify: ";
                cin >> id;
                if (books.find(id) != books.end()) {
                    string newTitle, newAuthor;
                    cin.ignore();
                    cout << "Enter new Title: ";
                    getline(cin, newTitle);
                    cout << "Enter new Author: ";
                    getline(cin, newAuthor);
                    librarian.modifyBook(books[id], newTitle, newAuthor);
                    cout << "Book details updated.\n";
                }
                else {
                    cout << "Book ID not found.\n";
                }
                break;
            }
            case 4: {
                int id;
                cout << "Enter Book ID to delete: ";
                cin >> id;
                if (books.find(id) != books.end()) {
                    librarian.deleteBook(books, id);
                    cout << "Book deleted successfully.\n";
                }
                else {
                    cout << "Book ID not found.\n";
                }
                break;
            }
            case 5:
                cout << "Logging out...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 5);
    }

    void mainMenu() {
        int choice;
        do {
            cout << "\n--- Library System ---\n";
            cout << "1. Borrower Login\n2. Librarian Login\n3. Exit\nEnter choice: ";
            cin >> choice;

            switch (choice) {
            case 1: {
                int id;
                string pin;
                cout << "Enter Borrower ID: ";
                cin >> id;
                cout << "Enter PIN: ";
                cin >> pin;
                Borrower* borrower = authenticateBorrower(id, pin);
                if (borrower) {
                    borrowerMenu(borrower);
                }
                else {
                    cout << "Invalid credentials.\n";
                }
                break;
            }
            case 2:
                librarianMenu();
                break;
            case 3:
                cout << "Exiting system...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
            }
        } while (choice != 3);
    }
}; 
