#include "apc.h"

/* 
 * Function: compare
 * Purpose : Compare magnitude of numbers passed as command-line arguments (string form)
 * Return  : SUCCESS if a >= b, FAILURE if a < b
 */
int compare(char *argv[])
{
    char *a = argv[1];
    char *b = argv[3];

    /* Skip sign if present */
    if (a[0] == '+' || a[0] == '-') a++;
    if (b[0] == '+' || b[0] == '-') b++;

    /* Skip leading zeros (e.g., 000123 → 123) */
    while (*a == '0' && a[1] != '\0') a++;
    while (*b == '0' && b[1] != '\0') b++;

    int len1 = strlen(a);
    int len2 = strlen(b);

    /* Step 1: Compare length — longer number is larger */
    if (len1 < len2) return FAILURE;
    if (len1 > len2) return SUCCESS;

    /* Step 2: Compare digit-by-digit if lengths are equal */
    for (int i = 0; i < len1; i++)
    {
        if (a[i] < b[i]) return FAILURE;
        if (a[i] > b[i]) return SUCCESS;
    }

    /* Numbers are equal → treat as a >= b */
    return SUCCESS;
}


/*
 * Function: dl_insert_first
 * Purpose : Insert a new node at the beginning of a doubly linked list
 */
int dl_insert_first(Dlist **head, Dlist **tail, int data)
{
    Dlist *new = malloc(sizeof(Dlist));
    new->data = data;

    /* First node insertion in an empty list */
    if (*head == NULL && *tail == NULL)
    {
        *head = new;
        *tail = new;
        new->next = NULL;
        new->prev = NULL;
        return SUCCESS;
    }
    else
    {
        /* Insert before existing head */
        new->next = *head;
        (*head)->prev = new;
        (*head) = new;
        return SUCCESS;
    }
}


/*
 * Function: reading_data
 * Purpose : Convert numeric string to doubly linked list (stored in reverse order)
 *           Example: "123" → 3→2→1
 */
int reading_data(char *str, Dlist **head, Dlist **tail)
{
    int len = (strlen(str) - 1);

    /* Ignore sign symbol if present */
    if (str[0] == '-' || str[0] == '+')
    {
        while (len > 0)
        {
            int data = str[len] - 48;   // Convert char to int
            dl_insert_first(head, tail, data);
            len--;
        }
    }
    else
    {
        while (len >= 0)
        {
            int data = str[len] - 48;
            dl_insert_first(head, tail, data);
            len--;
        }
    }
}


/*
 * Function: validation
 * Purpose : Check if input format is valid (number operator number)
 */
int validation(int argc, char *argv[])
{
    if (argc != 4)
        return FAILURE;

    /* Validate first number (allow optional + / - sign) */
    if (argv[1][0] == '+' || argv[1][0] == '-')
    {
        int i = 1;
        while (argv[1][i] != '\0')
        {
            if (!(argv[1][i] >= 48 && argv[1][i] <= 57))
            {
                return FAILURE;
            }
            i++;
        }
    }
    else
    {
        int i = 0;
        while (argv[1][i] != '\0')
        {
            if (!(argv[1][i] >= 48 && argv[1][i] <= 57))
            {
                return FAILURE;
            }
            i++;
        }
    }

    /* Validate second number */
    if (argv[3][0] == '+' || argv[3][0] == '-')
    {
        int j = 1;
        while (argv[3][j] != '\0')
        {
            if (!(argv[3][j] >= 48 && argv[3][j] <= 57))
            {
                return FAILURE;
            }
            j++;
        }
    }
    else
    {
        int j = 0;
        while (argv[3][j] != '\0')
        {
            if (!(argv[3][j] >= 48 && argv[3][j] <= 57))
            {
                return FAILURE;
            }
            j++;
        }
    }

    /* Validate operator (+ - x /) */
    int len = strlen(argv[2]);
    if (len == 1)
    {
        return argv[2][0];  // Return operator
    }
    else
    {
        return FAILURE;
    }
}


/*
 * Function: display_operation
 * Purpose : Prints numbers and result aligned mathematically like manual calculation
 */
