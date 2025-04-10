#include<iostream>
#include<mutex>
#include<condition_variable>

using namespace std;

mutex mtx;
condition_variable cv;
int buffer=200;
void ping()
{
	while (buffer >= 1) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [] {return (buffer % 2 != 0) ? true : false; });
		--buffer;
		cout << "PING" << endl;
		cv.notify_one();
	}
}
void pong()
{
	while (buffer >= 0) {
		unique_lock<mutex> lock(mtx);
		cv.wait(lock, [] {return (buffer % 2 == 0) ? true : false; });
		--buffer;
		cout << "PONG" << endl;
		cv.notify_one(); 
	}
}
int main()
{
	thread t1(ping);
	thread t2(pong);
	t1.join();
	t2.join();
}