#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct TextEditor {
    char** lines;
    int totalLines;
    int maxLines;
};

struct TextEditor* startEditor(int size) {
    struct TextEditor* editor = malloc(sizeof(struct TextEditor));
    editor->totalLines = 0;
    editor->maxLines = size;
    editor->lines = malloc(size * sizeof(char*));
    for (int i = 0; i < size; i++) {
        editor->lines[i] = NULL;
    }
    return editor;
}

void addNewLine(struct TextEditor* editor, char* text) {
    if (editor->totalLines >= editor->maxLines) {
        editor->maxLines = editor->maxLines * 2;
        editor->lines = realloc(editor->lines, editor->maxLines * sizeof(char*));
    }
    editor->lines[editor->totalLines] = malloc(strlen(text) + 1);
    strcpy(editor->lines[editor->totalLines], text);
    editor->totalLines++;
}

void putLineAt(struct TextEditor* editor, int position, char* text) {
    if (position < 0 || position > editor->totalLines) return;
    if (editor->totalLines >= editor->maxLines) {
        editor->maxLines = editor->maxLines * 2;
        editor->lines = realloc(editor->lines, editor->maxLines * sizeof(char*));
    }
    for (int i = editor->totalLines; i > position; i--) {
        editor->lines[i] = editor->lines[i - 1];
    }
    editor->lines[position] = malloc(strlen(text) + 1);
    strcpy(editor->lines[position], text);
    editor->totalLines++;
}

void removeLine(struct TextEditor* editor, int position) {
    if (position < 0 || position >= editor->totalLines) return;
    free(editor->lines[position]);
    for (int i = position; i < editor->totalLines - 1; i++) {
        editor->lines[i] = editor->lines[i + 1];
    }
    editor->totalLines--;
    editor->lines[editor->totalLines] = NULL;
}

void showAllLines(struct TextEditor* editor) {
    for (int i = 0; i < editor->totalLines; i++) {
        printf("%d: %s\n", i, editor->lines[i]);
    }
}

void makeCompact(struct TextEditor* editor) {
    if (editor->totalLines < editor->maxLines) {
        editor->maxLines = editor->totalLines;
        editor->lines = realloc(editor->lines, editor->maxLines * sizeof(char*));
    }
}

void writeToFile(struct TextEditor* editor, char* filename) {
    FILE* file = fopen(filename, "w");
    for (int i = 0; i < editor->totalLines; i++) {
        fprintf(file, "%s\n", editor->lines[i]);
    }
    fclose(file);
}

struct TextEditor* readFromFile(char* filename) {
    FILE* file = fopen(filename, "r");
    if (!file) return NULL;
    struct TextEditor* editor = startEditor(10);
    char singleLine[1000];
    while (fgets(singleLine, sizeof(singleLine), file)) {
        singleLine[strcspn(singleLine, "\n")] = '\0';
        addNewLine(editor, singleLine);
    }
    fclose(file);
    return editor;
}

void clearEverything(struct TextEditor* editor) {
    for (int i = 0; i < editor->totalLines; i++) {
        free(editor->lines[i]);
    }
    free(editor->lines);
    free(editor);
}

int main() {
    struct TextEditor* myEditor = startEditor(5);
    addNewLine(myEditor, "First line of text");
    addNewLine(myEditor, "Second line");
    addNewLine(myEditor, "Third line");
    printf("After adding 3 lines:\n");
    showAllLines(myEditor);
    printf("\n");
    putLineAt(myEditor, 1, "Inserted at position 1");
    printf("After inserting at position 1:\n");
    showAllLines(myEditor);
    printf("\n");
    removeLine(myEditor, 2);
    printf("After deleting line 2:\n");
    showAllLines(myEditor);
    printf("\n");
    writeToFile(myEditor, "output.txt");
    printf("Saved to file.\n");
    clearEverything(myEditor);
    return 0;
}