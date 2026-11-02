/*******************************************************************************************************************************************************************
*Title			: Subtraction
*Description		: This function performs subtraction of two given large numbers and store the result in the resultant list.
*Prototype		: int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int subtraction(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	/* caller must make sure operand 1 >= operand 2 (use compare_list) */
	int result = 0, borrow = 0, d1, d2;
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;

	while(temp1 != NULL)
	{
		/* work on local copies so operand 1 is NOT modified */
		d1 = temp1->data - borrow;
		d2 = (temp2 != NULL) ? temp2->data : 0;

		if(d1 < d2)
		{
			d1 += 10;
			borrow = 1;
		}
		else
		borrow = 0;

		result = d1 - d2;
		insert_first(headR,tailR,result);

		temp1 = temp1->prev;
		if(temp2 != NULL)
		temp2 = temp2->prev;
	}

	/* 100 - 99 would otherwise come out as 001 */
	strip_zeros(headR);
	return SUCCESS;
}
