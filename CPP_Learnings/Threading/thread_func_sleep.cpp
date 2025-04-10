#include<iostream>
#include<thread>
#include<string>
#include<chrono>

using namespace std;

void run1(int x)
{
	for (int i = 0; i < x; i++)
	{
		cout << i << "\n";

	}
	this_thread::sleep_for(chrono::nanoseconds(10));
}
void run2(string s, int x)
{
	for (int i = 0; i < x; i++) {
		cout << s << "\t" << i << endl;
	}
	this_thread::sleep_for(chrono::nanoseconds(10));
}
int main()
{
	thread thread_obj1(run1, 200);
	thread thread_obj2(run2, "hello", 200);
	thread_obj1.join();
	thread_obj2.join();
}