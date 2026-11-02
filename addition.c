/*******************************************************************************************************************************************************************
*Title			: Addition
*Description		: This function performs addition of two given large numbers and store the result in the resultant list.
*Prototype		: int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR);
*Input Parameters	: head1: Pointer to the first node of the first double linked list.
			: tail1: Pointer to the last node of the first double linked list.
			: head2: Pointer to the first node of the second double linked list.
			: tail2: Pointer to the last node of the second double linked list.
			: headR: Pointer to the first node of the resultant double linked list.
*Output			: Status (SUCCESS / FAILURE)
*******************************************************************************************************************************************************************/
#include "apc.h"

int addition(Dlist **tail1, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
	int result = 0, carry = 0;
	Dlist *temp1 = *tail1;
	Dlist *temp2 = *tail2;
	while(temp1 != NULL || temp2 != NULL)
	{
		if(temp1 != NULL && temp2 != NULL)
		{
			result = temp1->data + temp2->data + carry;
			result = check_result(result,&carry);

			temp1 = temp1->prev;
			temp2 = temp2->prev;
			insert_first(headR,tailR,result);
		}
		else if(temp1 != NULL && temp2 == NULL)
		{
			result = temp1->data + carry;
			result = check_result(result,&carry);

			temp1 = temp1->prev;
			insert_first(headR,tailR,result);
		}
		else if(temp1 == NULL && temp2 != NULL)
		{
			result = temp2->data + carry;
			result = check_result(result,&carry);

			temp2 = temp2->prev;
			insert_first(headR,tailR,result);
		}
	}

	if(carry == 1)
    insert_first(headR,tailR,1);

	return SUCCESS;
}
