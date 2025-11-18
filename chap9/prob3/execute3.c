#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int child, pid, status;

    if (argc < 2) {
        fprintf(stderr, "Usage: %s <command> [args...]\n", argv[0]);
        exit(1);
    }

    pid = fork();

    if (pid == 0) {
        execvp(argv[1], &argv[1]);
        fprintf(stderr, "%s: execution failed\n", argv[1]);
        exit(1);
    } 
    else {
        child = wait(&status);
        printf("[%d] child process %d end\n", getpid(), child);
        printf("\tenc code %d\n", status >> 8);
    }

    return 0;
}

