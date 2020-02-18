#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "table.h"
#include "symbol.h"
#define SYMBOLSIZE 109

struct Symbol
{
    char* name;
    struct Symbol* next;
};

static struct Symbol firstSymbol = {"<mark>", 0};
static struct Symbol *hashTable[SYMBOLSIZE];

static struct Symbol *newSymbol(char* name, struct Symbol* next)
{
    struct Symbol* symbol;

    symbol = malloc(sizeof(struct Symbol));
    if(symbol == NULL) {
        fprintf(stderr, "MLE!\n");
        exit(1);
    }
    symbol -> name = name;
    symbol -> next = next;

    return symbol;
}

static unsigned int hash(char *s)
{
    unsigned int base;
    char* ch;

    base = 0;
    ch = s;
    while(*ch != '\0') {
        base = base * 998244353 + *ch;
        ch ++;
    }

    return base;
}

struct Symbol *SymbolHash(char* name)
{
    int index;
    struct Symbol *symbol;
    struct Symbol *new;

    index = hash(name) % SYMBOLSIZE;
    symbol = hashTable[index];
    for(struct Symbol *i = symbol; i; i = symbol -> next) {
        if(!strcmp(symbol -> name, name)) {
            return i;
        }
    }
    new = newSymbol(name, symbol);
    hashTable[index] = new;

    return new;
}

struct SymbolTable *SymbolCreate()
{
    return HashTableTCreate();
}

void SymbolInsert(struct HashTable *table, struct Symbol *key, void * value)
{
    HashTableInsert(table, key, value);
}

void *SymbolFind(struct HashTable *table, struct Symbol *key)
{
    return HashTableFind(table, key);
}

void *SymbolInit(struct HashTable *table)
{
    // firstSymbol = {"<mark>", 0};
    SymbolInsert(table, &firstSymbol, NULL);
}

void SymbolReinit(struct HashTable *table)
{
    struct Symbol *symbol;

    symbol = HashTablePop(table);
    while(symbol != &firstSymbol) {
        free(symbol);
        symbol = HashTablePop(table);
    }
}

void SymbolClear(struct HashTable *table)
{
    HashTableClear(table);
}

void SymbolCallBack(struct HashTable *table, void (*f)(struct Symbol *key, void *value))
{
    HashTableCallBack(table, (void (*)(void *, void *)) f);
}