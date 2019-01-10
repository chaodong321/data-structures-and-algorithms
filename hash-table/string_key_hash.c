
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define HASH_TABLE_MAX_SIZE 10000

typedef struct _Node
{
    char* key;
    int value;
    struct _Node* next;
}HashNode;

HashNode* hash_table[HASH_TABLE_MAX_SIZE];
int hash_table_size;

void hash_table_init()
{
    hash_table_size = 0;
    memset(hash_table, 0, sizeof(HashNode*) * HASH_TABLE_MAX_SIZE);
}

// BKDR Hash Function
unsigned int BKDRHash(const char *str)
{
    unsigned int seed = 131; // 31 131 1313 13131 131313 etc..
    unsigned int hash = 0;
 
    while (*str){
        hash = hash * seed + (*str++);
    }
 
    return (hash & 0x7FFFFFFF);
}

void hash_table_insert(const char* skey, int nvalue)
{
    if(hash_table_size >= HASH_TABLE_MAX_SIZE){
        printf("out of hash table memory!\n");
        return;
    }

    unsigned int pos = BKDRHash(skey) % HASH_TABLE_MAX_SIZE;

    HashNode* head =  hash_table[pos];
    while(head){
        if(strcmp(head->key, skey) == 0)
        {
            printf("%s already exists!\n", skey);
            return ;
        }
        head = head->next;
    }

    HashNode* new_temp = (HashNode*)malloc(sizeof(HashNode));
    memset(new_temp, 0, sizeof(HashNode));
    new_temp->key = (char*)malloc(sizeof(char) * (strlen(skey) + 1));
    strcpy(new_temp->key, skey);
    new_temp->value = nvalue;

    new_temp->next = hash_table[pos];
    hash_table[pos] = new_temp;

    hash_table_size++;
}

void hash_table_remove(const char* skey){
    unsigned int pos = BKDRHash(skey) % HASH_TABLE_MAX_SIZE;
    if(hash_table[pos]){
        HashNode* head = hash_table[pos];
        HashNode* last = NULL;
        HashNode* remove = NULL;
        while(head){
            if(strcmp(skey, head->key) == 0)
            {
                remove = head;
                break;
            }
            last = head;
            head = head->next;
        }

        if(remove){
            if(last){
                last->next = remove->next;
            }
            else{
                hash_table[pos] = NULL;
            }

            free(remove->key);
            free(remove);
        }
    }
}

HashNode* hash_table_lookup(const char* skey){
    unsigned int pos = BKDRHash(skey) % HASH_TABLE_MAX_SIZE;
    if(hash_table[pos]){
        HashNode* head = hash_table[pos];
        while(head){
            if(strcmp(skey, head->key) == 0){
                return head;
            }
            head = head->next;
        }
    }
    return NULL;
}

void hash_table_print(){
    printf("\n----------------hash table print start----------------\n");
	printf("index------------------value\n");
    int i;
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i){
        if(hash_table[i]){
			printf("%d----------------", i);
            HashNode* head = hash_table[i];
            while(head){
                printf("%s:%d\t", head->key, head->value);
                head = head->next;
            }
            printf("\n");
        }
    }
	printf("------------------hash table print end----------------\n\n");
}

void hash_table_release(){
    int i;
    for(i = 0; i < HASH_TABLE_MAX_SIZE; ++i){
        if(hash_table[i]){
            HashNode* head = hash_table[i];
            while(head){
                HashNode* temp = head;
                head = head->next;
                if(temp){
                    free(temp->key);
                    free(temp);
                }
            }
        }
    }
}


//测试函数
#define MAX_STR_LEN 20
#define MIN_STR_LEN 10
void rand_str(char r[]){
    int len = MIN_STR_LEN + rand() % (MAX_STR_LEN - MIN_STR_LEN);
    int i;
    for(i = 0; i < len - 1; ++i){
        r[i] = 'a' + rand() % ( 'z' - 'a');
    }
    r[len - 1] = '\0';
}

int main(int argc, char** argv)
{
    srand(time(NULL));
    hash_table_init();
    const char *key1 = "aaaaaaaaa";
    const char *key2 = "bbbbbbbbb";
    const char *key3 = "ccccccccc";

    hash_table_insert(key1, 110);
    hash_table_insert(key2, 220);
    hash_table_insert(key3, 330);
    char str[MAX_STR_LEN + 1];
	int n = 10;
    while(n--){
        rand_str(str);
        hash_table_insert(str, n);
    }
    hash_table_print();

	printf("\n--------------lookup test start------------\n");
    HashNode* node = hash_table_lookup(key1);
    printf("lookup %s:%d\n", key1, node->value);
    node = hash_table_lookup(key2);
    printf("lookup key2:%d\n", key2, node->value);
	printf("--------------lookup test end----------------\n\n");

    printf("\n--------------remove test start--------------\n");
    printf("before remove %s:\n", key3);
    hash_table_remove(key3);
    printf("--------------remove test end----------------\n");

	hash_table_print();
    hash_table_release();
    return 0;
}