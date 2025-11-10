#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

extern char **environ;

void print_usage(char *progname) {
    fprintf(stderr,
        "Usage: %s [option]\n"
        "  -e [NAME] : print environment variable(s)\n"
        "  -u        : print real / effective user ID\n"
        "  -g        : print real / effective group ID\n"
        "  -i        : print process ID\n"
        "  -p        : print parent process ID\n",
        progname);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        print_usage(argv[0]);
        return 1;
    }

    if (strncmp(argv[1], "-e", 2) == 0) {
        char *name = NULL;
        if (strlen(argv[1]) > 2) {
            name = argv[1] + 2;
        } else if (argc >= 3) {
            name = argv[2];
        }

        if (name == NULL) {
            char **envp = environ;
            while (*envp != NULL) {
                printf("%s\n", *envp);
                envp++;
            }
        } else {
            char *value = getenv(name);
            if (value != NULL)
                printf("%s = %s\n", name, value);
            else
                printf("%s is not defined.\n", name);
        }
    } else if (strcmp(argv[1], "-u") == 0) {
        uid_t ruid = getuid();
        uid_t euid = geteuid();
        struct passwd *rpw = getpwuid(ruid);
        struct passwd *epw = getpwuid(euid);

        printf("My Realistic User ID : %d(%s)\n",
               (int)ruid, rpw ? rpw->pw_name : "unknown");
        printf("My Valid User ID : %d(%s)\n",
               (int)euid, epw ? epw->pw_name : "unknown");
    } else if (strcmp(argv[1], "-g") == 0) {
        gid_t rgid = getgid();
        gid_t egid = getegid();
        struct group *rg = getgrgid(rgid);
        struct group *eg = getgrgid(egid);

        printf("My Realistic Group ID : %d(%s)\n",
               (int)rgid, rg ? rg->gr_name : "unknown");
        printf("My Valid Group ID : %d(%s)\n",
               (int)egid, eg ? eg->gr_name : "unknown");
    } else if (strcmp(argv[1], "-i") == 0) {
        pid_t pid = getpid();
        printf("my process number : [%d]\n", (int)pid);
    } else if (strcmp(argv[1], "-p") == 0) {
        pid_t ppid = getppid();
        printf("my parent's process number : [%d]\n", (int)ppid);
    } else {
        print_usage(argv[0]);
        return 1;
    }

    return 0;
}

