#include<iostream>

using namespace std;

struct student {
	string name;
	int age;
};
int main() {
	student* s = new student{ "Shiva", 22 };
	cout << s->age << endl;
	cout << s->name << endl;
	s->age = 230;
	cout << s->age;
	student* s1[3];

	s1[0] = new student{ "Shiva", 22 };
	s1[1] = new student{ "Krishna", 24 };
	s1[2] = new student{ "Arjuna", 21 };

	for (int i = 0; i < 3; i++) {
		cout << s1[i]->name << " - " << s1[i]->age << endl;
		delete s1[i];
	}

}
