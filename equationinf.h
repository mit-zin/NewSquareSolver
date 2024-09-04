#ifndef EQUATIONINF_H
#define EQUATIONINF_H

const int ROOTS_SIZE = 4;
const int MAX_STROOTS_LEN = 10;
const char stRoots[4][MAX_STROOTS_LEN] = {"NO_ROOTS", "ONE_ROOT", "TWO_ROOTS", "INF_ROOTS"};

enum roots
{
    NO_ROOTS  = 0,
    ONE_ROOT  = 1,
    TWO_ROOTS = 2,
    INF_ROOTS = 3
};

struct SolverParameters
{
    double a, b, c;
    double x1, x2;
};

#endif
