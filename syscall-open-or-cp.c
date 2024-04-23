#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFER_SIZE 4096

int main() {
    int source_fd, dest_fd;
    ssize_t bytes_read, bytes_written;
    char buffer[BUFFER_SIZE];

    // Open the source file for reading
    source_fd = open("source.txt", O_RDONLY);
    if (source_fd == -1) {
        perror("open source.txt");
        exit(EXIT_FAILURE);
    }

    // Open or create the destination file for writing
    dest_fd = open("destination.txt", O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if (dest_fd == -1) {
        perror("open destination.txt");
        exit(EXIT_FAILURE);
    }

    // Read from the source file and write to the destination file
    while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if (bytes_written != bytes_read) {
            perror("write destination.txt");
            exit(EXIT_FAILURE);
        }
    }
    if (bytes_read == -1) {
        perror("read source.txt");
        exit(EXIT_FAILURE);
    }

    // Close the files
    if (close(source_fd) == -1) {
        perror("close source.txt");
        exit(EXIT_FAILURE);
    }
    if (close(dest_fd) == -1) {
        perror("close destination.txt");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully.\n");

    return 0;
}

