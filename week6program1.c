#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    key_t key;
    int shmid;
    char *shared_memory;

    key = ftok(".", 65);
    if (key == -1)
    {
        perror("ftok");
        exit(1);
    }

    shmid = shmget(key, 1024, 0666 | IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget");
        exit(1);
    }

    if (fork() == 0)
    {
        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)(-1))
        {
            perror("shmat");
            exit(1);
        }

        strcpy(shared_memory, "Message from child process");
        printf("Child wrote: %s\n", shared_memory);

        shmdt(shared_memory);
    }
    else
    {
        sleep(1);

        shared_memory = (char *)shmat(shmid, NULL, 0);
        if (shared_memory == (char *)(-1))
        {
            perror("shmat");
            exit(1);
        }

        printf("Parent read: %s\n", shared_memory);

        shmdt(shared_memory);
        shmctl(shmid, IPC_RMID, NULL);
    }

    return 0;
}
