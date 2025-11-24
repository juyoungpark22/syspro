#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX 1024
#define MAXARGS 64

int main() {
    char input[MAX];

    while (1) {
        printf("[shell] ");
        fflush(stdout);

        if (!fgets(input, sizeof(input), stdin))
            break;

        input[strcspn(input, "\n")] = 0;

        if (strlen(input) == 0)
            continue;

        int background = 0;
        int len = strlen(input);

        if (input[len - 1] == '&') {
            background = 1;
            input[len - 1] = '\0';
        }

        char *args[MAXARGS];
        int i = 0;

        char *token = strtok(input, " ");
        while (token != NULL) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL)
            continue;

        pid_t pid = fork();

        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp error");
            exit(1);
        } else {
            if (!background)
                waitpid(pid, NULL, 0);
            else
                printf("[background pid: %d]\n", pid);
        }
    }
    return 0;
}

