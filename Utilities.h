#ifndef UTILITIES_H
#define UTILITIES_H

#include "result.h"
#include "colortext.h"

const int SUB = 26;
const double EPSILON = 1e-6;

double             MinusZeroCheck(double num);
enum compareResult DoubleCompare (double num1, double num2);
void               SortRoots     (double* x1, double* x2);
enum result        BufferClear   (void);
void               ErrorPrint    (enum result res);

#endif
