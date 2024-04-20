#include "hashtab.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Инициализация хеш-таблицы
void initHashTable(HashItem **hashTable) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

// Хеш-функция (метод Рабина-Карпа)
unsigned long hash(char *str) {
    unsigned long hash = 0;
    int c;
    while ((c = *str++)) {
        hash = hash * 131 + c;
    }
    return hash % TABLE_SIZE;
}

// Хеш-функция метод ELF (Executable and Linkable Format)
unsigned long hashELF(char *str) { 
    unsigned long hash = 0, x;
    while (*str) {
        hash = (hash << 4) + (*str++);
        if ((x = hash & 0xF0000000L) != 0) { // старшие 4 бита сдвигаются на 24 бита вправо
            hash ^= (x >> 24);
            hash &= ~x; // (и не) между исходных и битовой инверсией
        }
    }
    return hash % TABLE_SIZE;
}


// Вставка элемента в хеш-таблицу
int hashTableInsert(HashItem **hashTable, char *key, int value) {
    unsigned long index = hash(key); // Получение начального индекса
    HashItem *item = (HashItem*) malloc(sizeof(HashItem));
    item->key = strdup(key);
    item->value = value;
    
    int attempts = 0; // Количество попыток вставки
    
    // Обработка коллизий
    while (hashTable[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
        attempts++;
    }
    hashTable[index] = item;
    
    return attempts;
}

int hashTableInsertELF(HashItem **hashTable, char *key, int value) {
    unsigned long index = hashELF(key);
    HashItem *item = (HashItem*) malloc(sizeof(HashItem));
    item->key = strdup(key);
    item->value = value;
    
    int attempts = 0; // Количество попыток вставки
    
    // Обработка коллизий
    while (hashTable[index] != NULL) {
        index = (index + 1) % TABLE_SIZE;
        attempts++;
    }
    hashTable[index] = item;
    
    return attempts;
}

// Поиск элемента в хеш-таблице
int hashTableSearch(HashItem **hashTable, char *key) {
    unsigned long index = hash(key);
    while (hashTable[index] != NULL) {
        if (strcmp(hashTable[index]->key, key) == 0) {
            return hashTable[index]->value;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return NULL;
}

int hashTableSearchELF(HashItem **hashTable, char *key) {
    unsigned long index = hashELF(key);
    while (hashTable[index] != NULL) {
        if (strcmp(hashTable[index]->key, key) == 0) {
            return hashTable[index]->value;
        }
        index = (index + 1) % TABLE_SIZE;
    }
    return NULL;
}