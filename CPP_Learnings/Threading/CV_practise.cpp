#include<iostream>
#include<condition_variable>
#include<mutex>
#include<chrono>
#include<thread>

using namespace std;

mutex mtx;
condition_variable cv;
long balance = 0; 

void deposit(int money) 
{
	cout << "...........Deposit Money...........\n";
	lock_guard<mutex> lock(mtx);
	balance += money;
	cout << "Money Deposited :\t" << money << "\tAvailable Balance :\t" << balance << endl;
	cv.notify_one();
	
}
void withdraw(int money)
{
	cout << "..........Withdrawal............\n";
	unique_lock<mutex> lock(mtx);
	cv.wait(lock, [] { return balance != 0; });
	if (balance < money)
	{
		cout << "Insufficient Funds";
	}
	else balance -= money;
	cout << "Money Withdrawn :\t" << money << "\tAvailable Balance :\t" << balance << endl;
}
int main()
{
	thread t1(deposit, 100000);
	thread t2(withdraw, 1000);
	t1.join();
	t2.join();
}