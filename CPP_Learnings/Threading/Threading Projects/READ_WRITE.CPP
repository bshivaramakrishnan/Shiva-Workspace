#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <string>
#include <mutex>
#include <condition_variable>

using namespace std;

mutex g_mtx;
condition_variable g_cv;

int g_linesWritten = 0;
int g_linesRead = 0;
int g_totalLines = 0;

class Fileoperations {
public:
    int countLines(const string& filename) {
        ifstream file(filename);
        string line;
        int count = 0;
        while (getline(file, line)) {
            count++;
        }
        return count;
    }

    void NewFileWriter(const string& filename) {
        ifstream infile(filename);
        ofstream outfile("File OUT.txt");
        string line;
        cout << "Reader started...\n";

        while (getline(infile, line)) {
            unique_lock<mutex> lock(g_mtx);

          
            while (g_linesWritten > g_linesRead)
                g_cv.wait(lock);

          
            outfile.clear();
            outfile.seekp(0);
            outfile << line << '\n';
            outfile.flush();

            cout << " Wrote: " << line << endl;
            g_linesWritten++;           
            lock.unlock();
            g_cv.notify_one();
            this_thread::sleep_for(chrono::milliseconds(300));
        }

        infile.close();
        outfile.close();
    }

    void Consolewriter() {
        ifstream infile("File OUT.txt");
        string line;

        cout << "Writer started...\n";

        while (true) {
            unique_lock<mutex> lock(g_mtx);

            
            while (g_linesRead >= g_linesWritten)
                g_cv.wait(lock);

           
            infile.clear();
            infile.seekg(0);
            getline(infile, line);
            g_linesRead++;

            cout << " Read: " << line << endl;

            lock.unlock();
            g_cv.notify_one();

            if (g_linesRead >= g_totalLines)
                break;

            this_thread::sleep_for(chrono::milliseconds(300));
        }

        infile.close();
    }
};

int main() {
    Fileoperations ops;
    g_totalLines = ops.countLines("test2.txt");

    thread t1(&Fileoperations::NewFileWriter, &ops, "test2.txt");
    thread t2(&Fileoperations::Consolewriter, &ops);

    t1.join();
    t2.join();

    cout << "\n  finished.\n";
    return 0;
}
