// 创建哈希表
struct HashTable *HashTableTCreate();
  
// 插入 key-value 对
void HashTableInsert(struct HashTable *table, void *key, void * value);

// 查找
void *HashTableFind(struct HashTable *table, void *key);
     
// 删除最新插入的元素
struct Node *HashTableDel(struct HashTable *table);
      
// 清空哈希表
void HashTableClear(struct HashTable *table);

void HashTableCallBack(struct HashTable *table, void (*f)(void *key, void *value));