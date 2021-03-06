#include <unistd.h>
//#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    uint8_t tmp = 11;
    pid_t my_pid = getpid();

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
        pid_t son_pid = getpid();
        pid_t p_pid = my_pid;

        printf("S: I'm the son! My pid: %d\r\n", (uint8_t) son_pid);
        printf("S: tmp start value: %d\r\n", tmp);
        printf("S: tmp after modification value: %d\r\n", tmp-1);
        printf("S: parent's pid: %d\r\n", (uint8_t) p_pid);
        printf("\n");
        //exit(0);
    }

    if(pid > 0)
    {
        pid_t son_pid = pid;

        printf("F: I'm the father! My pid: %d\r\n", (uint8_t) my_pid);
        printf("F: tmp start value: %d\r\n", tmp);
        printf("F: tmp after modification value: %d\r\n", tmp+1);
        printf("F: son's pid: %d\r\n", (uint8_t) son_pid);
        printf("\n");
        //exit(0);
    }

    return 0;
}