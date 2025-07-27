#include <stdio.h>
#include <unistd.h> 
#include <stdlib.h> 
int main()
{
    printf("Before execlp\n");
    execlp("ls", "ls", "-l", NULL);
    perror("execlp failed");
    exit(1);
    return 0;
}
