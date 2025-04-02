#include <iostream>
using namespace std;

class Vector {
private:
    int* data;
    size_t size;
    size_t capacity;

    void resize() {
        capacity = (capacity == 0) ? 1 : capacity + 16;
        int* newdata = new int[capacity];

        for (size_t i = 0; i < size; ++i) {
            newdata[i] = data[i];
        }

        delete[] data;
        data = newdata;
    }

public:
    
    Vector() : data(nullptr), size(0), capacity(0) {}

    
    ~Vector() {
        delete[] data;
    }

    void push_back(int element) {
        if (size == capacity) {
            resize();
        }
        data[size++] = element;
    }

    void pop_back() {
        if (size == 0) {
            cout << "Vector is already empty\n";
            return;
        }
        size--;
    }

    void remove(size_t element) {
        if (element >= size) {
            cout << "Error: Index out of bounds!\n";
            return;
        }

        for (size_t i = element; i < size - 1; ++i) {
            data[i] = data[i + 1];
        }

        size--;
    }

    void insert(size_t index, int element) {
        if (index > size) {
            cout << "Error: Index out of bounds!\n";
            return;
        }

        if (size == capacity) {
            resize();
        }

        for (size_t i = size; i > index; --i) {
            data[i] = data[i - 1];
        }

        data[index] = element;
        size++;
    }

    void display() {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }

    size_t get_size() const { return size; }
};

int main() {
    Vector v1;
    v1.push_back(10);
    v1.push_back(20);
    v1.display();  

    v1.push_back(30);
    v1.push_back(40);
    v1.display();  

    v1.pop_back();
    v1.display();  

    v1.remove(2);
    v1.display();  

    v1.insert(1, 99);
    v1.display(); 

    return 0;
}
