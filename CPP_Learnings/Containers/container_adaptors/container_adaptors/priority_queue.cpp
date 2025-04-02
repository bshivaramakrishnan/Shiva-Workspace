#include <iostream>
#include <queue>
using namespace std;

void displayPQ(priority_queue<int> pq) {
    cout << "Priority Queue Contents (largest to smallest): ";
    while (!pq.empty()) {
        cout << pq.top() << " ";
        pq.pop();
    }
    cout << endl;
}

int main() {
    priority_queue<int> pq;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Display top element\n";
        cout << "4. Display all elements\n";
        cout << "5. Check if priority queue is empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to push: ";
            cin >> value;
            pq.push(value);
            cout << value << " pushed into the priority queue.\n";
            break;
        }
        case 2: {
            if (pq.empty()) {
                cout << "Priority queue is empty, nothing to pop!\n";
            }
            else {
                cout << "Popped element: " << pq.top() << endl;
                pq.pop();
            }
            break;
        }
        case 3: {
            if (pq.empty()) {
                cout << "Priority queue is empty!\n";
            }
            else {
                cout << "Top element: " << pq.top() << endl;
            }
            break;
        }
        case 4: {
            if (pq.empty()) {
                cout << "Priority queue is empty!\n";
            }
            else {
                displayPQ(pq);
            }
            break;
        }
        case 5: {
            cout << (pq.empty() ? "Priority queue is empty.\n" : "Priority queue is not empty.\n");
            break;
        }
        case 6: {
            cout << "Exiting program.\n";
            break;
        }
        default: {
            cout << "Invalid choice, please try again.\n";
            break;
        }
        }
    } while (choice != 6);

    return 0;
}
