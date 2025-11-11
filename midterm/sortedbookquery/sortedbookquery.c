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
    Book books[100];
    int count = 0, option;

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

    while (fscanf(fp, "%d %s %s %d %d %d",
                  &books[count].id, books[count].name, books[count].author,
                  &books[count].year, &books[count].numofborrow,
                  &books[count].borrow) == 6) {
        count++;
    }
    fclose(fp);

    for (int i = 0; i < count - 1; i++) {
        for (int j = i + 1; j < count; j++) {
            if (books[i].numofborrow < books[j].numofborrow) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    printf("0: list of all books, 1: list of available books ) %d\n", option);
    printf("id  bookname  author  year  numofborrow  borrow\n");

    for (int i = 0; i < count; i++) {
        if (option == 0)
            printf("%d  %s  %s  %d  %d  %s\n",
                   books[i].id, books[i].name, books[i].author,
                   books[i].year, books[i].numofborrow,
                   books[i].borrow ? "True" : "False");
        else if (option == 1 && books[i].borrow == 1)
            printf("%d  %s  %s  %d  %d  %s\n",
                   books[i].id, books[i].name, books[i].author,
                   books[i].year, books[i].numofborrow,
                   books[i].borrow ? "True" : "False");
    }

    return 0;
}

