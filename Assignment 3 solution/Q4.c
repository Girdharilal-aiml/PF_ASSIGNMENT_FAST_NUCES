#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Book {
    int id;  
    int popularity; 
    int lastUsed; 
    int isHere;  
};

struct Shelf {
    struct Book* books;
    int maxBooks;        
    int currentBooks;    
    int timeCounter;     
};

void setupShelf(struct Shelf* shelf, int capacity) {
    shelf->maxBooks = capacity;
    shelf->currentBooks = 0;
    shelf->timeCounter = 0;
    shelf->books = (struct Book*)malloc(capacity * sizeof(struct Book));
    for (int i = 0; i < capacity; i++) {
        shelf->books[i].isHere = 0;
    }
}
int findBookOnShelf(struct Shelf* shelf, int bookId) {
    for (int i = 0; i < shelf->maxBooks; i++) {
        if (shelf->books[i].isHere == 1 && shelf->books[i].id == bookId) {
            return i;
        }
    }
    return -1;
}
int findOldestBook(struct Shelf* shelf) {
    int oldestTime = shelf->timeCounter + 1;
    int oldestIndex = -1;
    
    for (int i = 0; i < shelf->maxBooks; i++) {
        if (shelf->books[i].isHere == 1 && shelf->books[i].lastUsed < oldestTime) {
            oldestTime = shelf->books[i].lastUsed;
            oldestIndex = i;
        }
    }
    return oldestIndex;
}
void addBookToShelf(struct Shelf* shelf, int bookId, int popularityScore) {
    int position = findBookOnShelf(shelf, bookId);
    if (position != -1) {
        shelf->books[position].popularity = popularityScore;
        shelf->books[position].lastUsed = ++(shelf->timeCounter);
        return;
    }
    if (shelf->currentBooks == shelf->maxBooks) {
        int oldestPos = findOldestBook(shelf);
        if (oldestPos != -1) {
            shelf->books[oldestPos].isHere = 0;
            shelf->currentBooks--;
            position = oldestPos;
        }
    }
    if (position == -1) {
        for (int i = 0; i < shelf->maxBooks; i++) {
            if (shelf->books[i].isHere == 0) {
                position = i;
                break;
            }
        }
    }
    if (position != -1) {
        shelf->books[position].id = bookId;
        shelf->books[position].popularity = popularityScore;
        shelf->books[position].lastUsed = ++(shelf->timeCounter);
        shelf->books[position].isHere = 1;
        shelf->currentBooks++;
    }
}
int accessBookOnShelf(struct Shelf* shelf, int bookId) {
    int position = findBookOnShelf(shelf, bookId);
    if (position == -1) {
        return -1;
    }
    shelf->books[position].lastUsed = ++(shelf->timeCounter);   
    return shelf->books[position].popularity;
}
int main() {
    int shelfSize, numberOfOperations;
    printf("=== Library Shelf System ===\n");
    printf("Enter shelf capacity and number of operations: ");
    scanf("%d %d", &shelfSize, &numberOfOperations);
    struct Shelf myShelf;
    setupShelf(&myShelf, shelfSize);
    char command[10];
    int bookId, popularity;
    for (int i = 0; i < numberOfOperations; i++) {
        printf("\nOperation %d: ", i + 1);
        scanf("%s", command);
        if (strcmp(command, "ADD") == 0) {
            scanf("%d %d", &bookId, &popularity);
            addBookToShelf(&myShelf, bookId, popularity);
            printf("   Book ID %d added/updated with popularity %d\n", bookId, popularity);
        } 
        else if (strcmp(command, "ACCESS") == 0) {
            scanf("%d", &bookId);
            int result = accessBookOnShelf(&myShelf, bookId);
            printf("   Popularity of Book ID %d: %d\n", bookId, result);
        } 
        else {
            printf("   Error: Unknown command '%s'\n", command);
            i--;
        }
    }
    free(myShelf.books);
    return 0;
}