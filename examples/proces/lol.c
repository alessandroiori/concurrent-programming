#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
    pid_t child_pid;
    child_pid = fork();

    if(child_pid == 0)
    {
        pid_t new_process_pid = getpid();
        printf("I'm %d LOL process!\r\n", new_process_pid);
        char* args[] = {"./lol", (char*) NULL};
        execvp("./lol", args);
        printf(stderr, "Error on %d LOL process", new_process_pid);
    }
    return 0;
}