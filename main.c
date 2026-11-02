/**************************************************************************************************************************************************************
*Title		: main function(Driver function)
*Description	: This function is used as the driver function for the all the functions
***************************************************************************************************************************************************************/
#include "apc.h"

/* print a number with its sign (zero never gets a '-') */
static void print_signed(Dlist *head, int sign)
{
	if (sign < 0)
		printf("-");
	print_list(head);
}

/* strips an optional leading +/- from the operand, returns +1 or -1 */
static int get_sign(char **str)
{
	int sign = 1;

	if ((*str)[0] == '+')
		(*str)++;
	else if ((*str)[0] == '-')
	{
		sign = -1;
		(*str)++;
	}
	return sign;
}

/* resultR = (operand 1 with sign s1) + (operand 2 with sign s2), sign of result in *sR */
static void signed_add(Dlist **head1, Dlist **tail1, int s1, Dlist **head2, Dlist **tail2, int s2,
		       Dlist **headR, Dlist **tailR, int *sR)
{
	*headR = NULL;
	*tailR = NULL;

	if (s1 == s2)
	{
		/* same sign: add the magnitudes, keep the sign */
		addition(tail1, tail2, headR, tailR);
		*sR = s1;
	}
	else if (compare_list(head1, head2))
	{
		/* different sign, |op1| >= |op2|: |op1| - |op2|, sign of op1 */
		subtraction(tail1, tail2, headR, tailR);
		*sR = s1;
	}
	else
	{
		/* different sign, |op1| < |op2|: |op2| - |op1|, sign of op2 */
		subtraction(tail2, tail1, headR, tailR);
		*sR = s2;
	}

	if (check_z(*headR) == SUCCESS)
		*sR = 1;
}

int main(int argc, char* argv[])
{
	Dlist *head1, *tail1, *head2, *tail2, *headR, *tailR;
	char option = 'n', operator;
	char *num1, *num2;
	int sign1, sign2, signR;
	do
	{
		if (argc != 4)
		{
			printf("Usage: ./program operand1 operator operand2\n");
			return FAILURE;
		}

		operator = argv[2][0];

		/* separate the optional sign from the digits */
		num1 = argv[1];
		num2 = argv[3];
		sign1 = get_sign(&num1);
		sign2 = get_sign(&num2);

		if(create_list(&head1,&tail1,&num1) == SUCCESS)
		{
			if (check_z(head1) == SUCCESS)
				sign1 = 1;                 /* -0 is just 0 */
			printf("Operand 1 = ");
			print_signed(head1, sign1);
		}
		else 
		return 0;

		if(create_list(&head2,&tail2,&num2) == SUCCESS)
		{
			if (check_z(head2) == SUCCESS)
				sign2 = 1;
			printf("Operand 2 = ");
		 	print_signed(head2, sign2);
		}
		else
		{
			free_list(&head1, &tail1);
			return 0;
		}

		headR = NULL;
		tailR = NULL;
		signR = 1;

		switch (find_operator(operator))
		{
			case 1:
				/* call the function to perform the addition operation */
				printf("\n      Addition\n");
				signed_add(&head1,&tail1,sign1,&head2,&tail2,sign2,&headR,&tailR,&signR);

				printf("Result = ");
				print_signed(headR, signR);
				break;
			case 2:	
				/* subtraction: op1 - op2 is op1 + (-op2) */
				printf("\n      Subtraction\n");
				signed_add(&head1,&tail1,sign1,&head2,&tail2,-sign2,&headR,&tailR,&signR);

				printf("Result = ");
				print_signed(headR, signR);
				break;
			case 3:	
				/* call the function to perform the multiplication operation */
				printf("\n      Multiplication\n");
				multiplication(&head1,&tail1,&head2,&tail2,&headR,&tailR);
				signR = sign1 * sign2;
				if (check_z(headR) == SUCCESS)
					signR = 1;

				printf("Result = ");
				print_signed(headR, signR);
				break;
			case 4:	
				/* call the function to perform the division operation */
				printf("\n      Division\n");
				if (division(&head1,&tail1,&head2,&tail2,&headR,&tailR) == SUCCESS)
				{
					signR = sign1 * sign2;
					if (check_z(headR) == SUCCESS)
						signR = 1;

					printf("Result = ");
					print_signed(headR, signR);
				}
				break;
			default:
				printf("Invalid Input:-( Try again...\n");
		}

		free_list(&head1, &tail1);
		free_list(&head2, &tail2);
		free_list(&headR, &tailR);

		printf("Want to continue? Press [yY | nN]: ");
		if (scanf(" %c", &option) != 1)    /* EOF / no input -> stop */
			break;
	}while (option == 'y' || option == 'Y');

	return 0;
}
