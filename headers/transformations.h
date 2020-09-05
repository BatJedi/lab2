#ifndef TRANSFORMATIONS
#define TRANSFORMATIONS
#include "matrix.h"
#include "ppm.h"

matrix flipTrans(matrix);
int applyBlur(image);
int applyFlipping(image);
int applyCenterFlipping(image, int, int);
matrix blur(matrix, int);
int applyDeepFry(image, int);
matrix deepFry(matrix, int);
matrix fryKernel(int);
#endif
