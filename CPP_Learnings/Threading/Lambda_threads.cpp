#include<iostream>
#include<thread>

using namespace std;

int main()
{
	int a = 200;
	auto thread1 = [a](int x) ->int {for (int i = 0; i < a; i++) { cout << "Iteration" << i * x<<endl; }
	this_thread::sleep_for(chrono::nanoseconds(10)); return 0; };

	thread thread_obj1(thread1, 10);
	thread thread_obj2(thread1, 1);

	thread_obj1.join();
	thread_obj2.join();
}