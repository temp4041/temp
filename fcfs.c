#include <stdio.h>

// Structure to represent a process
struct Process {
    int process_id;   // Process ID
    int arrival_time; // Arrival time
    int burst_time;   // Burst time
};

// Function to calculate waiting time for each process
void calculateWaitingTime(struct Process processes[], int n, int waiting_time[]) {
    waiting_time[0] = 0; // Waiting time for the first process is 0

    // Calculate waiting time for each process
    for (int i = 1; i < n; i++) {
        waiting_time[i] = waiting_time[i - 1] + processes[i - 1].burst_time;
    }
}

// Function to calculate turnaround time for each process
void calculateTurnaroundTime(struct Process processes[], int n, int waiting_time[], int turnaround_time[]) {
    // Calculate turnaround time for each process
    for (int i = 0; i < n; i++) {
        turnaround_time[i] = waiting_time[i] + processes[i].burst_time;
    }
}

// Function to calculate average waiting time and average turnaround time
void calculateAverageTimes(struct Process processes[], int n) {
    int waiting_time[n], turnaround_time[n];

    // Calculate waiting time for each process
    calculateWaitingTime(processes, n, waiting_time);

    // Calculate turnaround time for each process
    calculateTurnaroundTime(processes, n, waiting_time, turnaround_time);

    // Calculate total waiting time and total turnaround time
    int total_waiting_time = 0, total_turnaround_time = 0;
    for (int i = 0; i < n; i++) {
        total_waiting_time += waiting_time[i];
        total_turnaround_time += turnaround_time[i];
    }

    // Calculate average waiting time and average turnaround time
    float avg_waiting_time = (float)total_waiting_time / n;
    float avg_turnaround_time = (float)total_turnaround_time / n;

    // Print average waiting time and average turnaround time
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
}

int main() {
    // Array of processes with their arrival time and burst time
    struct Process processes[] = {{1, 0, 5}, {2, 1, 3}, {3, 2, 8}, {4, 3, 6}};

    int n = sizeof(processes) / sizeof(processes[0]);

    printf("Process ID\tArrival Time\tBurst Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\n", processes[i].process_id, processes[i].arrival_time, processes[i].burst_time);
    }

    printf("\n");

    // Calculate average waiting time and average turnaround time
    calculateAverageTimes(processes, n);

    return 0;
}

