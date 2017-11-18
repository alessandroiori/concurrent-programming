#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    pid_t parent_pid = getpid();

    pid_t child_pid;
    child_pid = fork();

    if(child_pid < 0)
    {
        fprintf(stderr, "fork error\r\n");
        exit(1);

    } else if(child_pid == 0) {
        pid_t child_pid = getpid();

        printf("C%d: I'm children!\r\n", child_pid);
        printf("C%d: exe new code\r\n", child_pid);

        execlp("echo", "echo", "Hello,", "world", "!", (char*) NULL);
        fprintf(stderr, "ecexlp error\r\n");
        exit(1);

    } else if(child_pid > 0) {

        printf("P%d: I'm the parent!\r\n", parent_pid);
        printf("P%d: sleep\r\n", parent_pid);
        sleep(5);
        printf("P%d: wake up and exit\r\n", parent_pid);
        exit(0);
    }

    return 0;
}