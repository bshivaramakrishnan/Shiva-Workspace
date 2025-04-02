#include <iostream>
#include <forward_list>
using namespace std;

// Function to display forward_list elements
template <typename T>
void displayForwardList(const forward_list<T>& fl) {
    for (const auto& elem : fl)
        cout << elem << " ";
    cout << "\n";
}

// Function to insert elements into the forward_list
void insertElements(forward_list<int>& fl) {
    int n, value;
    cout << "Enter number of elements to insert: ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        fl.push_front(value); // Insert at front because forward_list doesn't support push_back
    }
    fl.reverse(); // Reverse to maintain input order
}

// Function to remove an element from the forward_list
void removeElement(forward_list<int>& fl) {
    int value;
    cout << "Enter value to remove: ";
    cin >> value;
    fl.remove(value);
}

// Function to sort the forward_list
void sortForwardList(forward_list<int>& fl) {
    fl.sort();
}

// Function to reverse the forward_list
void reverseForwardList(forward_list<int>& fl) {
    fl.reverse();
}

// Function to merge two forward_lists
void mergeForwardLists(forward_list<int>& fl1, forward_list<int>& fl2) {
    fl1.merge(fl2);
}

int main() {
    forward_list<int> myForwardList, anotherForwardList;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert elements\n";
        cout << "2. Remove an element\n";
        cout << "3. Sort the forward_list\n";
        cout << "4. Reverse the forward_list\n";
        cout << "5. Display the forward_list\n";
        cout << "6. Merge another forward_list\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: insertElements(myForwardList); break;
        case 2: removeElement(myForwardList); break;
        case 3: sortForwardList(myForwardList); break;
        case 4: reverseForwardList(myForwardList); break;
        case 5: displayForwardList(myForwardList); break;
        case 6:
            cout << "Enter elements for another forward_list to merge: \n";
            insertElements(anotherForwardList);
            mergeForwardLists(myForwardList, anotherForwardList);
            break;
        case 7: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}