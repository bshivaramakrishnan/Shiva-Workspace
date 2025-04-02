#include <iostream>
#include <map>
#include <string>

using namespace std;

void displayMap(const map<int, string>& students) {
    cout << "\nCurrent Map Contents:\n";
    for (const auto& pair : students) {
        cout << pair.first << " -> " << pair.second << endl;
    }
    cout << "---------------------------\n";
}

int main() {
    map<int, string> students;
    students[101] = "Alice";
    students.insert({ 102, "Bob" });
    students.emplace(103, "Charlie");

    displayMap(students);

    int searchKey = 102;
    auto it = students.find(searchKey);
    if (it != students.end()) {
        cout << "Found: " << searchKey << " -> " << it->second << endl;
    }
    else {
        cout << "Key " << searchKey << " not found!\n";
    }

    students[102] = "Bob Updated";
    cout << "\nAfter updating key 102:\n";
    displayMap(students);

    students.erase(103);
    cout << "After deleting key 103:\n";
    displayMap(students);

    int checkKey = 105;
    if (students.count(checkKey) > 0) {
        cout << "Key " << checkKey << " exists.\n";
    }
    else {
        cout << "Key " << checkKey << " does not exist.\n";
    }

    cout << "\nTotal number of elements in map: " << students.size() << endl;

    students.clear();
    cout << "\nAfter clearing, is map empty? " << boolalpha << students.empty() << endl;

    return 0;
}
