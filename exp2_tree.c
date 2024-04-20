#include "libs/bstree.h"
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int getRand(int min, int max) {
    return min + rand() % (max - min + 1);
}

int main() {
    const int max_words = 200000;
    char *words[max_words];
    int word_count = 0;

    // Загрузка слов из файла
    FILE *file = fopen("dict.txt", "r");

    char buffer[101];
    while (fgets(buffer, sizeof(buffer), file) && word_count < max_words) {
        buffer[strcspn(buffer, "\n")] = 0;
        words[word_count++] = strdup(buffer);
    }
    fclose(file);

    struct bstree *tree = NULL;
    clock_t t;
    int start = 0;

    for (int i = 10000; i <= max_words; i += 10000) {
        t = clock();
        for (int j = start; j < i; ++j) {
            tree = bstree_add(tree, words[j], j);
        }
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC;
        printf("Added %d elements; time = %.10lf microseconds\n", i, time_taken * (10*10*10*10*10*10));
        start = i;
    }

}