#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Solver.h"

enum result SolverModule(void)
{
    PRINTF_USUAL("I can solve quadratic equations.\n");
    printf("The quadratic equation has the form: ax^2 + bx + c = 0\n");

    enum yes_no solvReq = YES;
    while (solvReq == YES)
    {
        if (SingleEquation() == EOF_FOUND)
            return EOF_FOUND;

        PRINTF_USUAL("Do you want me to solve one more equation?");

        if (Request(&solvReq) == EOF_FOUND)
            return EOF_FOUND;
    }

    return SUCCESS;
}

enum result SingleEquation(void)
{
    struct SolverParameters par = {NAN, NAN, NAN, NAN, NAN};

    if (SolverInput(&par) == SUCCESS)
    {
        enum roots nRoots = Solve(&par);

        SolverOutput(nRoots, par.x1, par.x2);

        return SUCCESS;
    }
    else
        return EOF_FOUND;
}

enum roots Solve(SolverParameters *par)
{
    assert(par);

    return (DoubleCompare((*par).a, 0) != EQUAL) ? SquareSolve(par) : LinearSolve(par);
}

enum roots LinearSolve(struct SolverParameters *par)
{
    assert(par);

    if (DoubleCompare((*par).b, 0) == EQUAL)
        return (DoubleCompare((*par).c, 0) == EQUAL) ? INF_ROOTS : NO_ROOTS;
    else
    {
        (*par).x1 = MinusZeroCheck(-(*par).c / (*par).b);

        return ONE_ROOT;
    }
}

enum roots SquareSolve(SolverParameters *par)
{
    assert(par);
    assert(DoubleCompare((*par).a, 0));

    double d = (*par).b * (*par).b - 4 * (*par).a * (*par).c;
    enum compareResult cmpRes = DoubleCompare(d, 0);

    switch (cmpRes)
    {
        case FIRST_BIGGER :
            (*par).x1 = MinusZeroCheck((-(*par).b - sqrt(d)) / (2 * (*par).a));
            (*par).x2 = MinusZeroCheck((-(*par).b + sqrt(d)) / (2 * (*par).a));

            SortRoots(&(*par).x1, &(*par).x2);

            return TWO_ROOTS;
        case EQUAL :
            (*par).x1 = MinusZeroCheck(-(*par).b / 2 / (*par).a);

            return ONE_ROOT;
        case SECOND_BIGGER :
            return NO_ROOTS;
    }
}

enum result SolverInput(struct SolverParameters *par)
{
    assert(par);

    PRINTF_USUAL("Enter coefficients a, b and c separated by a space\n");
    PRINTF_ORAN_FORE();

    int EofCheck = 0;

    while ((EofCheck = scanf("%lf %lf %lf", &(*par).a, &(*par).b, &(*par).c)) != 3)
    {
        if (EofCheck == EOF)
            return EOF_FOUND;

        if (BufferClear() == EOF_FOUND)
            return EOF_FOUND;

        PRINTF_RED("Enter the coefficients right\n");
        PRINTF_ORAN_FORE();
    }

    if (BufferClear() == EOF_FOUND)
        return EOF_FOUND;

    return SUCCESS;
}

void SolverOutput(enum roots nRoots, double x1, double x2)
{
    PRINTF_GREEN();

    switch (nRoots)
    {
        case NO_ROOTS :
            printf("The equation has no roots.\n");
            break;
        case ONE_ROOT :
            printf("The equation has one root: %g\n", x1);
            break;
        case TWO_ROOTS :
            printf("The equation has two roots: %g and %g\n", x1, x2);
            break;
        case INF_ROOTS :
            printf("The equation has an infinite number of roots\n");
            break;
        default :
            PRINTF_RED_ITAL("error\n");
    }
}
