#ifndef UNITTESTS_H
#define UNITTESTS_H

#include "result.h"
#include "equationinf.h"
#include "colortext.h"
#include "Utilities.h"
#include "Request.h"
#include "Solver.h"

enum testResult
{
    NO_ERRORS = 0,
    ONE_ERROR = 1
};

struct TestData
{
    double a, b, c;
    double x1Right, x2Right;
    enum roots nRootsRight;
    int nTest;
};

enum result     TestModule     (void);
enum result     UnitTester     (int *nErrors);
enum testResult Test           (struct TestData data);
enum result     FileRead       (struct TestData data[], size_t arSize, FILE * fp);
enum result     xRightRead     (FILE *fp, double *xRight);
enum result     nRootsRightRead(FILE *fp, enum roots *nRootsRight);

#endif
