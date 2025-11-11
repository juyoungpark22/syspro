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
    if (argc != 3) {
        printf("Usage: %s <0:borrow | 1:return> <bookId>\n", argv[0]);
        return 1;
    }

    int mode = atoi(argv[1]);
    int targetId = atoi(argv[2]);
    Book books[100];
    int count = 0;

    FILE *fp = fopen("db.txt", "r");
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

    printf("0 bookId: borrow book, 1 bookId: return book ) %d %d\n", mode, targetId);

    for (int i = 0; i < count; i++) {
        if (books[i].id == targetId) {
            if (mode == 0) {  // borrow
                if (books[i].borrow == 1) {
                    printf("You cannot borrow bellow book since it has been booked.\n");
                } else {
                    books[i].borrow = 1;
                    books[i].numofborrow++;
                    printf("You've got bellow book..\n");
                }
            } else if (mode == 1) {  // return
                if (books[i].borrow == 0) {
                    printf("This book was not borrowed.\n");
                } else {
                    books[i].borrow = 0;
                    printf("You've returned bellow book..\n");
                }
            }

            printf("id  bookname  author  year  numofborrow  borrow\n");
            printf("%d  %s  %s  %d  %d  %s\n",
                   books[i].id, books[i].name, books[i].author,
                   books[i].year, books[i].numofborrow,
                   books[i].borrow ? "True" : "False");
        }
    }

    fp = fopen("db.txt", "w");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d %s %s %d %d %d\n",
                books[i].id, books[i].name, books[i].author,
                books[i].year, books[i].numofborrow, books[i].borrow);
    }
    fclose(fp);

    return 0;
}

