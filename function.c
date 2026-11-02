#include "apc.h"
int find_operator(char oper)
{
    switch(oper)
    {
        case '+':
            return 1;
        case '-':
            return 2;
        case 'x':
        case 'X':
            return 3;
        case '/':
            return 4;
        default:
            return FAILURE;
    }
}

int create_list(Dlist **head, Dlist **tail, char ** a)
{
    *head = NULL;
    *tail = NULL;

    int count = 0, res = 0;

    /* operand with no digits (e.g. "" or just a sign) is invalid */
    if(a[0][0] == '\0')
    {
        printf("ERROR : Operand has no digits\n");
        return FAILURE;
    }

    while(a[0][count])
    {

        if(a[0][count] >= '0' && a[0][count] <= '9')
        {
            res = a[0][count] - '0';
            count++;

            Dlist *Nnode = malloc(sizeof(Dlist));
            if(Nnode == NULL)
            {
                free_list(head,tail);
                return FAILURE;
            }

            Nnode->data = res;
            Nnode->prev = NULL;
            Nnode->next = NULL;

            if(*head == NULL) 
            {
                *head = Nnode;
                *tail = Nnode;
            }
            else
            {
                Nnode->prev = *tail;
                (*tail)->next = Nnode;
                *tail = Nnode;
            }
        }
        else
        {
            free_list(head,tail);
            printf("ERROR : Only digits are Allowed\n");
            return FAILURE;
        }
    }

    /* 007 -> 7, so that length based comparison works */
    strip_zeros(head);

    return SUCCESS;
}

int print_list(Dlist *head)
{
	/* Cheking the list is empty or not */
    if(check_z(head) == SUCCESS)
    {
        printf("0\n");
        return SUCCESS;
    }
	if (head == NULL)
	{
		printf("INFO : List is empty\n");
        return FAILURE;
	}
	else
	{
	    while (head)		
	    {
		    /* Printing the list */
		    printf("%d", head -> data);

		    /* Travering in forward direction */
		    head = head -> next;
	    }
        printf("\n");
    }
    return SUCCESS;
}

int insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *nNode = malloc(sizeof(Dlist));
    if(nNode == NULL)
    return FAILURE;

    nNode->data = data;
    nNode->prev = NULL;
    nNode->next = NULL;

    if(*head == NULL)
    {
        *head = nNode;
        *tail = nNode;

        return SUCCESS;
    }

    nNode->next = *head;
    (*head)->prev = nNode;
    *head = nNode;

    return SUCCESS;

}

int check_result(int result, int *carry)
{
    if(result > 9)
    {
        result = result % 10;
        *carry = 1;
    }
    else
    *carry = 0;

    return result;
}

int compare_list(Dlist **head1, Dlist **head2)
{
    int len1 = 0, len2 = 0;
    Dlist *temp1 = *head1;
    Dlist *temp2 = *head2; 
    while(temp1 != NULL)
    {
        len1++;
        temp1 = temp1->next;
    }

    while(temp2 != NULL)
    {
        len2++;
        temp2 = temp2->next;
    }

    // printf(" len1 - %d \t",len1);
    // printf(" len2 - %d \n",len2);
    if(len1 > len2)
    return 1;
    else if(len1 < len2)
    return 0;
    else
    {
        Dlist *temp1 = *head1;
        Dlist *temp2 = *head2;
        while(temp1 != NULL && temp2 != NULL)
        {
            if(temp1->data == temp2->data)
            {
                temp1 = temp1->next;
                temp2 = temp2->next;
            }
            else if(temp1->data > temp2->data)
            return 1;
            else
            return 0;
        }

        return 1;
    }
}

int delete_list(Dlist **head, Dlist **tail)
{
    if(*head == NULL)
    {
        printf("List Empty\n");
        return FAILURE;
    }
    else
    {
        while(*head != NULL)
        {
            Dlist *temp = *head;
            *head = (*head)->next;
            free(temp);
        }

        *tail = NULL;
    }

    return SUCCESS;
}

void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp;

    while (*head != NULL)
    {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    *tail = NULL;
}

int check_z(Dlist *head)
{
    if (head == NULL)
        return FAILURE;
    Dlist *temp = head;
    int count = 0,len = 0;
    while(temp != NULL)
    {
        len++;
        if(temp->data == 0)
        count++;

        temp = temp->next;
    }

    if(len == count)
    return SUCCESS;

    return FAILURE;
}

/* add a node at the end of the list */
int insert_last(Dlist **head, Dlist **tail, int data)
{
    Dlist *nNode = malloc(sizeof(Dlist));
    if(nNode == NULL)
    return FAILURE;

    nNode->data = data;
    nNode->prev = *tail;
    nNode->next = NULL;

    if(*head == NULL)
    *head = nNode;
    else
    (*tail)->next = nNode;

    *tail = nNode;
    return SUCCESS;
}

/* remove leading zeros from a list, always keeps at least one digit */
void strip_zeros(Dlist **head)
{
    while(*head != NULL && (*head)->data == 0 && (*head)->next != NULL)
    {
        Dlist *tmp = *head;
        *head = tmp->next;
        (*head)->prev = NULL;
        free(tmp);
    }
}
