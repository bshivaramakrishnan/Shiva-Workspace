#include<iostream>
#include<string>
using namespace std;

class Vector {
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
	Vector() {
		data = nullptr;
		size = 0;
		capacity = 0;
	}
	~Vector() { delete[] data; }
	void push_back(int x) {
		if (size == capacity) {
			resize();
		}
		data[size++] = x;
	}
	void pop_back() {
		if (size == 0) {
			cout << "Vector Already empty";

		}
		size--;
	}
	void remove(size_t x) {
		if (x >= size) {
			cout << "Error: Index out of bounds!\n";
			return;
		}

		for (size_t i = x; i < size - 1; ++i) {
			data[i] = data[i + 1];
		}

		size--;
	}
	void insert(int x, int y) {
		if (size == capacity) {
			resize();
		}
		for (size_t i = y; i < size; ++i) {
			data[i + 1] = data[i];
		}
		data[y] = x;
	}

	void display() {
		for (size_t i = 0; i < size; ++i) {
			cout << data[i] << " ";
		}cout << endl;
	}
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
	v1.insert(2, 3);
	v1.display();
	return 0;
}