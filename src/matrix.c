#include "matrix.h"
#include <stdlib.h>

matrix emptyMatrixStruct() //allocates space for a matrix struct and returns pointer to it.
{
  matrix res = (matrix)malloc(sizeof(struct matrix));
  if(!res) return NULL;
  return res;
}

int matrixalloc(matrix X)
{
  if(X == NULL) return 1;
  
  int rows = X->rows;
  int cols = X->cols;
  X->R = (int**)malloc(sizeof(int*)*rows);
  if(!(X->R)) return 2;
  X->G = (int**)malloc(sizeof(int*)*rows);
  if(!(X->G)) return 2;
  X->B = (int**)malloc(sizeof(int*)*rows);
  if(!(X->B)) return 2;
  for(int i = 0; i<rows; i++)
  {
    X->R[i] = (int*)malloc(sizeof(int)*cols);
    if(!(X->R[i])) return 2;
    X->G[i] = (int*)malloc(sizeof(int)*cols);
    if(!(X->G[i])) return 2;
    X->B[i] = (int*)malloc(sizeof(int)*cols);
    if(!(X->B[i])) return 2;
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
  if(!X) return;
  for(int i = 0; i<X->rows; i++)
  {
    if(X->R[i] != NULL) free(X->R[i]);
    if(X->G[i] != NULL) free(X->G[i]);
    if(X->B[i] != NULL) free(X->B[i]);
  }
  if(X->R != NULL) free(X->R);
  if(X->G != NULL) free(X->G);
  if(X->B != NULL) free(X->B);
  free(X);
}
