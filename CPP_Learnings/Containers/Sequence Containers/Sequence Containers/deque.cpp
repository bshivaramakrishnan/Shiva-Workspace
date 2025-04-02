#include <iostream>
#include <deque>
using namespace std;

// Function to display deque elements
template <typename T>
void displayDeque(const deque<T>& dq) {
    for (const auto& elem : dq)
        cout << elem << " ";
    cout << "\n";
}

// Function to insert elements into the deque
void insertElements(deque<int>& dq) {
    int n, value;
    cout << "Enter number of elements to insert: ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        dq.push_back(value);
    }
}

// Function to remove an element from the deque
void removeElement(deque<int>& dq) {
    int value;
    cout << "Enter value to remove: ";
    cin >> value;
    dq.erase(remove(dq.begin(), dq.end(), value), dq.end());
}

// Function to sort the deque
void sortDeque(deque<int>& dq) {
    sort(dq.begin(), dq.end());
}

// Function to reverse the deque
void reverseDeque(deque<int>& dq) {
    reverse(dq.begin(), dq.end());
}

// Function to merge another deque
void mergeDeques(deque<int>& dq1, deque<int>& dq2) {
    dq1.insert(dq1.end(), dq2.begin(), dq2.end());
    dq2.clear();
}

int main() {
    deque<int> myDeque, anotherDeque;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert elements\n";
        cout << "2. Remove an element\n";
        cout << "3. Sort the deque\n";
        cout << "4. Reverse the deque\n";
        cout << "5. Display the deque\n";
        cout << "6. Merge another deque\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: insertElements(myDeque); break;
        case 2: removeElement(myDeque); break;
        case 3: sortDeque(myDeque); break;
        case 4: reverseDeque(myDeque); break;
        case 5: displayDeque(myDeque); break;
        case 6:
            cout << "Enter elements for another deque to merge: \n";
            insertElements(anotherDeque);
            mergeDeques(myDeque, anotherDeque);
            break;
        case 7: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}