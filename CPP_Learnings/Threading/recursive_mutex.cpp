#include<iostream>
#include<fstream>
#include<mutex>

using namespace std;

recursive_mutex mtx;
int buffer = 0;

void recurs(int c,int x)
{
	if (x < 0) return;
	mtx.lock();
	++buffer;
	cout << "thread  ID: " << c << "\tExecuting" << "buffer value : " << buffer << endl;
	recurs(c, --x);
	mtx.unlock();
	cout << "unlocked by Thread : " << c<<endl;
}
int main()
{
	thread t1(recurs, 1, 10);
	thread t2(recurs, 2, 10);
	t1.join();
	t2.join();
}
