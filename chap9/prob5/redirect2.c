#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <output_file> <command> [args...]\n", argv[0]);
        return 1;
    }

    int child, pid, fd, status;

    pid = fork();
    if (pid < 0) {
        perror("fork");
        return 1;
    }

    if (pid == 0) {
        fd = open(argv[1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
        if (fd < 0) {
            perror("open");
            exit(1);
        }
        if (dup2(fd, STDOUT_FILENO) < 0) {
            perror("dup2");
            close(fd);
            exit(1);
        }
        close(fd);

        execvp(argv[2], &argv[2]);
        fprintf(stderr, "%s: execution failed\n", argv[2]);
        exit(1);

    } else {
        child = wait(&status);
        printf("[%d] child process %d end\n", getpid(), child);
    }

    return 0;
}

