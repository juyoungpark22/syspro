#include <stdio.h>

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
    Book books[4] = {
        {1, "1984", "George", 1949, 7, 0},
        {2, "Luster", "Raven", 2020, 3, 1},
        {3, "Hamnet", "Maggie", 2020, 1, 0},
        {4, "theWish", "Nocholas", 2021, 2, 1}
    };

    for (int i = 0; i < 3; i++) {
        for (int j = i + 1; j < 4; j++) {
            if (books[i].year < books[j].year) {
                Book temp = books[i];
                books[i] = books[j];
                books[j] = temp;
            }
        }
    }

    fp = fopen("db.txt", "w");
    if (fp == NULL) {
        printf("File open error.\n");
        return 1;
    }

    for (int i = 0; i < 4; i++) {
        fprintf(fp, "%d %s %s %d %d %d\n",
                books[i].id, books[i].name, books[i].author,
                books[i].year, books[i].numofborrow, books[i].borrow);
    }

    fclose(fp);
    printf("Books saved in descending order of year.\n");
    return 0;
}

