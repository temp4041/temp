#include <stdio.h>
#include <stdlib.h>

#define MAX_BLOCKS 100 // Maximum number of blocks in the file system

// Structure to represent a block in the file system
struct Block {
    int block_id;   // Block ID
    int is_allocated; // Flag to indicate if the block is allocated to a file
};

// Structure to represent a file
struct File {
    int file_id;    // File ID
    int size;       // File size (number of blocks)
    int *blocks;    // Array of block IDs allocated to the file
};

// Function to initialize blocks in the file system
void initializeBlocks(struct Block blocks[], int num_blocks) {
    for (int i = 0; i < num_blocks; i++) {
        blocks[i].block_id = i;
        blocks[i].is_allocated = 0;
    }
}

// Function to display the status of blocks in the file system
void displayBlockStatus(struct Block blocks[], int num_blocks) {
    printf("Block Status:\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("Block %d: %s\n", blocks[i].block_id, (blocks[i].is_allocated ? "Allocated" : "Free"));
    }
    printf("\n");
}

// Function to allocate file using sequential allocation strategy
void allocateSequential(struct File *file, struct Block blocks[], int num_blocks) {
    int allocated_blocks = 0;
    for (int i = 0; i < num_blocks && allocated_blocks < file->size; i++) {
        if (!blocks[i].is_allocated) {
            blocks[i].is_allocated = 1;
            file->blocks[allocated_blocks++] = i;
        }
    }
    if (allocated_blocks < file->size) {
        printf("Not enough contiguous blocks available for sequential allocation.\n");
    } else {
        printf("File %d allocated using sequential allocation.\n", file->file_id);
    }
}

// Function to allocate file using indexed allocation strategy
void allocateIndexed(struct File *file, struct Block blocks[], int num_blocks) {
    // Allocate an index block for the file
    int index_block = -1;
    for (int i = 0; i < num_blocks; i++) {
        if (!blocks[i].is_allocated) {
            blocks[i].is_allocated = 1;
            index_block = i;
            break;
        }
    }
    if (index_block == -1) {
        printf("Unable to allocate index block for file %d.\n", file->file_id);
        return;
    }

    // Allocate blocks for the file and store block IDs in the index block
    printf("Index Block Allocated at Block %d\n", index_block);
    printf("Blocks Allocated for File %d:\n", file->file_id);
    int allocated_blocks = 0;
    for (int i = 0; i < num_blocks && allocated_blocks < file->size; i++) {
        if (!blocks[i].is_allocated) {
            blocks[i].is_allocated = 1;
            blocks[index_block].is_allocated = 1; // Mark index block as allocated
            blocks[index_block].block_id = i; // Store block ID in index block
            printf("Block %d\n", i);
            file->blocks[allocated_blocks++] = i;
        }
    }
    if (allocated_blocks < file->size) {
        printf("Not enough free blocks available for indexed allocation.\n");
    } else {
        printf("File %d allocated using indexed allocation.\n", file->file_id);
    }
}

// Function to allocate file using linked allocation strategy
void allocateLinked(struct File *file, struct Block blocks[], int num_blocks) {
    // Allocate blocks for the file and store block IDs in file's block array
    printf("Blocks Allocated for File %d:\n", file->file_id);
    int allocated_blocks = 0;
    for (int i = 0; i < num_blocks && allocated_blocks < file->size; i++) {
        if (!blocks[i].is_allocated) {
            blocks[i].is_allocated = 1;
            file->blocks[allocated_blocks++] = i;
            printf("Block %d\n", i);
        }
    }
    if (allocated_blocks < file->size) {
        printf("Not enough free blocks available for linked allocation.\n");
    } else {
        printf("File %d allocated using linked allocation.\n", file->file_id);
    }
}

// Function to deallocate file
void deallocateFile(struct File *file, struct Block blocks[]) {
    printf("Deallocating File %d\n", file->file_id);
    for (int i = 0; i < file->size; i++) {
        blocks[file->blocks[i]].is_allocated = 0;
    }
}

int main() {
    // Initialize blocks in the file system
    struct Block blocks[MAX_BLOCKS];
    initializeBlocks(blocks, MAX_BLOCKS);

    // Display initial block status
    displayBlockStatus(blocks, MAX_BLOCKS);

    // Define files
    struct File file1 = {1, 3, malloc(sizeof(int) * 3)};
    struct File file2 = {2, 4, malloc(sizeof(int) * 4)};
    struct File file3 = {3, 2, malloc(sizeof(int) * 2)};

    // Allocate files using different strategies
    allocateSequential(&file1, blocks, MAX_BLOCKS);
    allocateIndexed(&file2, blocks, MAX_BLOCKS);
    allocateLinked(&file3, blocks, MAX_BLOCKS);

    // Display block status after allocation
    displayBlockStatus(blocks, MAX_BLOCKS);

    // Deallocate files
    deallocateFile(&file1, blocks);
    deallocateFile(&file2, blocks);
    deallocateFile(&file3, blocks);

    // Display block status after deallocation
    displayBlockStatus(blocks, MAX_BLOCKS);

    // Free allocated memory for file blocks
    free(file1.blocks);
    free(file2.blocks);
    free(file3.blocks);

    return 0;
}

