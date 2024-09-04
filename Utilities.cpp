#include <assert.h>
#include <math.h>
#include <stdio.h>

#include "Utilities.h"

// changes -0 to 0
double MinusZeroCheck(double num)
{
    return (DoubleCompare(num, 0) == EQUAL) ? fabs(num) : num;
}

// compares double values
enum compareResult DoubleCompare(double num1, double num2)
{
    if (num1 - num2 > EPSILON)
        return FIRST_BIGGER;
    else if (num1 - num2 < -EPSILON)
        return SECOND_BIGGER;
    else
        return EQUAL;
}

// changes roots if x1 > x2
void SortRoots(double* x1, double* x2)
{
    assert(x1);
    assert(x2);

    if (*x1 > *x2)
    {
        double change = *x1;
        *x1 = *x2;
        *x2 = change;
    }
}

// clears buffer
enum result BufferClear(void)
{
    int c = 0;

    while (((c = getchar()) != '\n')  &&  (c != SUB) && (c != EOF));

    if (c == EOF)
        return EOF_FOUND;
    else
        return SUCCESS;
}

// prints type of an error
void ErrorPrint(enum result res)
{
    PRINTF_RED_ITAL();

    switch (res)
    {
        case EOF_FOUND :
            printf("End of file.\n");
            break;
        case FILE_READ_ER :
            printf("Error while file reading.\n");
            break;
        case FILE_NOT_FOUND :
            printf("File was not found.\n");
            break;
        case UNKNOWN_ERROR :
            printf("Unknown error.\n");
            break;
        case NULL_POINTER :
            printf("Null pointer.\n");
            break;
        default:
            printf("Unknown error.\n");
    }
}
