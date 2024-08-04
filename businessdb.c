#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"
#include "hashtable.h"

#define NUM_BUCKETS 100

void load_database(hashtable *table, const char *filename);
void save_database(hashtable *table, const char *filename);
void prompt_user(hashtable *db);
void print_help();

int main() {
    hashtable *db = new_hashtable(NUM_BUCKETS);
    load_database(db, "customers.tsv");

    printf("Welcome to the Customer Database Program!\n");
    printf("Available commands: add, lookup, delete, list, save, quit, help\n");

    prompt_user(db);

    save_database(db, "customers.tsv");
    free_hashtable(db);

    return 0;
}

void load_database(hashtable *table, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char line[256];
    while (fgets(line, sizeof(line), file)) {
        char *email = strtok(line, "\t");
        char *name = strtok(NULL, "\t");
        char *shoesize_str = strtok(NULL, "\t");
        char *food = strtok(NULL, "\n");

        if (email && name && shoesize_str && food) {
            int shoesize = atoi(shoesize_str);
            add_customer(table, email, name, shoesize, food);
        }
    }

    fclose(file);
}

void save_database(hashtable *table, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    for (size_t i = 0; i < table->num_buckets; i++) {
        customer *c = table->buckets[i];
        while (c) {
            fprintf(file, "%s\t%s\t%d\t%s\n", c->email, c->name, c->shoesize, c->food);
            c = c->next;
        }
    }

    fclose(file);
}

void prompt_user(hashtable *db) {
    char command[10];
    while (1) {
        printf("command: ");
        scanf("%9s", command);
        if (strcmp(command, "quit") == 0) {
            break;
        } else if (strcmp(command, "save") == 0) {
            save_database(db, "customers.tsv");
        } else if (strcmp(command, "add") == 0) {
            char email[100], name[100], food[100];
            int shoesize;
            printf("email address? ");
            scanf("%99s", email);
            printf("name? ");
            scanf("%99s", name);
            printf("shoe size? ");
            scanf("%d", &shoesize);
            printf("favorite food? ");
            scanf("%99s", food);
            add_customer(db, email, name, shoesize, food);
            printf("Customer added successfully.\n");
        } else if (strcmp(command, "lookup") == 0) {
            char email[100];
            printf("email address? ");
            scanf("%99s", email);
            customer *c = lookup_customer(db, email);
            if (c) {
                print_customer(c);
            } else {
                printf("user not found!\n");
            }
        } else if (strcmp(command, "delete") == 0) {
            char email[100];
            printf("email address? ");
            scanf("%99s", email);
            if (delete_customer(db, email)) {
                printf("user deleted!\n");
            } else {
                printf("user not found!\n");
            }
        } else if (strcmp(command, "list") == 0) {
            list_customers(db);
        } else if (strcmp(command, "help") == 0) {
            print_help();
        } else {
            printf("unknown command\n");
        }
    }
}

void print_help() {
    printf("Available commands:\n");
    printf("  add    - Add a new customer\n");
    printf("  lookup - Lookup a customer by email\n");
    printf("  delete - Delete a customer by email\n");
    printf("  list   - List all customers\n");
    printf("  save   - Save the database to a file\n");
    printf("  quit   - Exit the program\n");
    printf("  help   - Show this help message\n");
}

