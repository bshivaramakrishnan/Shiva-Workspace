#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to display vector elements
template <typename T>
void displayVector(const vector<T>& vec) {
    for (const auto& elem : vec)
        cout << elem << " ";
    cout << "\n";
}

// Function to insert elements into the vector
void insertElements(vector<int>& vec) {
    int n, value;
    cout << "Enter number of elements to insert: ";
    cin >> n;
    cout << "Enter " << n << " elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> value;
        vec.push_back(value);
    }
}

// Function to remove an element from the vector
void removeElement(vector<int>& vec) {
    int value;
    cout << "Enter value to remove: ";
    cin >> value;
    vec.erase(remove(vec.begin(), vec.end(), value), vec.end());
}

// Function to sort the vector
void sortVector(vector<int>& vec) {
    sort(vec.begin(), vec.end());
}

// Function to reverse the vector
void reverseVector(vector<int>& vec) {
    reverse(vec.begin(), vec.end());
}

// Function to merge two vectors
void mergeVectors(vector<int>& vec1, vector<int>& vec2) {
    vec1.insert(vec1.end(), vec2.begin(), vec2.end());
    vec2.clear();
}

int main() {
    vector<int> myVector, anotherVector;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Insert elements\n";
        cout << "2. Remove an element\n";
        cout << "3. Sort the vector\n";
        cout << "4. Reverse the vector\n";
        cout << "5. Display the vector\n";
        cout << "6. Merge another vector\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: insertElements(myVector); break;
        case 2: removeElement(myVector); break;
        case 3: sortVector(myVector); break;
        case 4: reverseVector(myVector); break;
        case 5: displayVector(myVector); break;
        case 6:
            cout << "Enter elements for another vector to merge: \n";
            insertElements(anotherVector);
            mergeVectors(myVector, anotherVector);
            break;
        case 7: cout << "Exiting...\n"; break;
        default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
