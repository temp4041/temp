#include <stdio.h>
#include <stdlib.h>

#define MAX_PROCESSES 5 // Maximum number of processes
#define TIME_QUANTUM 2  // Time quantum for Round Robin scheduling

// Structure to represent a process
struct Process {
    int process_id;   // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
    int remaining_burst_time; // Remaining burst time
    int waiting_time; // Waiting time
    int turnaround_time; // Turnaround time
};

// Function to simulate Round Robin scheduling algorithm
void roundRobin(struct Process processes[], int n) {
    int current_time = 0; // Current time
    int completed_processes = 0; // Counter for completed processes

    printf("Time  | Process\n");
    printf("----------------\n");

    // Continue until all processes are completed
    while (completed_processes < n) {
        // Iterate through each process
        for (int i = 0; i < n; i++) {
            // Check if the process has arrived and still has remaining burst time
            if (processes[i].arrival_time <= current_time && processes[i].remaining_burst_time > 0) {
                printf("%-5d | P%d\n", current_time, processes[i].process_id);
                
                // Execute the process for the time quantum or remaining burst time, whichever is smaller
                int execution_time = (processes[i].remaining_burst_time < TIME_QUANTUM) ? processes[i].remaining_burst_time : TIME_QUANTUM;
                current_time += execution_time;
                processes[i].remaining_burst_time -= execution_time;

                // If the process is completed, update the completed processes counter
                if (processes[i].remaining_burst_time == 0) {
                    completed_processes++;
                    processes[i].turnaround_time = current_time - processes[i].arrival_time;
                }
            }
        }
    }

    // Calculate waiting time for each process
    int total_waiting_time = 0;
    for (int i = 0; i < n; i++) {
        processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;
        total_waiting_time += processes[i].waiting_time;
    }

    // Print waiting time and turnaround time for each process
    printf("\nProcess | Waiting Time | Turnaround Time\n");
    printf("------------------------------------------\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t   %d\t\t   %d\n", processes[i].process_id, processes[i].waiting_time, processes[i].turnaround_time);
    }
    printf("\nAverage Waiting Time: %.2f\n", (float)total_waiting_time / n);
}

int main() {
    // Array of processes with their arrival time and burst time
    struct Process processes[MAX_PROCESSES] = {
        {1, 0, 4, 4},
        {2, 1, 3, 3},
        {3, 2, 5, 5},
        {4, 3, 2, 2},
        {5, 4, 4, 4}
    };

    int n = sizeof(processes) / sizeof(processes[0]);

    // Simulate Round Robin scheduling algorithm and calculate waiting time and turnaround time
    roundRobin(processes, n);

    return 0;
}

