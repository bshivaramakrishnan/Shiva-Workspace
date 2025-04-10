#include <iostream>
#include <thread>
#include <atomic>

using namespace std;

atomic<int> counter(0); 
void increment(int times) {
    for (int i = 0; i < times; ++i) {
        ++counter;  
    }
}

int main() {
    int incrementsPerThread = 100000;

    
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
