#include <stdio.h>
#include <stdlib.h>
#include "table.h"
#define TABLESIZE 127

struct Node
{
    void *key;
    void *value;
    struct Node* next;
    void *prevtop;
};

struct HashTable
{
    struct Node *table[TABLESIZE];
    void *top;
};

static struct Node *newNode(void *key, void *value, struct Node* next, void *prevtop)
{
    struct Node* node;

    node = (struct Node*)malloc(sizeof(struct Node));
    if(node == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    node -> key = key;
    node -> value = value;
    node -> next = next;
    node -> prevtop = prevtop;

    return node;
}

// 创建哈希表
struct HashTable *HashTableTCreate()
{
    struct HashTable *table;

    table = (struct HashTable*)malloc(sizeof(struct HashTable));
    if(table == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    table -> top = NULL;
    for(int i = 0; i < TABLESIZE; i ++) {
        table -> table[i] = NULL;
    }

    return table;
}

// 插入 key-value 对
void HashTableInsert(struct HashTable *table, void *key, void * value)
{
    int index;

    index = ((unsigned)key) % TABLESIZE;
    table -> table[index] = newNode(key, value, table -> table[index], table -> top);
    table -> top = key;
}

// 查找
void *HashTableFind(struct HashTable *table, void *key)
{
    int index;

    index = ((unsigned)key) % TABLESIZE;
    for(struct Node* i = table -> table[index]; i; i = i -> next) {
        if(i -> key == key) {
            return i -> value;
        }
    }

    return NULL;
}
     
// 删除最新插入的元素
struct Node *HashTablePop(struct HashTable *table)
{
    int index;
    void *temp;
    struct Node *node;

    temp = table -> top;
    if(temp != NULL) {
        index = ((unsigned)temp) % TABLESIZE;
        node = table -> table[index];
        if(node != NULL) {
            table -> table[index] = node -> next;
            table -> top = node -> prevtop;

            return node;
        }      
    }
    
    return NULL;
}
      
void HashTableCallBack(struct HashTable *table, void (*f)(void *key, void *value)) 
{
    int index;
    void*temp;
    struct Node *node;

    temp = table -> top;
    if(temp != NULL) {
        index = ((unsigned)temp) % TABLESIZE;
        node = table -> table[index];
        if(node != NULL) {
            table -> table[index] = node -> next;
            table -> top = node -> prevtop;
            f(node -> key, node -> value);
            HashTableCallBack(table, f);
            table -> top = temp;
            node -> next = table -> table[index];
            table -> table[index] = node;
        }
    }
}

void HashTableClear(struct HashTable *table)
{
    struct Node *node;

    node = HashTablePop(table);
    while(node != NULL) {
        free(node);
        node = HashTablePop(table);
    }
}

int main()
{

    return 0;
}
