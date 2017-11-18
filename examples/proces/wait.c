#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
    pid_t pid;
    pid = fork();

    if(pid == 0)
    {
        //I'm the soon
        uint8_t sleep_sec = 5;
        pid_t my_pid = getpid();
        printf("S-%d: I'm the soon\r\n", my_pid);
        printf("S-%d: sleep for %ds\r\n", my_pid, sleep_sec);
        sleep(sleep_sec);
        printf("S-%d: wakeup\r\n", my_pid);
        //while(1);
        exit(0);
    }else if(pid > 0){
        //I'm the parent
        pid_t my_pid = getpid();
        printf("P-%d: I'm the parent\r\n", my_pid);
        printf("P-%d: waiting son %d\r\n", my_pid, pid);
        pid_t s_pid = wait(NULL);
        while(s_pid!=pid)
        {
            s_pid = wait(NULL);
        }
        printf("P-%d: son with pid %d ended\r\n", my_pid, s_pid);
        //while (1);
        exit(0);
    }else if(pid == -1){
        //Error on fork
        printf("ERROR: fork error");
        exit(1);
    }

    return 0;
}