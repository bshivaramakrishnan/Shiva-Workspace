#include<iostream>
#include<thread>
#include<string>

using namespace std;

void run1(int x)
{
	for (int i = 0; i < x; i++)
	{
		cout << i << "\n";
	}
}
void run2(string s, int x)
{
	for (int i = 0; i < x; i++) {
		cout << s << "\t" << i << endl;
	}
}
int main()
{
	thread thread_obj1(run1, 200);
	thread thread_obj2(run2, "hello", 200);
	thread_obj1.join();
	thread_obj2.join();
}