#include <stdio.h>

#define MAX_PAGES 3 // Maximum number of pages in memory

// Function to find if a page is present in memory
int findPage(int page, int *pages, int num_pages) {
    for (int i = 0; i < num_pages; i++) {
        if (pages[i] == page) {
            return 1; // Page found in memory
        }
    }
    return 0; // Page not found in memory
}

// Function to simulate FIFO page replacement policy
void FIFOPageReplacement(int *page_references, int num_references) {
    int pages[MAX_PAGES] = {0}; // Array to store pages in memory
    int page_faults = 0;         // Counter for page faults
    int next_index = 0;          // Next index in circular queue

    // Iterate through page references
    for (int i = 0; i < num_references; i++) {
        int page = page_references[i];

        // If page not found in memory, replace page at next_index with current page
        if (!findPage(page, pages, MAX_PAGES)) {
            pages[next_index] = page;
            page_faults++;
            next_index = (next_index + 1) % MAX_PAGES; // Move to the next index in circular queue
        }

        // Print memory state after each page reference
        printf("Page References: ");
        for (int j = 0; j < MAX_PAGES; j++) {
            printf("%d ", pages[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    // Input string of page references
    int page_references[] = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
    int num_references = sizeof(page_references) / sizeof(page_references[0]);

    // Demonstrate FIFO page replacement policy
    printf("FIFO Page Replacement Policy:\n");
    FIFOPageReplacement(page_references, num_references);

    return 0;
}

