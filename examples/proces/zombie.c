#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child_pid;
    pid_t parent_pid;

    parent_pid = getpid();
    child_pid = fork();

    if(child_pid == 0)
    {
        pid_t  my_pid = getpid();
        printf("C-%d: I'm zombie child\r\n", my_pid);
        printf("\n");
        exit(0);

    }else if(child_pid > 0){

        printf("P-%d: I'm parent\r\n", parent_pid);
        printf("P-%d: sleep\r\n", parent_pid);
        printf("\n");
        sleep(60);
        printf("P-%d: wake up\r\n", parent_pid);
        pid_t child_pid2 = waitpid(child_pid,NULL,WUNTRACED);
        printf("P-%d: join with child %d\r\n", parent_pid, child_pid2);
    }
    return 0;
}