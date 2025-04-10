#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {
    map<int, string> m;
    map<i

    m[1] = "Shiva";
    m[2] = "Dhisha";
    m[3] = "Hello";

    for (const auto& pair : m) {
        cout << "Key: " << pair.first << " Name: " << pair.second << "\n";
    }

    return 0;
}
