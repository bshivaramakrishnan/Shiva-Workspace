#include<iostream>
#include<mutex>
#include<thread>
#include<condition_variable>

using namespace std;

condition_variable cv;
long balance;
mutex mtx;

void withdraw(int amount)
{
	cout << "..............Withdrawal...........\n";
	unique_lock <mutex> lock(mtx);
	cv.wait(lock, [] { return (balance != 0) ? true : false; });
	if (amount > balance)
	{
		cout << "Insufficient Balance ";
	}
	else
	{
		balance -= amount;
		cout << "Amount Withdrawn:\t" << amount << "\t Available Balance:\t" << balance << endl;
	}
	cv.notify_one();
}
void deposit(int amount)
{
	cout << "..............Deposit...........\n" ;
	unique_lock<mutex> lock(mtx);
	balance += amount;
	cout << "Amount Deposited\t" << amount << "\tAvailable Balance : \t" << balance<< endl;
	cv.notify_one();
}

int main()
{
	thread t1(deposit, 1000000);
	thread t2(withdraw, 13342);
	t1.join();
	t2.join();
}