#include <iostream>
#include <stack>
using namespace std;

void displayStack(stack<int> s) {
    cout << "Stack contents (top to bottom): ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

int main() {
    stack<int> st;
    int choice;

    do {
        cout << "\nMenu:\n";
        cout << "1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Display top element\n";
        cout << "4. Display all elements\n";
        cout << "5. Check if stack is empty\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            int value;
            cout << "Enter value to push: ";
            cin >> value;
            st.push(value);
            cout << value << " pushed onto the stack.\n";
            break;
        }
        case 2: {
            if (st.empty()) {
                cout << "Stack is empty, cannot pop!\n";
            }
            else {
                cout << "Popped element: " << st.top() << endl;
                st.pop();
            }
            break;
        }
        case 3: {
            if (st.empty()) {
                cout << "Stack is empty!\n";
            }
            else {
                cout << "Top element: " << st.top() << endl;
            }
            break;
        }
        case 4: {
            if (st.empty()) {
                cout << "Stack is empty!\n";
            }
            else {
                displayStack(st);
            }
            break;
        }
        case 5: {
            cout << (st.empty() ? "Stack is empty." : "Stack is not empty.") << endl;
            break;
        }
        case 6: {
            cout << "Exiting program.\n";
            break;
        }
        default:
            cout << "Invalid choice, try again.\n";
        }
    } while (choice != 6);

    return 0;
}
