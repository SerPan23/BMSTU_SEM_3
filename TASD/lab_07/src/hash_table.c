#include "hash_table.h"

int data_init(data_t **data, char value)
{
    (*data) = malloc(sizeof(data_t));
    if (!(*data))
        return ERROR_MEMMORY_ALLOC;
    (*data)->value = value;
    (*data)->count = 1;
    (*data)->next = NULL;
    return EXIT_SUCCESS;
}

void data_free(data_t **data)
{
    free((*data));
    (*data) = NULL;
}

int data_hash(char data, int size)
{
    // printf("%d %% %d = %d\n", (int)data, size, (int)data % size);
    return (int)data % size;
}

int data_cmp(char a, char b)
{
    return a - b;
}


int hash_table_init(hash_table_t *hash_table, int type)
{
    hash_table->type = type;
    hash_table->size = 0;
    hash_table->collision_count = 0;
    hash_table->hash_key = DEFAULT_HASH_KEY;
    hash_table->max_ind = -1;
    for (size_t i = 0; i < MAX_ELEMENT_COUNT; i++)
        hash_table->data[i] = NULL;
    return EXIT_SUCCESS;
}

int hash_table_destroy(hash_table_t *hash_table)
{
    for (size_t i = 0; i < MAX_ELEMENT_COUNT; i++)
        if (hash_table->data[i] != NULL)
            data_free(&hash_table->data[i]);
    hash_table->size = 0;
    return EXIT_SUCCESS;
}

int hash_table_opened_add(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value)
{
    int pos = hash_func(value, hash_table->hash_key);
    if (pos < 0 || pos > MAX_ELEMENT_COUNT - 1)
        return ERROR_INVALID_POSITION;

    if (hash_table->data[pos] != NULL)
    {
        data_t *last = hash_table->data[pos];
        int flag = 0;
        for (data_t *cur = hash_table->data[pos]; cur != NULL; cur = cur->next)
        {
            if (data_cmp(cur->value, value) == 0)
            {
                cur->count++;
                flag = 1;
                break;
            }
            if (cur->next != NULL)
                last = last->next;
        }
        if (!flag)
        {
            data_t *tmp = NULL;
            int rc = data_init(&tmp, value);
            if (rc != EXIT_SUCCESS)
                return rc;
            last->next = tmp;
            hash_table->size++;
            hash_table->collision_count++;
        }
    }
    else
    {
        data_t *tmp = NULL;
        int rc = data_init(&tmp, value);
        if (rc != EXIT_SUCCESS)
            return rc;
        hash_table->data[pos] = tmp;
        hash_table->size++;
    }

    hash_table->max_ind = hash_table->max_ind < pos ? pos : hash_table->max_ind;

    return EXIT_SUCCESS;
}

int hash_table_closed_add(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value)
{
    int pos = hash_func(value, hash_table->hash_key);
    if (pos < 0 || pos > MAX_ELEMENT_COUNT - 1)
        return ERROR_INVALID_POSITION;

    if (hash_table->data[pos] != NULL)
    {
        for (; pos < MAX_ELEMENT_COUNT; pos++)
        {
            if (hash_table->data[pos] == NULL)
            {
                data_t *tmp = NULL;
                int rc = data_init(&tmp, value);
                if (rc != EXIT_SUCCESS)
                    return rc;
                hash_table->data[pos] = tmp;
                hash_table->size++;
                hash_table->collision_count++;
                break;
            }
            else if (data_cmp(hash_table->data[pos]->value, value) == 0)
            {
                hash_table->data[pos]->count++;
                break;
            }
        }
    }
    else
    {
        data_t *tmp = NULL;
        int rc = data_init(&tmp, value);
        if (rc != EXIT_SUCCESS)
            return rc;
        hash_table->data[pos] = tmp;
        hash_table->size++;
    }

    hash_table->max_ind = hash_table->max_ind < pos ? pos : hash_table->max_ind;

    return EXIT_SUCCESS;
}

