/*
Thread Sleep Timer

Problem: Start 5 threads. Each thread should:

    Sleep for a different amount of seconds (e.g., 1s, 2s, ..., 5s)

    Print its thread ID and wake-up time.
*/
#include<iostream>
#include<thread>
#include<chrono>
#include<mutex>

using namespace std;
mutex mtx;

void sleepthread(int seconds)
{
    lock_guard<mutex> lock(mtx);
    cout << "Starting sleep for Thread" << this_thread::get_id() << endl;
    cout << "Sleeping for :  " << seconds << "  Seconds;" << endl;
    this_thread::sleep_for(chrono::seconds(seconds));
}
int main()
{
    thread t1(sleepthread,2);
    thread t2(sleepthread,3);
    thread t3(sleepthread,4);
    thread t4(sleepthread,5);
    thread t5(sleepthread,6);
    t1.join();
    t2.join();
    t3.join();
    t4.join();
    t5.join();
}