void display_operation(Dlist *head1, Dlist *head2, Dlist *headR,char operator, int sign1, int sign2, int result_sign)
{
    // Step 1: Convert each list to a string (digits only)
    char num1[1024], num2[1024], result[1024];
    int i = 0;

    Dlist *temp = head1;
    while (temp)
    {
        num1[i++] = temp->data + '0';
        temp = temp->next;
    }
    num1[i] = '\0';

    i = 0;
    temp = head2;
    while (temp)
    {
        num2[i++] = temp->data + '0';
        temp = temp->next;
    }
    num2[i] = '\0';

    i = 0;
    temp = headR;
    while (temp)
    {
        result[i++] = temp->data + '0';
        temp = temp->next;
    }
    result[i] = '\0';

    // Step 2: Build signed strings (prepend '-' when sign is -1)
    char s_num1[1025], s_num2[1025], s_res[1025];

    if (sign1 == -1)
    {
        s_num1[0] = '-';
        strcpy(s_num1 + 1, num1);
    }
    else
    {
        strcpy(s_num1, num1);
    }

    if (sign2 == -1)
    {
        s_num2[0] = '-';
        strcpy(s_num2 + 1, num2);
    }
    else
    {
        strcpy(s_num2, num2);
    }

    if (result_sign == -1)
    {
        s_res[0] = '-';
        strcpy(s_res + 1, result);
    }
    else
    {
        strcpy(s_res, result);
    }

    // Step 3: Determine width (for right alignment)
    int len1 = strlen(s_num1);
    int len2 = strlen(s_num2);
    int lenR = strlen(s_res);

    int width = len1;
    if (len2 + 2 > width)
        width = len2 + 2; // +2 for operator and one space
    if (lenR > width)
        width = lenR;

    // Step 4: Print aligned output
    printf("\n%*s\n", width, s_num1);                      // First number
    printf("%c%*s\n", operator, width - 1, s_num2);        // Operator + second number
    for (int j = 0; j < width; j++)
        printf("-");
    printf("\n");
    printf("%*s\n", width, s_res);                         // Result
}



/*
 * Function: comparelist
 * Purpose : Compare numeric values stored in two linked lists
 * Return  : SUCCESS if head1 >= head2, FAILURE otherwise
 */
int comparelist(Dlist *head1, Dlist *head2)
{
    int x = length(head1);
    int y = length(head2);

    /* Longer list → larger number */
    if (x > y)
        return SUCCESS;
    if (x < y)
        return FAILURE;

    /* Same length → compare digit-by-digit */
    while (head1 && head2)
    {
        if (head1->data > head2->data)
            return SUCCESS;

        if (head1->data < head2->data)
            return FAILURE;

        head1 = head1->next;
        head2 = head2->next;
    }

    return SUCCESS;  // Equal numbers
}


/*
 * Function: remove_leading_zero
 * Purpose : Remove unnecessary zeros at number start (e.g., 000234 → 234)
 */
void remove_leading_zero(Dlist **head, Dlist **tail)
{
    while (*head && (*head)->data == 0 && *head != *tail)
    {
        Dlist *temp = *head;
        *head = (*head)->next;
        (*head)->prev = NULL;
        free(temp);
    }

    /* Update new tail */
    Dlist *t = *head;
    while (t && t->next)
        t = t->next;

    *tail = t;
}


/*
 * Function: free_list
 * Purpose : Free allocated linked list memory
 */
void free_list(Dlist **head, Dlist **tail)
{
    Dlist *temp = *head;

    while (temp)
    {
        Dlist *next = temp->next;
        free(temp);
        temp = next;
    }

    *head = NULL;
    *tail = NULL;
}


/*
 * Function: length
 * Purpose : Returns number of nodes (digits) in list
 */
int length(Dlist *head)
{
    int len = 0;
    while (head)
    {
        len++;
        head = head->next;
    }
    return len;
}

int dl_insert_last(Dlist **head, Dlist **tail, int data)
{
    /* Allocate memory for new node */
    Dlist *new = malloc(sizeof(Dlist));

    /* Check memory allocation failure */
    if (!new)
    {
        return FAILURE;
    }

    new->data = data;
    new->prev = NULL;
    new->next = NULL;

    /* Case 1: List is empty */
    if (*head == NULL && *tail == NULL)
    {
        *head = *tail = new;
        return SUCCESS;
    }

    /* Case 2: Append to end */
    new->prev = *tail;
    (*tail)->next = new;
    *tail = new;

    return SUCCESS;
}
