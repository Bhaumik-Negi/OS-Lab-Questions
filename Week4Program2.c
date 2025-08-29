#include <stdio.h>

struct Process {
    int pid, at, bt, priority, st, ct, rt;
    float tat, wt;
    int completed;
};

int main() {
    int n;
    float sum_tat = 0, sum_wt = 0;

    printf("Number of processes: ");
    scanf("%d", &n);

    struct Process p[n];

    for (int i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("For Process P%d (AT BT Priority): ", p[i].pid);
        scanf("%d %d %d", &p[i].at, &p[i].bt, &p[i].priority);
        p[i].completed = 0;
    }

    int completed = 0, curr_time = 0;
    int gantt[1000], gantt_idx = 0;

    while (completed < n) {
        int idx = -1;
        int min_priority = 1e9;

        // Find process with highest priority (lowest number)
        for (int i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= curr_time) {
                if (p[i].priority < min_priority) {
                    min_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == min_priority) {
                    // If same priority → choose earlier arrival
                    if (idx != -1 && p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx == -1) {
            // No process available, idle CPU
            gantt[gantt_idx++] = 0;
            curr_time++;
        } else {
            // Schedule this process till completion
            p[idx].st = curr_time;
            p[idx].rt = p[idx].st - p[idx].at; // response time
            p[idx].ct = curr_time + p[idx].bt;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;

            sum_tat += p[idx].tat;
            sum_wt += p[idx].wt;
            curr_time = p[idx].ct;
            p[idx].completed = 1;
            gantt[gantt_idx++] = p[idx].pid;

            completed++;
        }
    }

    // Gantt Chart
    printf("\nGantt Chart: ");
    int last = -1;
    for (int i = 0; i < gantt_idx; i++) {
        if (gantt[i] == 0) continue;
        if (gantt[i] != last) {
            printf("P%d ", gantt[i]);
            last = gantt[i];
        }
    }
    printf("\n");

    // Table
    printf("\nPID\tAT\tBT\tPriority\tST\tCT\tTAT\tWT\tRT\n");
    for (int i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t\t%d\t%d\t%.2f\t%.2f\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].priority,
               p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }

    printf("\nAverage Waiting Time: %.2f", sum_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", sum_tat / n);

    return 0;
}
