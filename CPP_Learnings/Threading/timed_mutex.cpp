#include<iostream>
#include<fstream>
#include<chrono>
#include<mutex>

using namespace std;

std::timed_mutex mtx;
int amt = 0;

void test(int i)
{
	if (mtx.try_lock_for(chrono::seconds(2)))
	{
		++amt;
		cout << "amount Incremented by thread : " << i << endl;
		this_thread::sleep_for(chrono::seconds(1));
		mtx.unlock();
	}
	else cout << "Thread ID : " << i << "\tDidnt Access Critical Resource"<<endl;
}

void main()
{
	thread t1(test, 1);
	thread t2(test, 2);
	t1.join();
	t2.join();
	cout << "total amount :"<<amt;
}