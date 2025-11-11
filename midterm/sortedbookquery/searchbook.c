#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[50];
    char author[50];
    int year;
    int numofborrow;
    int borrow;
} Book;

int main() {
    FILE *fp;
    Book b;
    char search[50];
    int found = 0;

    fp = fopen("db.txt", "r");
    if (fp == NULL) {
        printf("File open error.\n");
        return 1;
    }

    printf("input name of book ) ");
    scanf("%s", search);

    while (fscanf(fp, "%d %s %s %d %d %d",
                  &b.id, b.name, b.author, &b.year,
                  &b.numofborrow, &b.borrow) == 6) {
        if (strcmp(b.name, search) == 0) {
            printf("id  bookname  author  year  numofborrow  borrow\n");
            printf("%d  %s  %s  %d  %d  %s\n",
                   b.id, b.name, b.author, b.year,
                   b.numofborrow, b.borrow ? "True" : "False");
            found = 1;
            break;
        }
    }

    if (!found)
        printf("not found book name : '%s'\n", search);

    fclose(fp);
    return 0;
}

