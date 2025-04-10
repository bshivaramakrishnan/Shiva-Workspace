#include <iostream>
#include <fstream>
#include <thread>
#include <mutex>
#include <string>
#include <vector>

using namespace std;

mutex buffer_mutex;
vector<string> shared_buffer;

// Count total number of lines in the file
long countLines(const string& filename) {
    ifstream infile(filename);
    string line;
    long line_count = 0;

    while (getline(infile, line)) {
        ++line_count;
    }

    return line_count;
}

// Read a chunk of lines from the file
void readChunk(const string& filename, long start_line, long end_line) {
    ifstream infile(filename);
    string line;
    long current_line = 0;

    if (!infile) {
        cout << "Error opening input file.\n";
        return;
    }

    while (getline(infile, line)) {
        if (current_line >= start_line && current_line < end_line) {
            lock_guard<mutex> lock(buffer_mutex);
            shared_buffer.push_back(line + " [processed]");
        }
        ++current_line;
        if (current_line >= end_line) break;
    }

    infile.close();
    cout << "Read lines " << start_line << " to " << end_line << endl;
}

// Write the buffer to file
void writeToFile(const string& filename) {
    ofstream outfile(filename);
    if (!outfile) {
        cout << "Error opening output file.\n";
        return;
    }

    lock_guard<mutex> lock(buffer_mutex);
    for (const auto& line : shared_buffer) {
        outfile << line << '\n';
    }

    outfile.close();
    cout << "Writing done.\n";
}

int main() {
    string inputFile = "test.txt";
    string outputFile = "output.txt";
    const int num_threads = 4;

    // Step 1: Count total lines
    long total_lines = countLines(inputFile);
    cout << "Total lines: " << total_lines << endl;

    // Step 2: Divide work
    long chunk_size = total_lines / num_threads;
    vector<thread> readers;

    for (int i = 0; i < num_threads; ++i) {
        long start = i * chunk_size;
        long end = (i == num_threads - 1) ? total_lines : start + chunk_size;
        readers.emplace_back(readChunk, inputFile, start, end);
    }

    // Step 3: Join all reader threads
    for (auto& t : readers) {
        t.join();
    }

    // Step 4: Write result
    thread writer(writeToFile, outputFile);
    writer.join();

    cout << "All tasks completed.\n";
    return 0;
}