int hash_table_add(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value)
{
    int rc;
    if (hash_table->type == OPENED)
        rc = hash_table_opened_add(hash_table, hash_func, value);
    else
        rc = hash_table_closed_add(hash_table, hash_func, value);

    return rc;
}

data_t *hash_table_opened_search(hash_table_t *hash_table, int (*hash_func)(char data, int size), char data, int *cmp_cout)
{
    int pos = hash_func(data, hash_table->hash_key);

    if (hash_table->data[pos] != NULL)
        for (data_t *cur = hash_table->data[pos]; cur != NULL; cur = cur->next)
        {
            if (cmp_cout)
                ++(*cmp_cout);
            if (data_cmp(cur->value, data) == 0)
                return cur;
        }

    return NULL;
}

data_t *hash_table_closed_search(hash_table_t *hash_table, int (*hash_func)(char data, int size), char data, int *pos, int *cmp_cout)
{
    int p = hash_func(data, hash_table->hash_key);
    if (p < 0 || p > MAX_ELEMENT_COUNT - 1)
    {
        if (pos)
            *pos = -1;
        return NULL;
    }

    for (int i = p; i < MAX_ELEMENT_COUNT; i++)
    {
        if (data_cmp(hash_table->data[i]->value, data) == 0)
        {
            if (cmp_cout)
                ++(*cmp_cout);
            if (pos != NULL)
                *pos = i;
            return hash_table->data[i];
        }
    }

    return NULL;
}

data_t *hash_table_search(hash_table_t *hash_table, int (*hash_func)(char data, int size), char data, int *cmp_cout)
{
    data_t *rc = NULL;
    if (hash_table->type == OPENED)
        rc = hash_table_opened_search(hash_table, hash_func, data, cmp_cout);
    else
        rc = hash_table_closed_search(hash_table, hash_func, data, NULL, cmp_cout);

    return rc;
}

int hash_table_opened_remove(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value, data_t **data)
{
    data_t *tmp = hash_table_opened_search(hash_table, hash_func, value, NULL);
    if (tmp == NULL)
        return ERROR_INVALID_VALUE;

    data_t *prev = NULL;
    for (data_t *cur = tmp; cur != NULL; cur = cur->next)
    {
        if (data_cmp(cur->value, value) == 0)
        {
            *data = cur;
            hash_table->size--;
            if (prev)
            {
                if (cur->next)
                    prev->next = cur->next;
                else
                    prev->next = NULL;
            }
            break;
        }
        prev = cur;
    }

    return EXIT_SUCCESS;
}

int hash_table_closed_remove(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value, data_t **data)
{
    int pos = 0;
    data_t *tmp = hash_table_closed_search(hash_table, hash_func, value, &pos, NULL);
    if (tmp == NULL)
        return ERROR_INVALID_VALUE;

    *data = tmp;

    hash_table->data[pos] = NULL;
    hash_table->size--;

    return EXIT_SUCCESS;
}

int hash_table_remove(hash_table_t *hash_table, int (*hash_func)(char data, int size), char value, data_t **data)
{
    int rc;
    if (hash_table->type == OPENED)
        rc = hash_table_opened_remove(hash_table, hash_func, value, data);
    else
        rc = hash_table_closed_remove(hash_table, hash_func, value, data);

    return rc;
}

void hash_table_print(hash_table_t *hash_table, void (*print)(data_t *data, size_t ind))
{
    for (int i = 0; i <= hash_table->max_ind; i++)
    {
        if (hash_table->type == OPENED)
        {
            data_t *cur = hash_table->data[i];
            do
            {
                print(cur, i);
                if (cur != NULL)
                    cur = cur->next;
            } while (cur != NULL);

        }
        else
            print(hash_table->data[i], i);
    }
}

