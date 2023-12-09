#ifndef HASH_TABLE
#define HASH_TABLE

#include "defines.h"
#include "useful_funcs.h"

#define MAX_ELEMENT_COUNT 256
#define DEFAULT_HASH_KEY 17
#define MAX_COLLISION_COUNT 4

#define ERROR_INVALID_VALUE 100
#define ERROR_INVALID_POSITION 101
#define ERROR_POS_USED 102

typedef struct data data_t;

struct data
{
    char value;
    size_t count;
    data_t *next;
};

int data_init(data_t **data, char value);

void data_free(data_t **data);
int data_hash(char data, int size);
void data_print(data_t *data, size_t ind);
int data_cmp(char a,char b);

typedef enum { OPENED, CLOSED } hash_table_type;

typedef struct hash_table
{
    hash_table_type type;
    data_t *data[MAX_ELEMENT_COUNT];
    size_t size;
    int max_ind;
    size_t collision_count;
    int hash_key;
} hash_table_t;

int hash_table_init(hash_table_t *hash_table, int type);
int hash_table_destroy(hash_table_t *hash_table);

int hash_table_add(hash_table_t *hash_table, int (*hash_func)(char data, int size), char data);
int hash_table_remove(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value, data_t **data);
void hash_table_print(hash_table_t *hash_table, void (*print)(data_t *data, size_t ind));
data_t *hash_table_search(hash_table_t *hash_table, int (*hash_func)(char data, int size), char data, int *cmp_cout);

hash_table_t *hash_table_restruct(hash_table_t *hash_table, int new_hash_key);

// for user
hash_table_t *table_init(int type);
void table_free(hash_table_t *table);

int table_add(hash_table_t **table, char value);
int table_add_with_debug(hash_table_t **table, char value);

int table_create_from_str(hash_table_t **table, char *str);
void table_print(hash_table_t *table);
int table_search(hash_table_t *table, char value, int *cmp_count);

#endif
