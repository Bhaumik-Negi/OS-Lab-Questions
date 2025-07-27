#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
    pid_t pid1, pid2;
    pid1 = fork();
    if (pid1 == 0)
    {
        printf("Child 1 (PID: %d) is listing files...\n", getpid());
        execlp("ls", "ls", "-l", NULL); 
        printf("execlp failed");
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("Parent: Child 1 finished.\n");
        pid2 = fork();
        if (pid2 == 0)
        {
            printf("Child 2 (PID: %d), sleeping for 5 seconds...\n", getpid());
            sleep(5);
            printf("Child 2 (PID: %d) woke up. Parent PID is now: %d\n", getpid(), getppid());
        }
        else
        {
            printf("Parent (PID = %d ) exiting before child 2 completes...\n",getpid());
            exit(0);
        }
    }
    return 0;
}
