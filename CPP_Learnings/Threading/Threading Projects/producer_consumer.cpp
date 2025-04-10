#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <chrono>

using namespace std;

queue<int> buffer;
const unsigned int MAX_BUFFER_SIZE = 5;

mutex mtx;
condition_variable cv;

bool done = false;

void producer(int id) {
    for (int i = 1; i <= 10; ++i) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return buffer.size() < MAX_BUFFER_SIZE; });

        buffer.push(i);
        cout << "[Producer " << id << "] Produced: " << i << endl;

        lock.unlock();
        cv.notify_all();  
        this_thread::sleep_for(chrono::milliseconds(100));
    }

    unique_lock<mutex> lock(mtx);
    done = true;
    lock.unlock();
    cv.notify_all();
}

void consumer(int id) {
    while (true) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, [] { return !buffer.empty() || done; });

        if (!buffer.empty()) {
            int val = buffer.front();
            buffer.pop();
            cout << "\t[Consumer " << id << "] Consumed: " << val << endl;
        }
        else if (done) {
            break; 
        }

        lock.unlock();
        cv.notify_all(); 
        this_thread::sleep_for(chrono::milliseconds(150));
    }
}

int main() {
    thread prod(producer, 1);
    thread cons1(consumer, 1);
    thread cons2(consumer, 2);

    prod.join();
    cons1.join();
    cons2.join();

    cout << "All threads finished." << endl;
    return 0;
}
