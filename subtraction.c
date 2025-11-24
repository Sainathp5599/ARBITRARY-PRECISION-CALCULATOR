#include "apc.h"

/*****************************************************************************************
 * Function : subtraction
 * Purpose  : To subtract two large numbers represented as doubly linked lists.
 * Input    : head1, tail1 -> First number
 *            head2, tail2 -> Second number
 * Output   : Result stored in headR (Result = number1 - number2)
 * Return   : SUCCESS or FAILURE
 *****************************************************************************************/
int subtraction(Dlist **head1, Dlist **tail1, Dlist **head2, Dlist **tail2, Dlist **headR, Dlist **tailR)
{
    int borrow = 0, diff;
    
    /* Start subtraction from the last nodes (least significant digits) */
    Dlist *temp1 = *tail1;
    Dlist *temp2 = *tail2;

    /* Continue until both lists have been fully traversed */
    while (temp1 != NULL || temp2 != NULL)
    {
        int val1 = 0, val2 = 0;

        /* Extract digit from first number if available */
        if (temp1 != NULL)
        {
            val1 = temp1->data;
            temp1 = temp1->prev;  // Move to next higher digit
        }

        /* Extract digit from second number if available */
        if (temp2 != NULL)
        {
            val2 = temp2->data;
            temp2 = temp2->prev;
        }

        /* Subtract previous borrow from current digit */
        val1 = val1 - borrow;

        /* If borrowing needed (digit becomes negative) */
        if (val1 < val2)
        {
            val1 = val1 + 10;     // Borrow from next digit
            borrow = 1;           // Set borrow flag
        }
        else
        {
            borrow = 0;           // No borrow needed
        }

        /* Compute final difference for current digit */
        diff = val1 - val2;

        /* Insert result digit to front (maintains correct order) */
        dl_insert_first(headR, tailR, diff);
    }

    /* Remove leading zeros from result (e.g., "000123" → "123") */
    Dlist *temp = *headR;
    
    while (temp != NULL && temp->data == 0 && temp->next != NULL)
    {
        Dlist *to_delete = temp;   // Node holding an unnecessary leading zero
        temp = temp->next;         // Move forward
        temp->prev = NULL;         // Update new head's previous link
        free(to_delete);           // Free memory of removed node
        *headR = temp;             // Update actual head pointer
    }

    return SUCCESS;
}
