#include "apc.h"

int multiplication(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    Dlist *temp1 = *tail1;    // Start from least significant digit of first number
    int shift = 0;            // Keeps track of position shift for each row (like manual multiplication)

    /* Outer loop: iterate through each digit of first number from right to left */
    while (temp1)
    {
        Dlist *temp2 = *tail2;  // Start second number from last digit each iteration

        /* Temporary list to hold partial product result for current digit multiplication */
        Dlist *headR1 = NULL; 
        Dlist *tailR1 = NULL;
        int carry = 0;          // Carry for multiplication

        /* Inner loop: multiply current digit of num1 with all digits of num2 */
        while (temp2)
        {
            /* Multiply digits + carry */
            int mul = temp1->data * temp2->data + carry;

            /* Store result digit in reversed order (most significant later) */
            dl_insert_first(&headR1, &tailR1, mul % 10);

            /* Update carry */
            carry = mul / 10;

            temp2 = temp2->prev;  // Move to next digit (left side)
        }

        /* If any carry remains after loop, insert it */
        if (carry)
            dl_insert_first(&headR1, &tailR1, carry);

        /* Append zeros at the end based on multiplication place value (like shifting in decimal) */
        for (int i = 0; i < shift; i++)
            dl_insert_last(&headR1, &tailR1, 0);

        /* If result list is empty, copy this partial product directly */
        if (*headR == NULL)
        {
            *headR = headR1;
            *tailR = tailR1;
        }
        else
        {
            /* Else add this partial result to total result */
            
            Dlist *headR2 = NULL;  
            Dlist *tailR2 = NULL;

            /* Perform addition: total_result = total_result + partial_result */
            addition(&headR1, &tailR1, headR, tailR, &headR2, &tailR2);

            /* Update final result with new sum */
            *headR = headR2;
            *tailR = tailR2;
        }

        /* Increase shift for next row (equivalent to multiplying by 10) */
        shift++;

        /* Move to the next digit of first number */
        temp1 = temp1->prev;
    }

    return 0;  // Returns success (could return SUCCESS macro if desired)
}
