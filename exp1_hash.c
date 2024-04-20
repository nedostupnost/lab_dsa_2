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
    if (count == 0) {
        printf("No words loaded.\n");
        return 1;
    }

    // Создание и инициализация хеш-таблицы в функции main
    HashItem **hashTable = (HashItem**) calloc(TABLE_SIZE, sizeof(HashItem*));
    initHashTable(hashTable);

    srand(time(NULL));
    clock_t start, end;
    double totalTime = 0;

    for (int i = 0; i < count; i++) {
        hashTableInsert(hashTable, words[i], i);

        if ((i + 1) % 10000 == 0) {
            totalTime = 0;
            for (int j = 0; j < 1000; j++) {
                int randIndex = rand() % (i + 1);
                start = clock();
                hashTableSearch(hashTable, words[randIndex]);
                end = clock();
                totalTime += (double)(end - start) / CLOCKS_PER_SEC;
            }
            printf("n = %d; time = %.5lf microseconds\n", i + 1, totalTime * (10*10));
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
