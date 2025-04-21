#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include <fstream>
#include <iomanip>
#include <ctime>
#include <windows.h>
using namespace std;

class FileOperations {
    static const size_t bufferSize = 1024;

public:
    static bool MoveFile(const std::string& source, const std::string& destination);
    static bool CopyFile(const std::string& source, const std::string& destination);
    static void WriteFile(const std::string& destination);
    static void ReadFile(const std::string& source);
    static bool VerifyFile(const std::string& filePath, const std::string& expectedChecksum);
    static bool CreateDirectory(const std::string& dirPath);
    static bool DeleteDirectory(const std::string& dirPath);
    static std::vector<std::string> ListFiles(const std::string& directory, bool recursive = false);
    static std::unordered_map<std::string, std::string> GetFileMetadata(const std::string& filePath);
    static bool Exists(const std::string& path);
    static uint64_t GetFileSize(const std::string& filePath);
    static time_t GetLastModifiedTime(const std::string& filePath);

private:
    static void ListFilesHelper(const std::string& directory, std::vector<std::string>& files, bool recursive);
};