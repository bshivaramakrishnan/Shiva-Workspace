#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {
    int fd = open("file.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd < 0) {
        perror("File open failed");
        return 1;
    }

    const char* data = "Hello, low-level file!";
    write(fd, data, strlen(data));
    close(fd);

    fd = open("file.txt", O_RDONLY);
    if (fd < 0) {
        perror("File open failed");
        return 1;
    }

    char buffer[100];
    ssize_t bytesRead = read(fd, buffer, sizeof(buffer) - 1);
    buffer[bytesRead] = '\0';

    cout << "Read from file: " << buffer << endl;
    close(fd);

    return 0;
}
