#include <iostream>
#include <thread>
#include <vector>

typedef unsigned long long ull;
using namespace std;

// Each thread calculates its partial sum and stores it in 'result'
void arraySum(const vector<ull>& arr, ull start, ull end, ull& result) {
    ull sum = 0;
    for (ull i = start; i < end; ++i) {
        sum += arr[i];
    }
    result = sum;
    cout << "Thread ID: " << this_thread::get_id() << " | Partial Sum = " << result << endl;
}

int main() {
    const ull size = 2000000;
    vector<ull> arr(size);

    // Fill the array
    for (ull i = 0; i < size; ++i) {
        arr[i] = i + 1; // So the sum is not zero
    }

    // Divide the work
    ull chunk_size = size / 4;
    ull result1 = 0, result2 = 0, result3 = 0, result4 = 0;

    // Create 4 threads with references to result variables
    thread t1(arraySum, cref(arr), 0, chunk_size, ref(result1));
    thread t2(arraySum, cref(arr), chunk_size, chunk_size * 2, ref(result2));
    thread t3(arraySum, cref(arr), chunk_size * 2, chunk_size * 3, ref(result3));
    thread t4(arraySum, cref(arr), chunk_size * 3, size, ref(result4));

    t1.join();
    t2.join();
    t3.join();
    t4.join();

    ull total = result1 + result2 + result3 + result4;
    cout << "Total Sum = " << total << endl;

    return 0;
}