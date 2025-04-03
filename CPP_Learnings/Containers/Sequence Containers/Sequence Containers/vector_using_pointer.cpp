#include <iostream>
#include <vector>
using namespace std;

int main() {
  
    vector<int> vec = { 10, 20, 30, 40, 50 };

    
    int* ptr = &vec[0];

   
    cout << "Vector elements using pointer: ";
    for (size_t i = 0; i < vec.size(); i++) {
        cout << *(ptr + i) << " ";  
    }
    cout << endl;

    
    *(ptr + 2) = 100;  

    cout << "Vector after modification: ";
    for (int val : vec) {
      cout << val << " ";
    }
    cout << endl;

    
    cout << "Accessing elements using pointer iteration: ";
    for (int* it = &vec[0]; it != &vec[0] + vec.size(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    
    cout << "Using vector iterator: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << endl;

    return 0;
}