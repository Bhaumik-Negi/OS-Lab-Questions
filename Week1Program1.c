#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main()
{
    pid_t pid;
    pid = fork();
    if (pid < 0)
    {
        printf("Fork failed");
        return 1;
    }
    if (pid == 0)
    {
        printf("This is the Child process.\n");
        printf("Child PID: %d\n", getpid());
    }
    else
    {
        printf("This is the Parent process.\n");
        printf("Parent PID: %d\n", getpid());
        printf("Child PID from parent: %d\n", pid);
    }
    return 0;
}
