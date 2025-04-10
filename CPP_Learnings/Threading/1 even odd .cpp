#include<iostream>
#include<thread>
#include<chrono>
typedef unsigned long long ull;

using namespace std;

void evensum()
{
	ull count = 0;
	for (ull i = 0; i < 200; i++)
	{
		if (i % 2 == 0) 
		{
			count += i;
		}
	}
	cout << "even Sum : " << count;
}
void oddsum()
{
	ull count = 0;
	for (ull i=0; i < 200; i++)
	{
		if (i % 2 != 0)
		{
			count+=i;
		}
	}
	cout << "odd Sum : " << count;
}
int main()
{
	thread t1(evensum);
	thread t2(oddsum);
	t1.join();
	t2.join();
	return 0;
}