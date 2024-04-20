#include "libs/hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Загрузка слов из файла
int loadWords(char *filename, char **words) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Unable to open file");
        return 0;
    }

    char buffer[1024];
    int i = 0;
    while (fgets(buffer, 1024, file)) {
        buffer[strlen(buffer) - 1] = '\0'; // Удаление новой строки
        words[i++] = strdup(buffer);
    }
    fclose(file);
    return i;
}

int main() {
    char *words[200000];
    int count = loadWords("dict.txt", words);

    // Создание и инициализация хеш-таблицы в функции main
    HashItem **hashTable = (HashItem**) calloc(TABLE_SIZE, sizeof(HashItem*));
    initHashTable(hashTable);

    srand(time(NULL));
    clock_t start, end;
    double totalTime = 0, insertTime;

    for (int i = 0; i < count; i++) {
        start = clock();
        hashTableInsert(hashTable, words[i], i);
        end = clock();
        insertTime = (double)(end - start) / CLOCKS_PER_SEC;

        if ((i + 1) % 10000 == 0) {
            printf("n = %d; insert time = %.6lf microseconds\n", i + 1, insertTime * (10*10));
        }
    }

    // Очистка памяти
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashTable[i]) {
            free(hashTable[i]->key);
            free(hashTable[i]);
        }
    }
    free(hashTable);

    for (int i = 0; i < count; i++) {
        free(words[i]);
    }

    return 0;
}