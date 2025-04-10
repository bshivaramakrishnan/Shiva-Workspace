#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

int counter = 0;         
mutex mtx;          

void increment(int times) {
    for (int i = 0; i < times; ++i) {
        mtx.lock();           
        ++counter;            
        mtx.unlock();         
    }
}

int main() {
  
    const int incrementsPerThread = 100000;

    thread threads[4];

    threads[0] = thread(increment, incrementsPerThread);
    threads[1] = thread(increment, incrementsPerThread);
    threads[2] = thread(increment, incrementsPerThread);
    threads[3] = thread(increment, incrementsPerThread);
  
    for (int i = 0; i < 4; ++i) {
        threads[i].join();
    }

    cout << "Final Counter Value: " << counter << endl;

    return 0;
}
