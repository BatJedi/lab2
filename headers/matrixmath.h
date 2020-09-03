#include "matrix.h"
#ifndef MATRIXMATH
#define MATRIXMATH

int multiply(matrix , matrix , matrix );
matrix flippedIdentity(int);
matrix ones(int, int);
int scale(matrix, float);
matrix convolution(matrix, matrix, int);
#endif
