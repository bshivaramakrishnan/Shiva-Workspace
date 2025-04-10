#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
#include <condition_variable>
#include <queue>

using namespace std;


queue<string> g_buffer;
const unsigned int g_MAX_BUFFER_SIZE = 2;

mutex g_mtx;
condition_variable g_cv;
bool g_boolDone = false;

class Fileoperations
{
public:
    void reader(string m_strFilename)
    {
        string l_strLine;
        cout << "Starting File Reader..." << endl;
        ifstream l_fileObj(m_strFilename);

        while (getline(l_fileObj, l_strLine)) {
            unique_lock<mutex> l_lock(g_mtx);
            g_cv.wait(l_lock, [] { return g_buffer.size() < g_MAX_BUFFER_SIZE; });

            g_buffer.push(l_strLine);

            l_lock.unlock();
            g_cv.notify_all();
            this_thread::sleep_for(chrono::milliseconds(100));
        }

        unique_lock<mutex> l_lock(g_mtx);
        g_boolDone = true;
        l_lock.unlock();
        g_cv.notify_all();
    }

    void write()
    {
        cout << "Starting Buffer Reader..." << endl;
        while (true) {
            unique_lock<mutex> l_lock(g_mtx);
            g_cv.wait(l_lock, [] { return !g_buffer.empty() || g_boolDone; });

            if (!g_buffer.empty()) {
                string l_val = g_buffer.front();
                g_buffer.pop();
                cout << "[Consumer] " << l_val << endl;
            }
            else if (g_boolDone) {
                break;
            }

            l_lock.unlock();
            g_cv.notify_all();
            this_thread::sleep_for(chrono::milliseconds(150));
        }
    }
};

int main()
{
    Fileoperations m_fileOps;
    thread m_thread1(&Fileoperations::reader, &m_fileOps, "test.txt");
    thread m_thread2(&Fileoperations::write, &m_fileOps);

    m_thread1.join();
    m_thread2.join();

    return 0;
}
