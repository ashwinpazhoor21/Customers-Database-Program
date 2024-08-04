#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "customer.h"

customer* create_customer(char *email, char *name, int shoesize, char *food) {
    customer *c = malloc(sizeof(customer));
    c->email = strdup(email);
    c->name = strdup(name);
    c->shoesize = shoesize;
    c->food = strdup(food);
    c->next = NULL;
    return c;
}

void free_customer(customer *c) {
    free(c->email);
    free(c->name);
    free(c->food);
    free(c);
}

void print_customer(customer *c) {
    printf("%-20s %-20s %-5d %-20s\n", c->email, c->name, c->shoesize, c->food);
}

