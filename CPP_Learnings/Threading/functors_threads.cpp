#include<iostream>
#include<thread>

using namespace std;

class Overload {
public:
	void operator()(int x) {
		for (int i = 0; i < 100; i++) {
			cout <<"thread "<<x<< endl;
			this_thread::sleep_for(chrono::nanoseconds(5));
		}
	}
};
int main()
{
	Overload obj;
	thread thread1(obj, 1);
	thread thread2(obj, 2);
	thread1.join();
	thread2.join();

}