#include<iostream>
#include<fstream>
#include<string>
#include<thread>
typedef unsigned long long ull;

using namespace std;

int main()
{
	string line;
	string para;
	ofstream obj("test1.txt");
	if (!obj.is_open())
	{
		cout << "Error opening File";
	}
	for(ull i=0;i<200000000;i++)

}