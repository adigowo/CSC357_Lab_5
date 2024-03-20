#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <ctype.h>
#include <stdbool.h>


void limit_fork(rlim_t max_procs)
{
    struct rlimit rl;
    if (getrlimit(RLIMIT_NPROC, &rl))
    {
        perror("getrlimit");
        exit(-1);
    }
    else
    {
        // printf("Current max processes limit: %lu\n", (unsigned long)rl.rlim_cur);
        // printf("Max processes limit (hard limit): %lu\n", (unsigned long)rl.rlim_max);
    }
    rl.rlim_cur = max_procs;
    if (setrlimit(RLIMIT_NPROC, &rl))
    {
        perror("setrlimit");
        exit(-1);
    }
}

int main(int argc, char *argv[])
{
  //  limit_fork(300);
    /* continue with program logic here */

    int number = atoi(argv[1]);
    pid_t pid1 = fork();
    
    if (pid1 == 0){

        int xec1 = execl("./odds", "odds", argv[1], (char *)NULL);

        if (xec1 == -1){
            printf("odds");
            exit(EXIT_FAILURE);
        }

    }

    pid_t pid2 = fork();
    
    if (pid2 == 0){

        int xec2 = execl("./evens", "evens", argv[1], (char *)NULL);

        if (xec2 == -1){
            printf("odds");
            exit(EXIT_FAILURE);
        }

    }

    int status;
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);

    return 0;
}




