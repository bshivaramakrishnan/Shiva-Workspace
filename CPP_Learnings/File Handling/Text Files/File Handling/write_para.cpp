#include<iostream>
#include<string>
#include<fstream>

using namespace std;

void read() {
	string para;
	string line;
	string name;
	cout << "Enter file name to Create file : ";
	cin >> name;
	ofstream fileobj(name + ".txt");
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
			para += line;
		}
		fileobj << para;
		cout << "File Appended";
