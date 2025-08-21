#include <stdio.h>
struct Process {
    int pid, at, bt, st, ct, rt;
    float tat, wt;
    int completed;
};
int main() {
    int n, completed = 0, curr_time = 0, i, min_bt, idx;
    float sum_tat = 0, sum_wt = 0;
    int gantt_order[50], go_idx = 0; 
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("For Process %d\n", p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }
    while (completed < n) {
        min_bt = 1000000; idx = -1;
        for (i = 0; i < n; i++) {
            if (!p[i].completed && p[i].at <= curr_time && p[i].bt < min_bt) {
                min_bt = p[i].bt;
                idx = i;
            }
        }
        if (idx == -1) {
            curr_time++;
            continue;
        }
        p[idx].st = (curr_time < p[idx].at) ? p[idx].at : curr_time;
        p[idx].ct = p[idx].st + p[idx].bt;
        p[idx].rt = p[idx].st - p[idx].at;
        p[idx].tat = p[idx].ct - p[idx].at;
        p[idx].wt = p[idx].tat - p[idx].bt;
        sum_tat += p[idx].tat;
        sum_wt += p[idx].wt;
        curr_time = p[idx].ct;
        p[idx].completed = 1;
        completed++;
        gantt_order[go_idx++] = p[idx].pid;
    }
    printf("\nGantt Chart: ");
    for (i = 0; i < go_idx; i++) {
        printf("P%d ", gantt_order[i]);
    }
    printf("\n\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%d\n",
               p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\nSum of Turnaround Time: %.2f\n", sum_tat);
    printf("Average Turnaround Time: %.2f\n", sum_tat / n);
    printf("Sum of Waiting Time: %.2f\n", sum_wt);
    printf("Average Waiting Time: %.2f\n", sum_wt / n);
    return 0;
}
