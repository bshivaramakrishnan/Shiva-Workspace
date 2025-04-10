#include<iostream>
#include<fstream>

using namespace std;

void write() 
{
	int arr[10];
	cout << "Enter the elements of the array";
	for (int i = 0; i < 10; i++) {
		cin >> arr[i];
	}
	ofstream obj("array.bin", ios::binary);
	obj.write(reinterpret_cast<char*>(&arr), sizeof(arr));
	obj.close();
	cout << "Array written succefully";
}
void read() 
{
	int arr[10];
	ifstream obj("array.bin", ios::binary);
	obj.read(reinterpret_cast<char*>(&arr), sizeof(arr));
	obj.close();
	for (int i = 0; i < 10; i++) {
		cout << "Array element : " << i  <<" ->  " << arr[i] << "\n";
	}

}
int main()
{
	
	int choice;
	cout << "1: Write\n";
	cout << "2: Read\n";
	cin >> choice;
	switch (choice) {
	case 1: {
		write();
		break; }
	case 2:
	{read();
	break; }
	}
	return 0;
}