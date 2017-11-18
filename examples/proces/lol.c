#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

unsigned long factorial(unsigned long f)
{
    if ( f == 0 )
        return 1;
    return(f * factorial(f - 1));
}

int lolf(void)
{
    pid_t child_pid;
    child_pid = fork();

    if(child_pid == 0 || child_pid > 0) {

        unsigned long f = factorial(10000L);

        pid_t new_process_pid = getpid();
        printf("I'm %d LOL process!\r\n", new_process_pid);
        char* args[] = {"./lol", (char*) NULL};
        execvp("./lol", args);
        fprintf(stderr, "Error on %d LOL process", new_process_pid);

    } else if(child_pid < 0) {
        fprintf(stderr, "ERROR: error fork\r\n");
    }
    return 0;
}

int main(void)
{
    lolf();
    return 0;
}