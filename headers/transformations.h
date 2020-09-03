#ifndef TRANSFORMATIONS
#define TRANSFORMATIONS
#include "matrix.h"
#include "ppm.h"

matrix flipTrans(matrix);
int applyBlur(image);
int applyFlipping(image);
matrix blur(matrix, int);
int applySharpen(image);
matrix sharpen(matrix);
matrix sharpenKernel();
#endif
