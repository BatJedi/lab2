#include "matrix.h"
#include <stdlib.h>

matrix emptyMatrixStruct() //allocates space for a matrix struct and returns pointer to it.
{
  matrix res = malloc(sizeof(struct matrix));
  return res;
}

int matrixalloc(matrix X)
{
  if(X == NULL) return 1;
  
  int rows = X->rows;
  int cols = X->cols;
  X->R = malloc(sizeof(float*)*rows);
  X->G = malloc(sizeof(float*)*rows);
  X->B = malloc(sizeof(float*)*rows);
  for(int i = 0; i<rows; i++)
  {
    X->R[i] = malloc(sizeof(float)*cols);
    X->G[i] = malloc(sizeof(float)*cols);
    X->B[i] = malloc(sizeof(float)*cols);
  }
  return 0;
}

matrix creatematrix(int rows,int cols)
{
  matrix res = emptyMatrixStruct();
  res->rows = rows;
  res->cols = cols;
  if(matrixalloc(res) != 0) return NULL;
  return res;
}

void freematrix(matrix X)
{
  for(int i = 0; i<X->rows; i++)
  {
    free(X->R[i]);
    free(X->G[i]);
    free(X->B[i]);
  }
  free(X->R);
  free(X->G);
  free(X->B);
  free(X);
}
