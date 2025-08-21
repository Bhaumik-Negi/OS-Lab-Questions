#include <stdio.h>
struct Process {
    int pid, at, bt, st, ct, rt;
    float tat, wt;
};
int main() {
    int n, i;
    float sum_tat = 0, sum_wt = 0, cpu_util, throughput;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    struct Process p[n];
    for (i = 0; i < n; i++) {
        p[i].pid = i + 1;
        printf("For Process %d\n", p[i].pid);
        printf("Enter Arrival Time and Burst Time: ");
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
    for (i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                struct Process temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    for (i = 0; i < n; i++) {
        if (i == 0) {
            p[i].st = p[i].at;
        } else if (p[i - 1].ct < p[i].at) {
            p[i].st = p[i].at;
        } else {
            p[i].st = p[i - 1].ct;
        }
        p[i].ct = p[i].st + p[i].bt;
        p[i].rt = p[i].st - p[i].at;
        p[i].tat = p[i].ct - p[i].at;
        p[i].wt = p[i].tat - p[i].bt;
        sum_tat += p[i].tat;
        sum_wt += p[i].wt;
    }
    int total_bt = 0, max_ct = 0;
    for (i = 0; i < n; i++) {
        total_bt += p[i].bt;
        if (p[i].ct > max_ct) max_ct = p[i].ct;
    }
    cpu_util = (total_bt * 100.0) / max_ct;
    throughput = (float)n / max_ct;
    printf("\nGantt Chart: ");
    for (i = 0; i < n; i++) printf("P%d ", p[i].pid);
    printf("\n\nPID\tAT\tBT\tST\tCT\tTAT\tWT\tRT\n");
    for (i = 0; i < n; i++) {
        printf("P%d\t%d\t%d\t%d\t%d\t%.2f\t%.2f\t%d\n",p[i].pid, p[i].at, p[i].bt, p[i].st, p[i].ct, p[i].tat, p[i].wt, p[i].rt);
    }
    printf("\nSum of Turnaround Time: %.2f\n", sum_tat);
    printf("Average Turnaround Time: %.2f\n", sum_tat / n);
    printf("Sum of Waiting Time: %.2f\n", sum_wt);
    printf("Average Waiting Time: %.2f\n", sum_wt / n);
    printf("CPU Utilization: %.2f%%\n", cpu_util);
    printf("Throughput: %.2f\n", throughput);
    return 0;
}
