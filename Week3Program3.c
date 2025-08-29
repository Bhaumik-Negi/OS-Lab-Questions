#include <stdio.h>
struct Process {
    int pid, at, bt, st, ct, rt, remaining;
    float tat, wt;
    int start_flag;
};
int main() {
    int n, completed = 0, curr_time = 0, i, idx, min_remaining;
    float sum_tat = 0, sum_wt = 0;
    int last_idx = -1;
    int gantt_chart[1000], gc_len = 0;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("For Process %d\n", p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].remaining = p[i].bt;
        p[i].start_flag = 0;
    }
    while (completed < n) {
        min_remaining = 1000000; idx = -1;
        for (i = 0; i < n; i++) {
            if (p[i].at <= curr_time && p[i].remaining > 0 && p[i].remaining < min_remaining) {
                min_remaining = p[i].remaining;
                idx = i;
            }
        }
        if (idx == -1) { curr_time++; continue; }
        if (!p[idx].start_flag) {
            p[idx].st = curr_time;
            p[idx].rt = curr_time - p[idx].at;
            p[idx].start_flag = 1;
        }
        if (last_idx != idx) {
            gantt_chart[gc_len++] = p[idx].pid;
            last_idx = idx;
        }
        p[idx].remaining--;
        curr_time++;
        if (p[idx].remaining == 0) {
            p[idx].ct = curr_time;
            p[idx].tat = p[idx].ct - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            sum_tat += p[idx].tat; sum_wt += p[idx].wt;
            completed++;
        }
    }
    printf("\nGantt Chart: ");
    for (i = 0; i < gc_len; i++)
        printf("P%d ", gantt_chart[i]);
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
