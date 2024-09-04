#ifndef SOLVER_H
#define SOLVER_H

#include "result.h"
#include "equationinf.h"
#include "colortext.h"
#include "Utilities.h"
#include "Request.h"

enum result SolverModule  (void);
enum result SingleEquation(void);
enum result SolverInput   (struct SolverParameters *par);
void        SolverOutput  (enum roots nRoots, double x1, double x2);
enum roots  Solve         (struct SolverParameters *par);
enum roots  LinearSolve   (struct SolverParameters *par);
enum roots  SquareSolve   (struct SolverParameters *par);

#endif
