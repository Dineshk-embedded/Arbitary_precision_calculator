/*******************************************************************************************************************************************************************
*Title			: Division
*Description		: This function performs division of two given large numbers and store the result in the resultant list.
*Prototype		: int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	Dlist *temp;
	int count;

	/* divisor == 0 check */
	if (check_z(*head2) == SUCCESS)
	{
		printf("ERROR : Division by zero\n");
		return FAILURE;
	}

	*headR = *tailR = NULL;
	Dlist *headRem = NULL, *tailRem = NULL;

	/* long division: bring down one digit of operand 1 at a time */
	for (temp = *head1; temp != NULL; temp = temp->next)
	{
		/* remainder = remainder * 10 + next digit */
		insert_last(&headRem, &tailRem, temp->data);
		strip_zeros(&headRem);

		/* how many times does operand 2 fit in the remainder? (at most 9) */
		count = 0;
		while (compare_list(&headRem, head2))
		{
			Dlist *hN = NULL, *tN = NULL;
			subtraction(&tailRem, tail2, &hN, &tN);
			free_list(&headRem, &tailRem);
			headRem = hN;
			tailRem = tN;
			count++;
		}

		insert_last(headR, tailR, count);   /* this quotient digit */
	}

	strip_zeros(headR);

	/* headRem is the remainder here */
	free_list(&headRem, &tailRem);
	return SUCCESS;
}
