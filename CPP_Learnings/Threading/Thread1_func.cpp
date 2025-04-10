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
void run2(string s,int x)
{
	for (int i = 0; i < x; i++) {
		cout << string << "\t" << x<<endl;
	}
}
int main()
{
	thread thread_obj1(run1, 20);
	thread thread_obj2(run2,"hello",20);
	thread_obj1.join();
	thread_obj2.join();
}