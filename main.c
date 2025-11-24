/**************************************************************************************************************************************************************
 * Title        : main function (Driver function)
 * Description  : This function is used as the driver function for all arithmetic operations on large numbers.
 **************************************************************************************************************************************************************/
#include "apc.h"

int main(int argc, char *argv[])
{
    /* Validate input format (number operator number) */
    int valid = validation(argc, argv);
    if (valid == FAILURE)
    {
        printf("Invalid input!\n");
        return 0;
    }

    /* Extract operator (+, -, x, /) */
    char operator = argv[2][0];

    /* Initialize linked list heads and tails for two numbers and result */
    Dlist *head1 = NULL, *tail1 = NULL;
    Dlist *head2 = NULL, *tail2 = NULL;
    Dlist *headR = NULL, *tailR = NULL;
    char option;

    do
    {
        /* Determine if numbers are negative based on input sign */
        int neg1 = (argv[1][0] == '-');
        int neg2 = (argv[3][0] == '-');

        int sign1 = neg1 ? -1 : 1;
        int sign2 = neg2 ? -1 : 1;
        int result_sign = 1; // will update per operation

        /* Remove sign (+/-) before storing actual digits */
        char *num1 = (neg1 || argv[1][0] == '+') ? argv[1] + 1 : argv[1];
        char *num2 = (neg2 || argv[3][0] == '+') ? argv[3] + 1 : argv[3];

        /* Convert input numbers into doubly linked lists */
        reading_data(num1, &head1, &tail1);
        reading_data(num2, &head2, &tail2);

        /* ========================= OPERATOR HANDLING ========================= */

        /* ----------- Addition Case ------------- */
        if (operator == '+')
        {
            if (neg1 && !neg2)
            {
                if (compare(argv))
                {
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    result_sign = -1; // |-a| >= |b| → result negative
                }
                else
                {
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
                    result_sign = +1; // |b| > |a| → result positive
                }
            }
            else if (!neg1 && neg2)
            {
                if (compare(argv))
                {
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                    result_sign = +1; // |a| >= |b|, a positive
                }
                else
                {
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
                    result_sign = -1; // |b| > |a|, b negative
                }
            }
            else
            {
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                result_sign = (sign1 == sign2) ? sign1 : +1; // both + or both -
            }
        }
        /* ----------- Subtraction Case ------------- */
        else if (operator == '-')
        {
            if (neg1 && !neg2)
            {
                // -a - b = -(a + b)
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                result_sign = -1;
            }
            else if (!neg1 && neg2)
            {
                // a - (-b) = a + b
                addition(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                result_sign = +1;
            }
            else
            {
                // both positive or both negative
                int cmp = compare(argv); // compares |a| and |b|

                if (!neg1 && !neg2)
                {
                    // a - b
                    if (cmp)
                        result_sign = +1; // |a| >= |b|
                    else
                        result_sign = -1; // |b| > |a|
                }
                else
                {
                    // -a - -b = -(a - b) = b - a
                    if (cmp)
                        result_sign = -1; // |a| >= |b| → result negative
                    else
                        result_sign = +1; // |b| > |a| → result positive
                }

                if (cmp)
                    subtraction(&head1, &tail1, &head2, &tail2, &headR, &tailR);
                else
                    subtraction(&head2, &tail2, &head1, &tail1, &headR, &tailR);
            }
        }

        /* ----------- Multiplication Case ------------- */
        else if (operator == 'x')
        {
            multiplication(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            result_sign = (sign1 == sign2) ? +1 : -1;
        }

        /* ----------- Division Case ------------- */
        else if (operator == '/')
        {
            division(&head1, &tail1, &head2, &tail2, &headR, &tailR);
            result_sign = (sign1 == sign2) ? +1 : -1;

            // // Optional: if quotient is zero, make sign positive
            // if (headR && headR->data == 0 && headR == *tailR)
            //     result_sign = +1;
        }

        else
        {
            /* Invalid operator handling */
            printf("Invalid operator!\n");
        }

        /* Display the final result */
        display_operation(head1, head2, headR, operator, sign1, sign2, result_sign);


        /* Ask user to perform another calculation */
        printf("\nWant to continue? Press [yY | nN]: ");
        scanf("\n%c", &option);

        /* Reset lists before reusing for next iteration */
        head1 = tail1 = head2 = tail2 = headR = tailR = NULL;

    } while (option == 'y' || option == 'Y');

    return 0;
}
