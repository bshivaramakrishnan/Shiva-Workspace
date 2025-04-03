#include<iostream>

using namespace std;

class vector {
	int* data;
	size_t size;
	size_t capacity;
public: 
	void resize() {
		capacity = (capacity == 0) ? 1 : capacity + 16;
		int* newdata = new int[capacity];
		for (size_t i = 0; i < size; ++i) {
			newdata[i] = data[i];

		}
		delete[] data;
		data = newdata;

	}
};