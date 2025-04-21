#include "FileOperations.h"
#include <windows.h>
#include <fileapi.h>
#include <sys/stat.h>
#include <cstdlib>
#include <cerrno>
#include <sstream>  // Added for std::ostringstream
#include <iomanip>  // Added for std::setw, std::setfill
#include <iostream> // Added for std::cout

bool FileOperations::MoveFile(const std::string& source, const std::string& destination) {
    return ::MoveFileA(source.c_str(), destination.c_str()) != 0;
}

bool FileOperations::CopyFile(const std::string& source, const std::string& destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dest(destination, std::ios::binary);
    if (!src || !dest) return false;

    char buffer[bufferSize];
    while (src.read(buffer, bufferSize)) {
        dest.write(buffer, src.gcount());
    }
    dest.write(buffer, src.gcount());
    return true;
}

void FileOperations::WriteFile(const std::string& destination) {
    std::ofstream out(destination, std::ios::binary);
    if (!out) return;
    out << "File written at " << time(nullptr) << std::endl;
}

void FileOperations::ReadFile(const std::string& source) {
    std::ifstream in(source);
    if (!in) return;

    std::string line;
    while (std::getline(in, line)) {
        std::cout << line << std::endl;
    }
}

bool FileOperations::VerifyFile(const std::string& filePath, const std::string& expectedChecksum) {
    std::ifstream file(filePath, std::ios::binary);
    if (!file) return false;

    std::ostringstream checksum;
    char ch;
    while (file.get(ch)) {
        checksum << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(ch));
    }

    return checksum.str() == expectedChecksum;
}

bool FileOperations::CreateDirectory(const std::string& dirPath) {
    return CreateDirectoryA(dirPath.c_str(), NULL) != 0 || GetLastError() == ERROR_ALREADY_EXISTS;
}

bool FileOperations::DeleteDirectory(const std::string& dirPath) {
    SHFILEOPSTRUCTA fileOp = {
        NULL,
        FO_DELETE,
        (dirPath + '\0').c_str(),
        NULL,
        FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT,
        FALSE,
        NULL,
        NULL
    };
    return SHFileOperationA(&fileOp) == 0;
}

void FileOperations::ListFilesHelper(const std::string& directory, std::vector<std::string>& files, bool recursive) {
    WIN32_FIND_DATAA findData;
    HANDLE hFind = FindFirstFileA((directory + "\\*").c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) return;

    do {
        std::string name = findData.cFileName;
        if (name == "." || name == "..") continue;

        std::string fullPath = directory + "\\" + name;
        files.push_back(fullPath);

        if (recursive && (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
            ListFilesHelper(fullPath, files, recursive);
        }
    } while (FindNextFileA(hFind, &findData) != 0);

    FindClose(hFind);
}

std::vector<std::string> FileOperations::ListFiles(const std::string& directory, bool recursive) {
    std::vector<std::string> files;
    ListFilesHelper(directory, files, recursive);
    return files;
}

std::unordered_map<std::string, std::string> FileOperations::GetFileMetadata(const std::string& filePath) {
    std::unordered_map<std::string, std::string> metadata;
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;

    if (!GetFileAttributesExA(filePath.c_str(), GetFileExInfoStandard, &fileInfo)) {
        return metadata;
    }

    size_t slash = filePath.find_last_of("\\/");
    std::string filename = (slash != std::string::npos) ? filePath.substr(slash + 1) : filePath;

    metadata["filename"] = filename;
    size_t dot = filename.find_last_of('.');
    metadata["extension"] = (dot != std::string::npos) ? filename.substr(dot + 1) : "";

    LARGE_INTEGER size;
    size.HighPart = fileInfo.nFileSizeHigh;
    size.LowPart = fileInfo.nFileSizeLow;
    metadata["size"] = std::to_string(size.QuadPart);

    FILETIME ft = fileInfo.ftLastWriteTime;
    ULARGE_INTEGER ull;
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    metadata["last_modified"] = std::to_string(ull.QuadPart / 10000000ULL - 11644473600ULL);

    return metadata;
}

bool FileOperations::Exists(const std::string& path) {
    DWORD attrs = GetFileAttributesA(path.c_str());
    return (attrs != INVALID_FILE_ATTRIBUTES);
}

uint64_t FileOperations::GetFileSize(const std::string& filePath) {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (!GetFileAttributesExA(filePath.c_str(), GetFileExInfoStandard, &fileInfo)) {
        return 0;
    }

    LARGE_INTEGER size;
    size.HighPart = fileInfo.nFileSizeHigh;
    size.LowPart = fileInfo.nFileSizeLow;
    return size.QuadPart;
}

time_t FileOperations::GetLastModifiedTime(const std::string& filePath) {
    WIN32_FILE_ATTRIBUTE_DATA fileInfo;
    if (!GetFileAttributesExA(filePath.c_str(), GetFileExInfoStandard, &fileInfo)) {
        return 0;
    }

    FILETIME ft = fileInfo.ftLastWriteTime;
    ULARGE_INTEGER ull;
    ull.LowPart = ft.dwLowDateTime;
    ull.HighPart = ft.dwHighDateTime;
    return ull.QuadPart / 10000000ULL - 11644473600ULL;
}