#ifndef HASHTABLE_H
#define HASHTABLE_H

#include "customer.h"

typedef struct hashtable {
    size_t num_buckets;
    customer **buckets;
} hashtable;

hashtable* new_hashtable(size_t num_buckets);
void free_hashtable(hashtable *table);
void add_customer(hashtable *table, char *email, char *name, int shoesize, char *food);
customer* lookup_customer(hashtable *table, char *email);
int delete_customer(hashtable *table, char *email);
void list_customers(hashtable *table);

#endif

