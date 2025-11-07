#include <stdio.h>
struct Resource {
    int res[10];   
};
int main() {
    int p, r;
    printf("Enter number of processes : ");
    scanf("%d", &p);
    printf("Enter number of resources : ");
    scanf("%d", &r);
    struct Resource max[p], alloc[p], need[p];
    struct Resource total, avail;
    printf("Enter maximum requirement :\n");

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &max[i].res[j]);

    printf("Enter allocated matrix :\n");

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            scanf("%d", &alloc[i].res[j]);

    printf("Resource Vector : ");

    for (int j = 0; j < r; j++)
        scanf("%d", &total.res[j]);

    for (int j = 0; j < r; j++) {
        avail.res[j] = total.res[j];
        for (int i = 0; i < p; i++)
            avail.res[j] -= alloc[i].res[j];
    }

    for (int i = 0; i < p; i++)
        for (int j = 0; j < r; j++)
            need[i].res[j] = max[i].res[j] - alloc[i].res[j];

    int finish[p];
    
    for (int i = 0; i < p; i++) finish[i] = 0;

    int count = 0;
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                int j;
                for (j = 0; j < r; j++)
                    if (need[i].res[j] > avail.res[j])
                        break;
                if (j == r) {
                    for (int k = 0; k < r; k++)
                        avail.res[k] += alloc[i].res[k];
                    finish[i] = 1;
                    found = 1;
                    count++;
                }
            }
        }
        if (!found) break;
    }
    int deadlock = 0;
    for (int i = 0; i < p; i++)
        if (!finish[i]) {
            deadlock = 1;
            break;
        }
    if (deadlock)
        printf("Deadlock detected\n");
    else
        printf("No deadlock detected\n");
    return 0;
}
