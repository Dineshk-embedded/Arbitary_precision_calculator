/*******************************************************************************************************************************************************************
*Title			: Multiplication
*Description		: This function performs multiplication of two given large numbers and store the result in the resultant list.
*Prototype		: int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	*headR = NULL;
	*tailR = NULL;
 
	Dlist *temp2 = *tail2;
	int shift = 0;

	while(temp2 != NULL)
	{
		Dlist *headP = NULL, *tailP = NULL;
		int carry = 0;

		for(int i = 0; i < shift; i++)
		{
			if(insert_first(&headP, &tailP, 0) == FAILURE)
			return FAILURE;
		}

		Dlist *temp1 = *tail1;
		while(temp1 != NULL)
		{
			int data = temp1->data * temp2->data + carry;
			insert_first(&headP, &tailP, data % 10);
			carry = data / 10;
 
			temp1 = temp1->prev;
		}

		if(carry)
		insert_first(&headP, &tailP, carry);

		if(*headR == NULL)
		{
			/* first partial product is the first result */
			*headR = headP;
			*tailR = tailP;
		}
		else
		{
			/* result = result + partial (addition needs a fresh list to write into) */
			Dlist *headN = NULL, *tailN = NULL;
			addition(tailR, &tailP, &headN, &tailN);
 
			delete_list(headR, tailR);
			delete_list(&headP, &tailP);
 
			*headR = headN;
			*tailR = tailN;
		}

		temp2 = temp2->prev;
		shift++;
	}

	/* 100 x 0 would otherwise be 000 */
	strip_zeros(headR);
	return SUCCESS;
}
