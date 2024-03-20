#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <ctype.h>
#include <stdbool.h>
#include <fcntl.h>
#include <sys/stat.h>


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
    int description = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);


    if (dup2(description, STDOUT_FILENO) == -1) {

        close(description);
        return EXIT_FAILURE;
    }

    close(description);

    execvp(argv[1], &argv[1]);
    return EXIT_FAILURE;

}