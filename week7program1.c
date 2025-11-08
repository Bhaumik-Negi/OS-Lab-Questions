#include <stdio.h>

int main()
{
    int m;
    printf("Enter the number of frames available: ");
    scanf("%d", &m);
    int lru[m];

    int n;
    printf("Enter the number of requests: ");
    scanf("%d", &n);

    int original[n];

    printf("Enter the elements in the array:\n");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &original[i]);
    }

    int hit = 0;
    int miss = 0;
    int k = 0;

    // initialize cache as empty (-1 means empty)
    for (int i = 0; i < m; i++)
    {
        lru[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int val = original[i];
        int found = 0;

        // Check if page is already in cache (hit)
        for (int j = 0; j < m; j++)
        {
            if (val == lru[j])
            {
                hit++;
                found = 1;
                break;
            }
        }

        // If not found, it's a miss → replace using FIFO
        if (found == 0)
        {
            miss++;
            lru[k] = val;
            k = (k + 1) % m; // move FIFO pointer circularly
        }
    }

    printf("\nFinal Results:\n");
    printf("Hits : %d\n", hit);
    printf("Page Faults : %d\n", miss);

    return 0;
}
