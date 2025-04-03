#include <iostream>
#include <list>
#include <string>

using namespace std;

void splice(list<int>* l1, int index, list<int>* l2) {
    auto it = l1->begin();
    advance(it, index);
    l1->splice(it, *l2);
}

void insert(list<int>* l1, int index) {
    auto it = l1->begin();
    advance(it, index);
    l1->insert(it, 100);
}

void inserts(list<string>* l1, int index, string y) {
    auto it = l1->begin();
    advance(it, index);
    l1->insert(it, y);
}

void displays(list<string>* l1) {
    cout << "Displaying list of strings: ";
    for (string i : *l1) {
        cout << i << " ";
    }
    cout << endl;
}

void display(list<int>* l1) {
    cout << "Displaying list of integers: ";
    for (int i : *l1) {
        cout << i << " ";
    }
    cout << endl;
}

int main() {
    list<int> list1 = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    list<int> list4 = { 100, 200, 300, 400 };
    list<int> list3 = { 10, 20, 30, 40, 50, 60, 70, 80, 90 };
    list<string> list2 = { "Hello", "world", "Hello1", "Hello world" };

    cout << "Inserting 100 at index 2 in list1." << endl;
    insert(&list1, 2);
    cout << "Adding elements to front and back of list1." << endl;
    list1.push_back(100);
    list1.push_front(200);
    display(&list1);

    cout << "Removing elements from front and back of list1." << endl;
    list1.pop_back();
    list1.pop_front();
    display(&list1);

    cout << "Checking if list1 is empty: " << list1.empty() << endl;
    cout << "Size of list1: " << list1.size() << endl;
    cout << "Max size of list1: " << list1.max_size() << endl;

    cout << "Reversing list1." << endl;
    list1.reverse();
    display(&list1);

    cout << "Inserting 'Shiva' at index 2 in list2." << endl;
    inserts(&list2, 2, "Shiva");
    displays(&list2);

    cout << "Sorting list1 and list2." << endl;
    list1.sort();
    list2.sort();
    display(&list1);
    displays(&list2);

    cout << "Merging list3 into list1." << endl;
    list1.merge(list3);
    display(&list1);

    cout << "Splicing list4 into list1 at index 3." << endl;
    splice(&list1, 3, &list4);
    display(&list1);

    cout << "Displaying list3 (should be empty):" << endl;
    display(&list3);
    cout << "Checking if list3 is empty: " << list3.empty() << endl;
}
