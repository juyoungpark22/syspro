#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int pid, child, status;

    printf("PARENT: PID = %d  GID = %d\n", getpid(), getpgrp());

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        setpgid(0, 0);
        printf("CHILD:  PID = %d  GID = %d\n", getpid(), getpgrp());
    }

    return 0;
}

