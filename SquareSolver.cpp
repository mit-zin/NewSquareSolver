#include <stdio.h>

#include "Solver.h"
#include "Utilities.h"
#include "Request.h"
#include "UnitTests.h"
#include "result.h"
#include "colortext.h"

int main(void)
{
    enum result res = TestModule();

    if (res == SUCCESS)
        res = SolverModule();
    else
        ErrorPrint(res);

    PRINTF_USUAL("End of programm.");

    return SUCCESS;
}