void hash_table_restruct_opened(hash_table_t *hash_table, hash_table_t *new_table)
{
    for (int pos = 0; pos < hash_table->max_ind; pos++)
    {
        if (hash_table->data[pos] != NULL)
            for (data_t *cur = hash_table->data[pos]; cur != NULL; cur = cur->next)
            {
                for (size_t i = 0; i < cur->count; i++)
                    hash_table_add(new_table, data_hash, cur->value);
            }
    }
}

void hash_table_restruct_closed(hash_table_t *hash_table, hash_table_t *new_table)
{
    for (int pos = 0; pos < hash_table->max_ind; pos++)
    {
        data_t *tmp = hash_table->data[pos];
        if (tmp != NULL)
            for (size_t i = 0; i < tmp->count; i++)
                hash_table_add(new_table, data_hash, tmp->value);
    }
}

hash_table_t *hash_table_restruct(hash_table_t *hash_table, int new_hash_key)
{
    hash_table_t *new_table = NULL;
    new_table = table_init(hash_table->type);
    if (!new_table)
        return NULL;

    new_table->hash_key = new_hash_key;

    // printf("\nSTART RESTRUCT\n");

    if (new_table->type == OPENED)
        hash_table_restruct_opened(hash_table, new_table);
    else
        hash_table_restruct_closed(hash_table, new_table);

    // printf("\nEND RESTRUCT (NEW HASH KEY: %d)\n", new_table->hash_key);

    return new_table;
}

// for user
hash_table_t *table_init(int type)
{
    hash_table_t *tmp = malloc(sizeof(hash_table_t));
    if (!tmp)
        return NULL;

    hash_table_init(tmp, type);

    return tmp;
}

void table_free(hash_table_t *table)
{
    hash_table_destroy(table);
    free(table);
}

int table_add(hash_table_t **table, char value)
{
    int rc = hash_table_add(*table, data_hash, value);
    if (rc != EXIT_SUCCESS)
        return rc;

    if ((*table)->collision_count >= MAX_COLLISION_COUNT)
        *table = hash_table_restruct(*table, get_next_prime((*table)->hash_key));

    return EXIT_SUCCESS;
}

int table_add_with_debug(hash_table_t **table, char value)
{
    int rc = hash_table_add(*table, data_hash, value);
    if (rc != EXIT_SUCCESS)
        return rc;

    if ((*table)->collision_count >= MAX_COLLISION_COUNT)
    {
        *table = hash_table_restruct(*table, get_next_prime((*table)->hash_key));
        printf("\nTABLE RESTRUCTED (NEW HASH KEY: %d)\n", (*table)->hash_key);
    }

    return EXIT_SUCCESS;
}

int table_create_from_str(hash_table_t **table, char *str)
{
    int rc = EXIT_SUCCESS;
    for (size_t i = 0; i < strlen(str); i++)
    {
        rc = table_add(table, str[i]);
        if (rc != EXIT_SUCCESS)
            return rc;
    }

    return EXIT_SUCCESS;
}

void data_print(data_t *data, size_t ind)
{
    if (!data)
        printf("│ %5zu │ %5c │ %5c │\n", ind, '-', '-');
    else
        printf("│ %5zu │ %5c │ %5zu │\n", ind, data->value, data->count);
}

void table_print(hash_table_t *table)
{
    // printf("\nTABLE HASH MAX IND: %d\n", table->max_ind);
    printf("\nTABLE HASH KEY: %d\n", table->hash_key);
    printf("┌───────┬───────┬───────┐\n");
    printf("│ %5s │ %5s │ %5s │\n", "Index", "Value", "Count");
    printf("├───────┼───────┼───────┤\n");
    hash_table_print(table, data_print);
    printf("└───────┴───────┴───────┘\n");
    printf("Table row filled count: %zu\n", table->size);
    printf("Collision count: %zu\n", table->collision_count);
}

int table_search(hash_table_t *table, char value, int *cmp_count)
{
    hash_table_search(table, data_hash, value, cmp_count);
    return EXIT_SUCCESS;
}
