#include "matrixmath.h"
#include "matrix.h"
#include "transformations.h"
#include <stdlib.h>

matrix flipTrans(matrix X)
{
  matrix flipped = emptyMatrixStruct();
  matrix transformation = flippedIdentity(X->cols);
  if(multiply(flipped, X, transformation) != 0) return NULL;
  freematrix(transformation);
  return flipped;
}

//changes made here 
matrix randfilterTrans(matrix X)
{
  matrix filtered = emptyMatrixStruct();
  matrix filter = fillrand(X->rows, X->cols);
  if(multiply(filtered, X, filter) !=0) return NULL;
  return filtered;
}