#include <stdio.h>
struct Resource {
    int a, b, c;
};

int main() {
    int p, r;
    printf("Enter number of processes : ");
    scanf("%d", &p);
    printf("Enter number of resources : ");
    scanf("%d", &r);
    struct Resource max[p], alloc[p], need[p];
    struct Resource total, avail;
    printf("Enter maximum requirement : \n");
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &max[i].a, &max[i].b, &max[i].c);
    }
    printf("Enter allocated matrix : \n");
    for (int i = 0; i < p; i++) {
        scanf("%d %d %d", &alloc[i].a, &alloc[i].b, &alloc[i].c);
    }
    printf("Resource Vector : ");
    scanf("%d %d %d", &total.a, &total.b, &total.c);
    avail.a = total.a;
    avail.b = total.b;
    avail.c = total.c;
    for (int i = 0; i < p; i++) {
        avail.a -= alloc[i].a;
        avail.b -= alloc[i].b;
        avail.c -= alloc[i].c;
    }
    for (int i = 0; i < p; i++) {
        need[i].a = max[i].a - alloc[i].a;
        need[i].b = max[i].b - alloc[i].b;
        need[i].c = max[i].c - alloc[i].c;
    }
    int finish[p];
    int safeSeq[p];
    for (int i = 0; i < p; i++) finish[i] = 0;
    int count = 0;
    while (count < p) {
        int found = 0;
        for (int i = 0; i < p; i++) {
            if (!finish[i]) {
                // Check if need <= avail
                if (need[i].a <= avail.a &&
                    need[i].b <= avail.b &&
                    need[i].c <= avail.c) {
                    
                    // Pretend to allocate
                    avail.a += alloc[i].a;
                    avail.b += alloc[i].b;
                    avail.c += alloc[i].c;

                    safeSeq[count++] = i;
                    finish[i] = 1;
                    found = 1;
                }
            }
        }
        if (!found) break; 
    }

    if (count < p) {
        printf("Request cannot be fulfilled\n");
    } else {
        printf("Request can be fulfilled\n");
        printf("Safe Sequence : ");
        for (int i = 0; i < p; i++) {
            printf("P%d", safeSeq[i]);
            if (i != p - 1) printf(" ");
        }
        printf("\n");
    }

    return 0;
}
