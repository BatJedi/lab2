#include "matrixmath.h"
#include "matrix.h"
#include "transformations.h"
#include <stdlib.h>

matrix *flipTrans(matrix *X)
{
  matrix *flipped = malloc(sizeof(matrix));
  matrix *transformation = flippedIdentity(X->cols);
  if(multiply(flipped, X, transformation) != 0) return NULL;
  freematrix(transformation);
  return flipped;
}
