// 基于哈希表 table.c 扩展的符号表

// 创建符号表
struct SymbolTable *SymbolCreate();

// 将 name 哈希后插入 symbol 数组中对应的下标
struct Symbol *SymbolHash(char* name);

// 插入 key-value 对
void SymbolInsert(struct HashTable *table, struct Symbol *key, void * value);

// 查找
void *SymbolFind(struct HashTable *table, struct Symbol *key);

// 初始化
void *SymbolInit(struct HashTable *table);

// 清空符号表
void SymbolClear(struct HashTable *table);

// 重初始化符号表，不断 pop 直到只剩下 firstSymbol（通过比较地址判断是否为 firstSymbol）
void SymbolReinit(struct HashTable *table);

void SymbolCallBack(struct HashTable *table, void (*f)(struct Symbol *key, void *value));