#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int val) : data(val), next(nullptr) {}
};
class linkedl {
private:
    Node* head;
public:
    linkedl() :head(nullptr) {}
    void insert(int value) {
        node* new node = mew Node(Value);
        if (head == nullptr) {
            head = new node;
            return;
            Void delete()
                Nde
        }
    }
};
class doublyLinkedList() {
    
}

class LinkedList {
private:
    Node* head;

public:
    LinkedList() : head(nullptr) {} 

    void insert(int value) {
        Node* newNode = new Node(value);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " -> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }

    ~LinkedList() {
        Node* temp;
        while (head != nullptr) {
            temp = head;
            head = head->next;
            delete temp;
        }
    }
};
int main() {
    LinkedList list;
    list.insert(10);
    list.insert(20);
    list.insert(30);

    cout << "Linked List: ";
    list.display();  
    return 0;
}
