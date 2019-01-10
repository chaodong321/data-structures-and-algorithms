
/*
  哈希表的C实现
  查找使用的方法是“除留余数法”，解决冲突使用的方法是“链地址法”。
*/


#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define HASH_TABLE_SIZE 10

//定义哈希表和基本数据节点
typedef struct _Node
{
    int data;
    struct _Node* next;
}Node;

typedef struct _HashTable
{
    Node* bucket[HASH_TABLE_SIZE];
}HashTable;

typedef enum{
    FALSE,
    TRUE
}STATUS;

int hash_func(int key)
{
    return (key%HASH_TABLE_SIZE);
}

//创建哈希表
HashTable* hash_table_create()
{
    HashTable *ht = (HashTable*)malloc(sizeof(HashTable));
    memset(ht, 0, sizeof(HashTable));
    return ht;
}

//销毁哈希表
void hash_table_destroy(HashTable *ht)
{
    unsigned int i;
    for(i = 0; i < HASH_TABLE_SIZE; i++){
        Node *list = ht->bucket[i];
        while(NULL != list){
            Node *node = list;
            list = list->next;
            free(node);
        }
    }
    free(ht);
}

//在哈希表中查找数据
Node* hash_table_find(HashTable *ht, int data)
{
    Node* node;
    if(NULL ==  ht || NULL == (node = ht->bucket[hash_func(data)])){
        return NULL;
    }

    while(node){
        if(data == node->data){
            return node;
        }
        node = node->next;
    }
    return NULL;
}

//在哈希表中插入数据
STATUS hash_table_insert(HashTable *ht, int data)
{
    if(NULL == ht){
        return FALSE;
    }

    Node *node;
    if(NULL == ht->bucket[hash_func(data)]){
        node = (Node*)malloc(sizeof(Node));
        memset(node, 0, sizeof(Node));
        node->data = data;
        ht->bucket[hash_func(data)] = node;
        return TRUE;
    }

    if(NULL != hash_table_find(ht, data)){
        return FALSE;
    }

    node = ht->bucket[hash_func(data)];
    while(NULL != node->next){
        node = node->next;
    }

    Node *new_node;
    new_node = (Node*)malloc(sizeof(Node));
    memset(new_node, 0, sizeof(Node));
    new_node->data = data;
    node->next = new_node;
    return TRUE;
}

//从哈希表中删除数据
STATUS hash_table_delete(HashTable *ht, int data)
{
    if(NULL == ht){
        return FALSE;
    }

    int hash = hash_func(data);
    Node* node = ht->bucket[hash];
    if(NULL ==node){
        return FALSE;
    }

    if(node->data == data){
        ht->bucket[hash] = node->next;
        free(node);
        return TRUE;
    }

    while(NULL != node->next){
        Node* delete_node = node->next;
        if(delete_node->data == data){
            node->next = delete_node->next;
            free(delete_node);
            return TRUE;
        }
        node = node->next;
    }
    return FALSE;
}

void main()
{
    //创建哈希表
    HashTable *ht=hash_table_create();

    //插入
    hash_table_insert(ht,1);
    hash_table_insert(ht,4);
    hash_table_insert(ht,11);
    hash_table_insert(ht,21);
    printf("first array : %d \n",ht->bucket[1]->data);
    if(NULL == ht->bucket[2]){
        printf("ht 2 is null\n");
    }

    //查找
    Node* node1=hash_table_find(ht,11);
    Node* node2=hash_table_find(ht,21);
    if(NULL != node1){
        printf("node1 data : %d \n",node1->data);
    }
    if(NULL != node2){
        printf("node2 data : %d \n",node2->data);
    }

    //删除
    hash_table_delete(ht,21);
    Node* node3=hash_table_find(ht,21);
    if(NULL == node3){
        printf("21 is cancel\n");
    }
    else{
        printf("ht 1 : %d \n",node3->data);
    }

    //销毁哈希表
    hash_table_destroy(ht);
}