#include<stdio.h>
#include "apc.h"

int division(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    /* Check divide-by-zero (if divisor = 0) */
    if (*head2 == *tail2 && (*head2)->data == 0)
    {
        return FAILURE;
    }

    /* If dividend < divisor, result = 0 */
    if (comparelist(*head1, *head2) == FAILURE)
    {
        dl_insert_last(headR, tailR, 0);
        return SUCCESS;
    }

    /* remH, remT → Stores remainder while processing digits one by one */
    Dlist *remH = NULL;
    Dlist *remT = NULL;

    /* temp traverses dividend from MSB to LSB */
    Dlist *temp = *head1;

    /* Iterate through each digit of dividend like long division */
    while (temp)
    {
        /* Bring next digit down → append to remainder list */
        dl_insert_last(&remH, &remT, temp->data);

        /* Remove leading zeros from remainder */
        remove_leading_zero(&remH, &remT);

        int qdigit = 0;   // Stores the quotient digit for current place

        /* Subtract divisor from remainder repeatedly until remainder < divisor */
        while (comparelist(remH, *head2) != FAILURE)
        {
            /* Temporary result after subtraction */
            Dlist *resH = NULL;
            Dlist *resT = NULL;

            /* remH = remH - divisor */
            subtraction(&remH, &remT, head2, tail2, &resH, &resT);

            /* Cleanup leading zeros after subtraction */
            remove_leading_zero(&resH, &resT);

            /* Free old remainder to replace with new one */
            free_list(&remH, &remT);

            /* Update remainder */
            remH = resH;
            remT = resT;

            qdigit++;  // Count number of successful subtractions → quotient digit
        }

        /* Append quotient digit to result list */
        dl_insert_last(headR, tailR, qdigit);

        /* Move to next digit in original number */
        temp = temp->next;
    }

    /* Remove leading zeros from final quotient */
    remove_leading_zero(headR, tailR);

    return SUCCESS;
}
