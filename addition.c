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

int addition(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int carry = 0;      // Stores carry generated after each digit addition
    int sum;            // Stores the result of digit-by-digit addition
    
    /* Pointers to traverse both lists from right to left (LSB to MSB) */
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    /* Loop until both numbers are fully processed */
    while (temp1 != NULL || temp2 != NULL)
    {
        /* Case 1: Both lists have digits at current position */
        if (temp1 != NULL && temp2 != NULL)
        {
            sum = temp1->data + temp2->data + carry;   // Add digits + carry
            temp1 = temp1->prev;                       // Move to previous digit
            temp2 = temp2->prev;
        }
        /* Case 2: First number finished → only second number remaining */
        else if (temp1 == NULL && temp2 != NULL)
        {
            sum = 0 + temp2->data + carry;             // Add only second digit
            temp2 = temp2->prev;
        }
        /* Case 3: Second number finished → only first number remaining */
        else
        {
            sum = temp1->data + 0 + carry;             // Add only first digit
            temp1 = temp1->prev;
        }

        /* If result is ≥ 10, extract unit digit & set carry */
        if (sum > 9)
        {
            dl_insert_first(headR, tailR, sum % 10);   // Store unit digit
            carry = 1;                                 // Set carry for next step
        }
        else
        {
            dl_insert_first(headR, tailR, sum);        // Store direct sum
            carry = 0;                                 // No carry generated
        }
    }

	if (carry)
    dl_insert_first(headR, tailR, carry);

    return SUCCESS;  // Added logically expected return statement (optional based on your implementation)
}
