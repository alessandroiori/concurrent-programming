#include <unistd.h>
//#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    pid_t pid;
    pid = fork();


    if(pid == -1)
    {
        //printf(stderr, "fork error\r\t");
        printf("ERROR: fork error\r\n");
        exit(1);
    }

    if(pid == 0)
    {
        printf("I'm the son! My pid: %d\r\n", (uint8_t) pid);
        exit(0);
    }

    if(pid > 0)
    {
        printf("I'm the father! Son's pid: %d\r\n", (uint8_t) pid);
        exit(0);
    }

    return 0;
}