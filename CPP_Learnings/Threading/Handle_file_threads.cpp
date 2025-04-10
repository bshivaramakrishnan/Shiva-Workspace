#include<iostream>
#include<vector>
#include<mutex>
#include<fstream>
#include<thread>
#include<string>

using namespace std;


mutex buffer_mutex;
vector<string> shared_buffer;

long countlines(const string& filename) {
	string line;
	long count = 0;
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "error opening file to count lines";
	}
	while (getline(infile, line)) {
		++count;
	}
	infile.close();
	return count;

}
void readChunk(const string& filename, long start_line, long end_line) {
	string line;
	long current_line = 0;
	ifstream infile(filename);
	if (!infile.is_open()) {
		cout << "error opening file to count lines";
	}
	while (getline(infile, line))
	{
		if (current_line >= start_line && current_line < end_line) {
			lock_guard<mutex> lock(buffer_mutex);
			shared_buffer.push_back(line + " [Processed] ");
			++current_line;
		}
		if (current_line > end_line) {
			break;
		}
	}
	infile.close();
	cout << "Read lines " << start_line << " to " << end_line << endl;
}
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
	
	string inputFile;
	string outputFile;
	cout << "Enter file name to read \n";
	cin >> inputFile;
	cout << "Enter File name to write \n";
	cin >> outputFile;

	const int num_threads = 4;

	long total_lines = countlines(inputFile);
	cout << "Total lines: " << total_lines << endl;

	long chunk_size = total_lines / num_threads;
	vector<thread> readers;

	for (int i = 0; i < num_threads; ++i) {
		long start = i * chunk_size;
		long end =  start + chunk_size;
		readers.emplace_back(readChunk, inputFile, start, end);
	}

	for (auto& t : readers) {
		t.join();
	}


	thread writer(writeToFile, outputFile);
	writer.join();

	cout << "All tasks completed.\n";
	return 0;
}



