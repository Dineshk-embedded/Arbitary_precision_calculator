#ifndef APC_H
#define APC_H
#define SUCCESS 0
#define FAILURE -1
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef int data_t;
typedef struct node
{
	struct node *prev;
	data_t data;
	struct node *next;
}Dlist;

/* Include the prototypes here */
int find_operator(char oper);
int create_list(Dlist **head, Dlist **tail, char ** a);
int print_list(Dlist *head);
int insert_first(Dlist **head, Dlist **tail, int data);
int insert_last(Dlist **head, Dlist **tail, int data);
void strip_zeros(Dlist **head);
int check_result(int result, int *carry);
int compare_list(Dlist **head1, Dlist **head2);
int delete_list(Dlist **head, Dlist **tail);
void free_list(Dlist **head, Dlist **tail);
int check_z(Dlist *head);
int addition(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
int subtraction(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR);
int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR);
#endif
