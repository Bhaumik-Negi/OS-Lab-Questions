// LRU.c
#include <stdio.h>

typedef struct {
    int val;   // page number
    int rate;  // time of last use
} LRU;

int findLeastRecentlyUsed(LRU cache[], int m) {
    int minIndex = 0;
    for (int i = 1; i < m; i++) {
        if (cache[i].rate < cache[minIndex].rate)
            minIndex = i;
    }
    return minIndex;
}

int main() {
    int n, m;
    printf("Enter number of page references: ");
    scanf("%d", &n);
    printf("Enter cache (frame) size: ");
    scanf("%d", &m);

    int pages[n];
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    LRU cache[m];
    for (int i = 0; i < m; i++) {
        cache[i].val = -1;   
        cache[i].rate = 0;
    }

    int time = 0, hit = 0, miss = 0;

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;
        time++;

        // Check if page already in cache (hit)
        for (int j = 0; j < m; j++) {
            if (cache[j].val == page) {
                hit++;
                cache[j].rate = time; 
                found = 1;
                break;
            }
        }

        // If not found → miss, replace least recently used
        if (!found) {
            miss++;
            int replaceIndex = findLeastRecentlyUsed(cache, m);
            cache[replaceIndex].val = page;
            cache[replaceIndex].rate = time;
        }
    }

    printf("\nFinal Results:\n");
    printf("Total Hits: %d\n", hit);
    printf("Total Misses: %d\n", miss);
    printf("Total Page Faults: %d\n", miss);

    return 0;
}
