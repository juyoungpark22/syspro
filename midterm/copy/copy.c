#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *src, *dest;
    int ch, option;

    if (argc != 4) {
        printf("Usage: %s <option> <source> <destination>\n", argv[0]);
        return 1;
    }

    option = atoi(argv[1]);
    src = fopen(argv[2], "r");
    if (src == NULL) {
        printf("Error opening source file.\n");
        return 1;
    }

    dest = fopen(argv[3], "w");
    if (dest == NULL) {
        printf("Error creating destination file.\n");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF) {
        if (option == 1)
            ch = tolower(ch);
        else if (option == 2)
            ch = toupper(ch);
        fputc(ch, dest);
    }

    fclose(src);
    fclose(dest);

    printf("File copy completed.\n");
    return 0;
}

