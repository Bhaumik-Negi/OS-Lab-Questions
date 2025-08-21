#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    int choice;
    printf("Choose the process type:\n");
    printf("1. Orphan Process\n");
    printf("2. Zombie Process\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    pid_t pid = fork();
    if (pid < 0) {
        printf("Fork failed\n");
        exit(1);
    }
    else if (choice == 1) { // Orphan Process
        if (pid == 0) { 
            printf("Child process (PID: %d) started\n", getpid());
            sleep(5); 
            printf("Child process (PID: %d) running, parent PID now: %d\n", getpid(), getppid());
        } 
        else { 
            printf("Parent process (PID: %d) exiting\n", getpid());
            exit(0);
        }
    }
    else if (choice == 2) { // Zombie Process
        if (pid == 0) { 
            printf("Child process (PID: %d) ending\n", getpid());
            exit(0); 
        } 
        else { 
            printf("Parent process (PID: %d) sleeping, child PID: %d\n", getpid(), pid);
            sleep(10); 
            wait(NULL);
            printf("Parent process exiting, child has been reaped\n");
        }
    }
    else {
        printf("Invalid choice\n");
    }
    return 0;
}
