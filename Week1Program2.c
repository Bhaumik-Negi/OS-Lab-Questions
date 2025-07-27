#include <stdio.h>  
#include <unistd.h> 
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
        printf("Child Process:\n");
        printf("PID: %d\n", getpid());
        printf("Parent PID: %d\n", getppid());
    }
    else
    {
        printf("Parent Process:\n");
        printf("PID: %d\n", getpid());
        printf("Child PID: %d\n", pid);
    }
    return 0;
}
