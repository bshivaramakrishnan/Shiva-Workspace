#include<iostream>
#include<string>
using namespace std;
class Student {
public:
    string name;
    Student(string s) :name(s) {};
    void out(){
        cout << "allocated names : " << name << endl;
    }
};
int main() {
    Student* students = new Student[2]{ Student("Shiva"),Student("Dhisha") };
    students[0].out();
    students[1].out();
        return 0;
}