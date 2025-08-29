#include <stdio.h>
struct Process {
    int pid, at, bt, priority, st, ct, rt, remaining;
    float tat, wt;
    int started;
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
        p[i].remaining = p[i].bt;
        p[i].started = 0;
    }
    int completed = 0, curr_time = 0;
    int gantt[1000]; 
    int gantt_idx = 0;
    while (completed < n) {
        int idx = -1;
        int min_priority = 1e9;
        for (int i = 0; i < n; i++) {
            if (p[i].at <= curr_time && p[i].remaining > 0) {
                if (p[i].priority < min_priority) {
                    min_priority = p[i].priority;
                    idx = i;
                } else if (p[i].priority == min_priority) {
                    if (idx != -1 && p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }
        if (idx == -1) {
            gantt[gantt_idx++] = 0; 
            curr_time++;
            continue;
        }
        if (!p[idx].started) {
            p[idx].st = curr_time;
            p[idx].rt = curr_time - p[idx].at;
            p[idx].started = 1;
        }
        p[idx].remaining--;
        gantt[gantt_idx++] = p[idx].pid; 
        curr_time++;
        if (p[idx].remaining == 0) {
            p[idx].ct = curr_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            sum_tat += p[idx].tat;
            sum_wt += p[idx].wt;
            completed++;
        }
    }
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
