#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 3) {
        printf("Usage: %s <source_path> <destination_path>\n", argv[0]);
        return 1;
    }

    const char *source_path = argv[1];
    const char *destination_path = argv[2];

    // Perform the move operation
    if (rename(source_path, destination_path) != 0) {
        perror("Error moving file");
        return 1;
    }

    printf("File moved successfully.\n");

    return 0;
}

