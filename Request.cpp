#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "Request.h"

// asks to enter yes or no
enum result Request(enum yes_no * answer)
{
    assert(answer);

    PRINTF_USUAL(" Enter \"yes\" or \"no\" (without spaces or other symbols).\n");
    PRINTF_ORAN_FORE();

    const int LAST_SYMB_OF_ANS = 3;
    const int SIZE_ANS         = 5;

    char input[SIZE_ANS] = {};

    char *eofCheck = fgets(input, SIZE_ANS, stdin);

    while (strcmp(input, "yes\n") && strcmp(input, "no\n"))
    {
        if (!eofCheck)
            return EOF_FOUND;

        PRINTF_RED("You must enter only \"yes\" or \"no\".\n");
        PRINTF_ORAN_FORE();

        if (input[LAST_SYMB_OF_ANS] != '\0' && input[LAST_SYMB_OF_ANS] != '\n')
        {
            if (BufferClear() == EOF_FOUND)
                return EOF_FOUND;
        }

        ArrClear(input, SIZE_ANS);

        eofCheck = fgets(input, SIZE_ANS, stdin);
    }

    *answer = (!strcmp(input, "yes\n")) ? YES : NO;

    return SUCCESS;
}

// clears an array
void ArrClear(char arr[], int arSize)
{
    for (int i = 0; i < arSize; i++)
        arr[i] = '\0';
}
