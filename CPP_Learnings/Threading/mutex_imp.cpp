#include<iostream>
#include<thread>
#include<mutex>
std::mutex mtx;
std::mutex tx;
typedef unsigned long long ull;
ull counter1 = 0;
ull counter11 = 0;

using namespace std;

void counter() {
	
	for (ull i = 0; i < 2000000; i++)
	{
		if (mtx.try_lock())
		{
			counter1++;
			mtx.unlock();
		}
		
	}
	cout << counter1<<endl;
}
void counter2() {
	for (ull i = 0; i < 2000000; i++)
	{
		tx.lock();
		counter11++;	
		tx.unlock();
	}
	cout << counter11<<endl;
}
int main() 
{
	thread t(counter);
	thread t2(counter2);
	thread t3(counter);
	thread t4(counter2);
	t.join();
	t2.join();
	t3.join();
	t4.join();
}