#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <fstream>
#include <map>

using namespace std;

mutex buffer_mutex;
map<int, vector<char>> shared_buffer;

const size_t CHUNK_SIZE = 1024 * 1024; 

void readChunk(const string& filename, long start_byte, long size_to_read, int chunk_index) {
    ifstream infile(filename, ios::binary);
    if (!infile.is_open()) {
        cerr << "Error opening file to read.\n";
        return;
    }

    vector<char> buffer(size_to_read);
    infile.seekg(start_byte);
    infile.read(buffer.data(), size_to_read);
    infile.close();

   
    for (auto& byte : buffer) {
        byte ^= 0xFF;
    }

    {
        lock_guard<mutex> lock(buffer_mutex);
        shared_buffer[chunk_index] = move(buffer);
    }

    cout << "Processed chunk " << chunk_index << " (bytes " << start_byte << " to " << (start_byte + size_to_read) << ")\n";
}

void writeToFile(const string& filename, int total_chunks) {
    ofstream outfile(filename, ios::binary);
    if (!outfile) {
        cerr << "Error opening output file.\n";
        return;
    }

    for (int i = 0; i < total_chunks; ++i) {
        lock_guard<mutex> lock(buffer_mutex);
        if (shared_buffer.find(i) != shared_buffer.end()) {
            outfile.write(shared_buffer[i].data(), shared_buffer[i].size());
        }
        else {
            cerr << "Missing chunk " << i << " — skipping!\n";
        }
    }

    outfile.close();
    cout << "Writing completed successfully.\n";
}

int main() {
    string inputFile, outputFile;
    cout << "Enter input file name: ";
    cin >> inputFile;
    cout << "Enter output file name: ";
    cin >> outputFile;

    const int num_threads = 4;

    ifstream infile(inputFile, ios::binary | ios::ate);
    if (!infile.is_open()) {
        cerr << "Error opening input file.\n";
        return 1;
    }

    long total_size = infile.tellg();
    infile.close();

    cout << "Total file size: " << total_size << " bytes\n";

    long chunk_size = total_size / num_threads;
    long remaining = total_size % num_threads;

    vector<thread> readers;

    for (int i = 0; i < num_threads; ++i) {
        long start = i * chunk_size;
        long size = (i == num_threads - 1) ? (chunk_size + remaining) : chunk_size;
        readers.emplace_back(readChunk, inputFile, start, size, i);
    }

    for (auto& t : readers) {
        t.join();
    }

    thread writer(writeToFile, outputFile, num_threads);
    writer.join();

    cout << "All tasks completed.\n";
    return 0;
}
