#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

#define MAX 1024

void run_command(char *cmd);

int main() {
    char input[MAX];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = 0; // remove newline

        char *command = strtok(input, ";");
        while (command != NULL) {
            run_command(command);
            command = strtok(NULL, ";");
        }
    }
    return 0;
}

void run_command(char *cmd) {
    char *args[MAX];
    int background = 0;
    int in_fd = -1, out_fd = -1;

    while (*cmd == ' ') cmd++;

    int len = strlen(cmd);
    if (len > 0 && cmd[len - 1] == '&') {
        background = 1;
        cmd[len - 1] = '\0'; // remove '&'
    }

    char *infile = strstr(cmd, "<");
    if (infile != NULL) {
        *infile = '\0';
        infile++;
        while (*infile == ' ') infile++;
        in_fd = open(infile, O_RDONLY);
        if (in_fd < 0) {
            perror("input open error");
            return;
        }
    }

    char *outfile = strstr(cmd, ">");
    if (outfile != NULL) {
        *outfile = '\0';
        outfile++;
        while (*outfile == ' ') outfile++;
        out_fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (out_fd < 0) {
            perror("output open error");
            return;
        }
    }

    int i = 0;
    char *token = strtok(cmd, " ");
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

    if (args[0] == NULL)
        return;

    pid_t pid = fork();

    if (pid == 0) {
        if (in_fd >= 0) {
            dup2(in_fd, STDIN_FILENO);
            close(in_fd);
        }
        if (out_fd >= 0) {
            dup2(out_fd, STDOUT_FILENO);
            close(out_fd);
        }

        execvp(args[0], args);
        perror("execvp error");
        exit(1);
    } 
    else {
        if (!background)
            waitpid(pid, NULL, 0);
        else
            printf("[background pid: %d]\n", pid);
    }
}
