#include <iostream>
#include<vector>
using namespace std;

int main() {
    int* data = new int[10];

    cout << "Enter integers: ";
    for (int i = 0; i < 5; i++) {
        cin >> data[i];
    }

   

    delete[] data; 
    return 0;
}
