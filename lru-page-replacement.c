#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3 // Maximum number of frames in memory

// Function to find if a page is present in memory
int findPage(int page, int *pages, int num_frames) {
    for (int i = 0; i < num_frames; i++) {
        if (pages[i] == page) {
            return 1; // Page found in memory
        }
    }
    return 0; // Page not found in memory
}

// Function to find the index of the least recently used page
int findLRUIndex(int *last_used, int num_frames) {
    int min_index = 0;
    for (int i = 1; i < num_frames; i++) {
        if (last_used[i] < last_used[min_index]) {
            min_index = i;
        }
    }
    return min_index;
}

// Function to simulate LRU page replacement policy
void LRUPageReplacement(int *page_references, int num_references) {
    int frames[MAX_FRAMES] = {0};   // Array to store pages in memory
    int last_used[MAX_FRAMES] = {0}; // Array to store last used time for each page
    int page_faults = 0;             // Counter for page faults

    // Iterate through page references
    for (int i = 0; i < num_references; i++) {
        int page = page_references[i];

        // If page not found in memory, replace the least recently used page with the current page
        if (!findPage(page, frames, MAX_FRAMES)) {
            int lru_index = findLRUIndex(last_used, MAX_FRAMES);
            frames[lru_index] = page;
            last_used[lru_index] = i + 1; // Update last used time
            page_faults++;
        } else {
            // Update last used time for the page
            for (int j = 0; j < MAX_FRAMES; j++) {
                if (frames[j] == page) {
                    last_used[j] = i + 1; // Update last used time
                    break;
                }
            }
        }

        // Print memory state after each page reference
        printf("Page References: ");
        for (int j = 0; j < MAX_FRAMES; j++) {
            printf("%d ", frames[j]);
        }
        printf("\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    // Input string of page references
    int page_references[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int num_references = sizeof(page_references) / sizeof(page_references[0]);

    // Demonstrate LRU page replacement policy
    printf("LRU Page Replacement Policy:\n");
    LRUPageReplacement(page_references, num_references);

    return 0;
}

