#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int id;
    char name[50];
    char author[50];
    int year;
    int numofborrow;
    int borrow;
} Book;

int main(int argc, char *argv[]) {
    FILE *fp;
    Book b;
    int option;

    if (argc != 2) {
        printf("Usage: %s <0:all | 1:available>\n", argv[0]);
        return 1;
    }

    option = atoi(argv[1]);
    fp = fopen("db.txt", "r");
    if (fp == NULL) {
        printf("File open error.\n");
        return 1;
    }

    printf("id  bookname  author  year  numofborrow  borrow\n");

    while (fscanf(fp, "%d %s %s %d %d %d",
                  &b.id, b.name, b.author, &b.year,
                  &b.numofborrow, &b.borrow) == 6) {
        if (option == 0)
            printf("%d  %s  %s  %d  %d  %s\n",
                   b.id, b.name, b.author, b.year,
                   b.numofborrow, b.borrow ? "True" : "False");
        else if (option == 1 && b.borrow == 1)
            printf("%d  %s  %s  %d  %d  %s\n",
                   b.id, b.name, b.author, b.year,
                   b.numofborrow, b.borrow ? "True" : "False");
    }

    fclose(fp);
    return 0;
}

