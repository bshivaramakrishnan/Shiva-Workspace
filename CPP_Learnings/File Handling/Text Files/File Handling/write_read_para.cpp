#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void writeToFile() {
	string para;
	string line;
	string name;
	cout << "Enter file name to Create file : ";
	cin >> name;
	fstream fileobj(name + ".txt",ios::out);
	if (!fileobj.is_open())
	{
		cout << "error opening file ";
	}
	cout << "Enter End to stop writing\n";
	while (true)
	{
		getline(cin, line);
		if (line == "END" || line == "end" || line == "End")
		{
			break;
		}
		para += line+"\n";
	}
	fileobj << para;
	fileobj.close();
	cout << "File Appended";
}
void readFromFile()
{
	string line;
	string name;
	cout << "Enter the file name to read";
	cin >> name;
	fstream obj(name + ".txt", ios::in);
		if (!obj.is_open()) {
			cout << "error opening file";
		}
		while (getline(obj, line)) {
			cout << line << endl;

		}
		obj.close();
	
}
int main() {
	int choice;
	cout << "1. Write to file\n2. Read from file\nEnter choice: ";
	cin >> choice;

	if (choice == 1)
		writeToFile();
	else if (choice == 2)
		readFromFile();
	else
		cout << "Invalid choice.\n";

	return 0;
}