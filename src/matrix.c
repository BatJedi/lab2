#include "matrix.h"
#include <stdlib.h>

matrix emptyMatrixStruct() //allocates space for a matrix struct and returns pointer to it.
{
  matrix res = (matrix)malloc(sizeof(struct matrix));
  return res;
}

int matrixalloc(matrix X)
{
  if(X == NULL) return 1;
  
  int rows = X->rows;
  int cols = X->cols;
  X->R = (unsigned char**)malloc(sizeof(unsigned char*)*rows);
  X->G = (unsigned char**)malloc(sizeof(unsigned char*)*rows);
  X->B = (unsigned char**)malloc(sizeof(unsigned char*)*rows);
  for(int i = 0; i<rows; i++)
  {
    X->R[i] = (unsigned char*)malloc(sizeof(unsigned char)*cols);
    X->G[i] = (unsigned char*)malloc(sizeof(unsigned char)*cols);
    X->B[i] = (unsigned char*)malloc(sizeof(unsigned char)*cols);
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
