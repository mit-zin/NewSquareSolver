#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "UnitTests.h"

enum result TestModule(void)
{
    PRINTF_USUAL("Do you wnat to start unit testing?");
    enum yes_no testReq = NO;

    if (Request(&testReq) == SUCCESS)
    {
        if (testReq == YES)
        {
            int nErrors = 0;

            enum result res = UnitTester(&nErrors);

            if (res != SUCCESS)
                return res;
            else
                PRINTF_ITALICS("Number of errors: %d\n", nErrors);
        }

        return SUCCESS;
    }
    else
        return EOF_FOUND;
}

enum result UnitTester(int *nErrors)
{
    assert(nErrors);

    FILE *fp = fopen("data.txt", "r");
    if (!fp)
        return FILE_NOT_FOUND;

    size_t arSize = 0;

    int scanRes = fscanf(fp, "%u", &arSize);
    switch (scanRes)
    {
        case EOF :
            return EOF_FOUND;
        case 0 :
            return FILE_READ_ER;
        case 1 :
            break;
        default :
            return UNKNOWN_ERROR;
    }

    struct TestData *tests = (struct TestData *) calloc(arSize, sizeof(struct TestData));
    if (!tests)
    {
        return NULL_POINTER;
    }

    enum result res = FileRead(tests, arSize, fp);
    fclose(fp);

    if (res == SUCCESS)
    {
        for (size_t i = 0; i < arSize; i++)
            *nErrors += Test(tests[i]);

        free(tests);
        tests = NULL;

        return SUCCESS;
    }
    else
    {
        free(tests);
        tests = NULL;

        return res;
    }
}

// single test
enum testResult Test(struct TestData data)
{
    struct SolverParameters par = {data.a, data.b, data.c, NAN, NAN};
    enum roots nRoots = Solve(&par);

    SortRoots(&(data.x1Right), &(data.x2Right));

    if (nRoots != data.nRootsRight ||
        DoubleCompare(par.x1, data.x1Right) ||
        DoubleCompare(par.x2, data.x2Right))
    {
        PRINTF_RED_ITAL("Error Test %d: a = %lg, b = %lg, c = %lg, x1 = %lg, x2 = %lg, nRoots = %d\n"
                        "Expected: x1 = %lg, x2 = %lg, nRoots = %d\n",
                    data.nTest, data.a,
                    data.b, data.c,
                    par.x1, par.x2,
                    nRoots, data.x1Right,
                    data.x2Right, data.nRootsRight);

        return ONE_ERROR;
    }
    else
        return NO_ERRORS;
}

// reads test data from a file
enum result FileRead(struct TestData data[], size_t arSize, FILE *fp)
{
    assert(fp);

    for (size_t i = 0; i < arSize; i++)
    {
        int scRes = fscanf(fp, "%d %lf %lf %lf",
                           &data[i].nTest, &data[i].a, &data[i].b, &data[i].c);
        switch (scRes)
        {
            case EOF :
                return EOF_FOUND;
            case 4 :
                break;
            default:
                return FILE_READ_ER;
        }

        enum result res = xRightRead(fp, &data[i].x1Right);
        if (res != SUCCESS)
            return res;
        res = xRightRead(fp, &data[i].x2Right);
        if (res != SUCCESS)
            return res;

        res = nRootsRightRead(fp, &data[i].nRootsRight);
        if (res != SUCCESS)
            return res;
    }

    return SUCCESS;
}

// reads right roots
enum result xRightRead(FILE *fp, double *xRight)
{
    assert(fp);
    assert(xRight);

    int res = fscanf(fp, "%lf", xRight);

    switch (res)
    {
        case EOF :
            return EOF_FOUND;
        case 0 :
        {
            const int ST_NAN_LEN = 4;

            char stXRight[ST_NAN_LEN] = {};

            fscanf(fp, "%s", stXRight);

            if (!strcmp(stXRight, "NAN"))
            {
                *xRight = NAN;

                return SUCCESS;
            }
            else
                return FILE_READ_ER;
        }
        case 1 :
            return SUCCESS;
        default:
            return UNKNOWN_ERROR;
    }
}

// reads right number of roots
enum result nRootsRightRead(FILE *fp, enum roots *nRootsRight)
{
    assert(fp);
    assert(nRootsRight);

    char stNRootsRight[MAX_STROOTS_LEN] = {};

    int res = fscanf(fp, "%s", stNRootsRight);

    switch (res)
    {
        case 1 :
            for (int i = 0; i < ROOTS_SIZE; i++)
            {
                if (!strcmp(stNRootsRight, stRoots[i]))
                {
                    int numInRoots = i;

                    switch (numInRoots)
                    {
                        case NO_ROOTS :
                            *nRootsRight = NO_ROOTS;
                            break;
                        case ONE_ROOT :
                            *nRootsRight = ONE_ROOT;
                            break;
                        case TWO_ROOTS :
                            *nRootsRight = TWO_ROOTS;
                            break;
                        case INF_ROOTS :
                            *nRootsRight = INF_ROOTS;
                            break;
                        default:
                            return FILE_READ_ER;
                    }

                    return SUCCESS;
                }
            }

            return FILE_READ_ER;
        case EOF :
            return EOF_FOUND;
        case 0 :
            return FILE_READ_ER;
        default :
            return UNKNOWN_ERROR;
    }
}
