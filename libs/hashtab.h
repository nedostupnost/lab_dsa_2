#define TABLE_SIZE 500000

// Элемент хеш-таблицы
typedef struct {
  char *key;
  int value;
} HashItem;

void initHashTable(HashItem **hashTable);
unsigned long hashELF(char *str);
unsigned long hash(char *str);
int hashTableInsert(HashItem **hashTable, char *key, int value);
int hashTableInsertELF(HashItem **hashTable, char *key, int value);
int hashTableSearch(HashItem **hashTable, char *key);
int hashTableSearchELF(HashItem **hashTable, char *key);