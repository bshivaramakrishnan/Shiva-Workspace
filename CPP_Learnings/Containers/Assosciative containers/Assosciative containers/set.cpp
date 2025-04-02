#include <iostream>
#include <set>
using namespace std;

template <typename T>
void displaySet(const set<T>& s) {
    for (const auto& elem : s)
        cout << elem << " ";
    cout << "\n";
}

void insertElements(set<int>& s) {
    int n, value;
    cout << "Enter number of elements to insert: ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        s.insert(value);
    }
}
void removeElement(set<int>& s) {
    int value;
    cout << "Enter value to remove: ";
    cin >> value;
    s.erase(value);
}
void findElement(const set<int>& s) {
    int value;
    cout << "Enter value to find: ";
    cin >> value;
    if (s.find(value) != s.end())
        cout << "Element found!\n";
    else
        cout << "Element not found.\n";
}
void mergeSets(set<int>& s1, const set<int>& s2) {
    s1.insert(s2.begin(), s2.end());
}

int main() {
    set<int> mySet, anotherSet;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert elements\n";
        cout << "2. Remove an element\n";
        cout << "3. Find an element\n";
        cout << "4. Display the set\n";
        cout << "5. Merge another set\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: insertElements(mySet); break;
        case 2: removeElement(mySet); break;
        case 3: findElement(mySet); break;
        case 4: displaySet(mySet); break;
        case 5:
            cout << "Enter elements for another set to merge: \n";
            insertElements(anotherSet);
            mergeSets(mySet, anotherSet);
            break;
        case 6: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 6);

    return 0;
}