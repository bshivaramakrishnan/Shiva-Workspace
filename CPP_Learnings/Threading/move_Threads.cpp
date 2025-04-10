#include <iostream>
#include <thread>
using namespace std;

void hello() {
    cout << "Hello from moved thread\n";
    cout<<this_thread::get_id();
}

int main() {
    thread t1(hello);
    thread t2 = move(t1); 
    t2.join();
}
