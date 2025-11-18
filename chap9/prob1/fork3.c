#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid1, pid2;

    pid1 = fork();

    if (pid1 < 0) {
        perror("fork1 error");
        exit(1);
    }

    if (pid1 == 0) {
        printf("[Child 1] : Hello, world ! pid=%d\n", getpid());
        return 0;
    } 
    else {
        pid2 = fork();

        if (pid2 < 0) {
            perror("fork2 error");
            exit(1);
        }

        if (pid2 == 0) {
            printf("[Child 2] : Hello, world ! pid=%d\n", getpid());
            return 0;
        }
        else {
            printf("[Parent] : Hello, world ! pid=%d\n", getpid());
        }
    }

    return 0;
}

