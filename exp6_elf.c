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
    double totalTime = 0, insertTime, searchTime;
    int totalCollisions = 0; // Общее количество коллизий

    // Вставка элементов в хеш-таблицу
    for (int i = 0; i < count; i++) {
        int collisions = hashTableInsertELF(hashTable, words[i], i);
        totalCollisions += collisions;
        if ((i + 1) % 10000 == 0)
        {
            printf("Collisions at index %d: %d\n", i + 1, totalCollisions);
        }
    }

    // Измерение времени поиска для разных диапазонов индексов
    for (int range = 1; range <= 20; range++) { // Диапазоны от 10000 до 200000 с шагом 10000
        int endIndex = range * 10000;
        double totalSearchTime = 0;

        for (int experiment = 0; experiment < 1000; experiment++) {
            int randomIndex = rand() % (endIndex + 1); // Случайный индекс в текущем диапазоне
            start = clock();
            int result = hashTableSearchELF(hashTable, words[randomIndex]);
            end = clock();
            searchTime = (double)(end - start) / CLOCKS_PER_SEC;
            totalSearchTime += searchTime;
        }

        double averageSearchTime = totalSearchTime / 1000;
        printf("Average search time for range %d: %.5lf microseconds\n", endIndex, averageSearchTime*(10*10*10*10*10));
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
