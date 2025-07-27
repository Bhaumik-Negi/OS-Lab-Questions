#include <stdio.h>
#include <dirent.h> 
#include <stdlib.h> 
int main()
{
    DIR *dir;
    struct dirent *entry;
    char path[] = "."; 
    dir = opendir(path);
    if (dir == NULL)
    {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }
    printf("Contents of directory: %s\n", path);
    while ((entry = readdir(dir)) != NULL)
    {
        printf("%s\n", entry->d_name); 
    }
    closedir(dir);
    return 0;
}
