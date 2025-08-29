#include <stdio.h>

struct Process {
    int pid, at, bt, ct, tat, wt, rt, remaining;
    int started;
};

int main() {
    int n, tq;
    float sum_tat = 0, sum_wt = 0;

    printf("Number of processes : ");
    scanf("%d", &n);

    struct Process p[n];

    printf("Burst time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
        p[i].pid = i;
        p[i].remaining = p[i].bt;
        p[i].started = 0;
    }

    printf("Arrival time : ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
    }

    printf("Time Quantum: ");
    scanf("%d", &tq);

    int completed = 0, curr_time = 0;
    int gantt[1000], gantt_idx = 0;
    int q[1000], front = 0, rear = 0; // ready queue

    // Push first arrived processes
    int visited[n];
    for (int i = 0; i < n; i++) visited[i] = 0;

    while (completed < n) {
        // Enqueue available processes
        for (int i = 0; i < n; i++) {
            if (p[i].at <= curr_time && !visited[i] && p[i].remaining > 0) {
                q[rear++] = i;
                visited[i] = 1;
            }
        }

        if (front == rear) { // CPU idle
            curr_time++;
            continue;
        }

        int idx = q[front++]; // dequeue

        if (!p[idx].started) {
            p[idx].rt = curr_time - p[idx].at; // response time
            p[idx].started = 1;
        }

        int exec_time = (p[idx].remaining > tq) ? tq : p[idx].remaining;
        for (int i = 0; i < exec_time; i++) {
            gantt[gantt_idx++] = p[idx].pid;
            curr_time++;
            // New arrivals during execution
            for (int j = 0; j < n; j++) {
                if (p[j].at <= curr_time && !visited[j] && p[j].remaining > 0) {
                    q[rear++] = j;
                    visited[j] = 1;
                }
            }
        }

        p[idx].remaining -= exec_time;
        if (p[idx].remaining == 0) {
            p[idx].ct = curr_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            sum_tat += p[idx].tat;
            sum_wt += p[idx].wt;
            completed++;
        } else {
            q[rear++] = idx; // put back in queue
        }
    }

    // Print Gantt Chart
    printf("\nGantt Chart : ");
    int last = -1;
    for (int i = 0; i < gantt_idx; i++) {
        if (gantt[i] != last) {
            printf("P%d ", gantt[i]);
            last = gantt[i];
        }
    }
    printf("\n");

    // Print process details
    printf("\nPID\tAT\tBT\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               p[i].pid, p[i].at, p[i].bt,
               p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage waiting time: %.2f", sum_wt / n);
    printf("\nAverage turnaround time : %.2f\n", sum_tat / n);

    return 0;
}
