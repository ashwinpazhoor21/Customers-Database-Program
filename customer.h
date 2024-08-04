#ifndef CUSTOMER_H
#define CUSTOMER_H

typedef struct customer {
    char *email;
    char *name;
    int shoesize;
    char *food;
    struct customer *next;
} customer;

customer* create_customer(char *email, char *name, int shoesize, char *food);
void free_customer(customer *c);
void print_customer(customer *c);

#endif

