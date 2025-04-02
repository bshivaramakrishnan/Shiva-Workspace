#include <iostream>
#include <list>
using namespace std;

// Function to display list elements
template <typename T>
void displayList(const list<T>& lst) {
    for (const auto& elem : lst)
        cout << elem << " ";
    cout << "\n";
}

// Function to insert elements into the list
void insertElements(list<int>& lst) {
    int n, value;
    cout << "Enter number of elements to insert: ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        lst.push_back(value);
    }
}

// Function to remove an element from the list
void removeElement(list<int>& lst) {
    int value;
    cout << "Enter value to remove: ";
    cin >> value;
    lst.remove(value);
}

// Function to sort the list
void sortList(list<int>& lst) {
    lst.sort();
}

// Function to reverse the list
void reverseList(list<int>& lst) {
    lst.reverse();
}

// Function to merge two lists
void mergeLists(list<int>& lst1, list<int>& lst2) {
    lst1.merge(lst2);
}

// Function to splice elements from one list to another
void spliceLists(list<int>& lst1, list<int>& lst2) {
    lst1.splice(lst1.end(), lst2);
}

int main() {
    list<int> myList, anotherList;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert elements\n";
        cout << "2. Remove an element\n";
        cout << "3. Sort the list\n";
        cout << "4. Reverse the list\n";
        cout << "5. Display the list\n";
        cout << "6. Merge another list\n";
        cout << "7. Splice another list\n";
        cout << "8. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: insertElements(myList); break;
        case 2: removeElement(myList); break;
        case 3: sortList(myList); break;
        case 4: reverseList(myList); break;
        case 5: displayList(myList); break;
        case 6:
            cout << "Enter elements for another list to merge: \n";
            insertElements(anotherList);
            mergeLists(myList, anotherList);
            break;
        case 7:
            cout << "Enter elements for another list to splice: \n";
            insertElements(anotherList);
            spliceLists(myList, anotherList);
            break;
        case 8: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 8);

    return 0;
}