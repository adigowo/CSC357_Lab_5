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
    limit_fork(300);
    /* continue with program logic here */

    int number = atoi(argv[1]);
    pid_t pid = fork();

    if (pid == -1){

        printf("fork failed");
        exit(EXIT_FAILURE);

    } else if (pid == 0) {

        int i = 1;

        while (i <= number){

            if (i % 2 != 0) { 

                printf("%d\n", i);
                
            }

            i = i + 2;

        }
        exit(EXIT_SUCCESS);

    } else {

        int status;

        wait(&status);

        int i = 2;

        while (i <= number){

            if (i % 2 == 0) { 

                printf("%d\n", i);

            }
            i+= 2;
        }

    }


    return 0;
}




