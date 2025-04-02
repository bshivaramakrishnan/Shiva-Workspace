#include <iostream>
#include <queue>
using namespace std;

void displayQueue(queue<int> q) {
    cout << "Queue contents (front to back): ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;
}

int main() {
    queue<int> q;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Enqueue (Push)\n";
        cout << "2. Dequeue (Pop)\n";
        cout << "3. Display front element\n";
        cout << "4. Display all elements\n";
        cout << "5. Check if queue is empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to enqueue: ";
            cin >> value;
            q.push(value);
            cout << value << " enqueued into the queue.\n";
            break;
        }
        case 2: {
            if (q.empty()) {
                cout << "Queue is empty, cannot dequeue!\n";
            }
            else {
                cout << "Dequeued element: " << q.front() << endl;
                q.pop();
            }
            break;
        }
        case 3: {
            if (q.empty()) {
                cout << "Queue is empty!\n";
            }
            else {
                cout << "Front element: " << q.front() << endl;
            }
            break;
        }
        case 4: {
            if (q.empty()) {
                cout << "Queue is empty!\n";
            }
            else {
                displayQueue(q);
            }
            break;
        }
        case 5: {
            cout << (q.empty() ? "Queue is empty.\n" : "Queue is not empty.\n");
            break;
        }
        case 6: {
            cout << "Exiting program.\n";
            break;
        }
        default:
            cout << "Invalid choice, please try again.\n";
        }
    } while (choice != 6);

    return 0;
}
