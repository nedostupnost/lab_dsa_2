#include "libs/bstree.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

int getRand(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    srand(time(NULL));
    const int max_words = 200000;
    char *words[max_words];
    int word_count = 0;

    // Загрузка слов из файла
    FILE *file = fopen("dict.txt", "r");

    char buffer[1024];
    while (fgets(buffer, sizeof(buffer), file) && word_count < max_words) {
        buffer[strcspn(buffer, "\n")] = 0; // Удаление символа новой строки
        words[word_count++] = strdup(buffer);
    }
    fclose(file);

    // Создание корня дерева
    struct bstree *tree = bstree_create(words[0], 0);
    clock_t t;

    // Добавление слов в дерево и измерение времени поиска
    for (int i = 2; i <= word_count; ++i) {
        tree = bstree_add(tree, words[i - 1], i - 1);

        if (i % 10000 == 0) {
            int test_count = 1000; // Количество тестов для усреднения времени
            double time_accum = 0;

            for (int j = 0; j < test_count; ++j) {
                int random_index = getRand(0, i - 1);
                t = clock();
                struct bstree *node = bstree_lookup(tree, words[random_index]);
                t = clock() - t;
                time_accum += ((double)t) / CLOCKS_PER_SEC;
            }

            double average_time = time_accum / test_count;
            printf("n = %d; average time = %.10lf microseconds\n", i, average_time * (10*10*10*10*10));
        }
    }

    // Освобождение памяти
    for (int i = 0; i < word_count; ++i) {
        free(words[i]);
    }
}