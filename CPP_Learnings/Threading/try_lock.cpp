#include <iostream>
#include <thread>
#include <chrono>
#include <mutex>

using namespace std;


int dataFromProducerA = 0;
int dataFromProducerB = 0;

std::mutex mutexA;
std::mutex mutexB;

void sleepForSeconds(int seconds) {
    this_thread::sleep_for(chrono::seconds(seconds));
}

void produceData(int& sharedData, mutex& dataMutex, const string& label) {
    for (int i = 1; i <= 5; ++i) {
        dataMutex.lock();
        ++sharedData;
        cout << "Produced by " << label << ": " << sharedData << endl;
        dataMutex.unlock();
        sleepForSeconds(1);
    }
}

void consumeData() {
    int consumptionCount = 5;
    int totalSum = 0;

    while (consumptionCount > 0) {
        if (try_lock(mutexA, mutexB)) {
            if (dataFromProducerA != 0 && dataFromProducerB != 0) {
                totalSum += dataFromProducerA + dataFromProducerB;

                cout << "Consumed: " << dataFromProducerA << " + " << dataFromProducerB
                    << " = " << dataFromProducerA + dataFromProducerB << endl;

          
                dataFromProducerA = 0;
                dataFromProducerB = 0;

                --consumptionCount;
            }
           
            mutexA.unlock();
            mutexB.unlock();
        }

        sleepForSeconds(1);
    }
}

int main() {
    thread producerA(produceData, ref(dataFromProducerA), ref(mutexA), "Producer A");
    thread producerB(produceData, ref(dataFromProducerB), ref(mutexB), "Producer B");
    thread consumer(consumeData);

    producerA.join();
    producerB.join();
    consumer.join();

    return 0;
}
