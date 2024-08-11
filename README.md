# E-Commerce Customer Database

## Description

This project involves designing and implementing a simple database to manage customer information for an e-commerce business that sells both snacks and shoes. The database is implemented using hash tables, allowing efficient storage, retrieval, and management of customer data. The application provides a user interface for interacting with the database, including functionalities to add, delete, lookup, list, and save customer records.

### Features

- **Add Customers**: Input customer data including email address, name, shoe size, and favorite food. The email address is used as a unique identifier, and duplicate entries replace existing data.
- **Lookup Customers**: Retrieve and display information about a customer based on their email address.
- **Delete Customers**: Remove a customer's data from the database using their email address.
- **List Customers**: Display all customers in the database.
- **Save Database**: Write the current state of the database to a file (`customers.tsv`).
- **Quit**: Clean up all allocated memory and exit the program.

### Key Files

- **`businessdb.c`**: Main driver file for the database operations.
- **`customer.h`** and **`customer.c`**: Defines the customer data structure and associated functions.
- **`hash_table.h`** and **`hash_table.c`**: Implements the hash table structure and functions for managing the database.
- **`Makefile`**: Builds the project with appropriate compilation flags.

### Data Structures

- **Hash Tables**: Used to store customer records efficiently. The hash table consists of an array of buckets, each containing a linked list of customers.
- **Linked Lists**: Used within hash table buckets to handle collisions by storing multiple customers with the same hash value.

### Usage

To run the program and manage the customer database:

```bash
$ make
$ ./businessdb