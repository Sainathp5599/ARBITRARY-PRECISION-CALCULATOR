#include<stdio.h>      // Standard I/O functions
#include<string.h>     // String handling functions
#include<stdlib.h>     // Memory allocation, exit(), atoi(), etc.

#ifndef APC_H       // Header guard start
#define APC_H

/* Common return status macros */
#define SUCCESS 1
#define FAILURE 0

/* Data type used to store number digits */
typedef int data_t;

/* 
 * Doubly linked list node structure to store digits of a large number
 * prev -> Pointer to previous node
 * data -> Digit stored (0-9)
 * next -> Pointer to next node
 */
typedef struct node
{
    struct node *prev;
    data_t data;
    struct node *next;
} Dlist;


/* Validates command-line arguments */
int validation(int argc, char *argv[]);

/* Reads number string and stores digits in doubly linked list */
int reading_data(char *str, Dlist **head1, Dlist **tail);

/* Inserts node at beginning of the list */
int dl_insert_first(Dlist **head, Dlist **tail, int data);

/* Adds two large numbers stored in linked lists */
int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/* Compares signs of numbers based on input arguments */
int compare(char *argv[]);

/* Subtracts large numbers stored in linked lists */
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/* Prints operands and result with chosen operator */
void display_operation(Dlist *head1, Dlist *head2, Dlist *headR,char operator, int sign1, int sign2, int result_sign);

/* Multiplies large numbers stored in linked lists */
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/* Inserts node at the end of the list */
int dl_insert_last(Dlist **head, Dlist **tail, int data);

/* Performs division on large numbers */
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);

/* Compares two number lists; returns relation status */
int comparelist(Dlist *head1, Dlist *head2);

/* Removes extra zeros at the head of result number */
void remove_leading_zero(Dlist **head, Dlist **tail);

/* Frees allocated linked list memory */
void free_list(Dlist **head, Dlist **tail);

/* Returns length of the linked list (number of digits) */
int length(Dlist *head);

#endif  // End header guard
