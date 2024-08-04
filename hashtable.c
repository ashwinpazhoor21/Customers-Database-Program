#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while (*str != '\0') {
        c = *str;
        hash = ((hash << 5) + hash) + (unsigned char)c; /* hash * 33 + c */
        str++;
    }
    return hash;
}

hashtable* new_hashtable(size_t num_buckets) {
    hashtable *table = calloc(1, sizeof(hashtable));
    table->num_buckets = num_buckets;
    table->buckets = calloc(num_buckets, sizeof(customer *));
    return table;
}

void free_hashtable(hashtable *table) {
    for (size_t i = 0; i < table->num_buckets; i++) {
        customer *c = table->buckets[i];
        while (c) {
            customer *next = c->next;
            free_customer(c);
            c = next;
        }
    }
    free(table->buckets);
    free(table);
}

void add_customer(hashtable *table, char *email, char *name, int shoesize, char *food) {
    unsigned long bucket_num = hash(email) % table->num_buckets;
    customer *c = create_customer(email, name, shoesize, food);
    c->next = table->buckets[bucket_num];
    table->buckets[bucket_num] = c;
}

customer* lookup_customer(hashtable *table, char *email) {
    unsigned long bucket_num = hash(email) % table->num_buckets;
    customer *c = table->buckets[bucket_num];
    while (c) {
        if (strcmp(c->email, email) == 0) {
            return c;
        }
        c = c->next;
    }
    return NULL;
}

int delete_customer(hashtable *table, char *email) {
    unsigned long bucket_num = hash(email) % table->num_buckets;
    customer *c = table->buckets[bucket_num];
    customer *prev = NULL;
    while (c) {
        if (strcmp(c->email, email) == 0) {
            if (prev) {
                prev->next = c->next;
            } else {
                table->buckets[bucket_num] = c->next;
            }
            free_customer(c);
            return 1;
        }
        prev = c;
        c = c->next;
    }
    return 0;
}

void list_customers(hashtable *table) {
    printf("%-20s %-20s %-5s %-20s\n", "Email", "Name", "Size", "Favorite Food");
    for (size_t i = 0; i < table->num_buckets; i++) {
        customer *c = table->buckets[i];
        while (c) {
            print_customer(c);
            c = c->next;
        }
    }
}

