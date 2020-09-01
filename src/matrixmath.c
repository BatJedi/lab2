#include "matrixmath.h"
#include "matrix.h"
#include "transformations.h"
#include <stdlib.h>

int multiply(matrix *P, matrix *A, matrix *B)
{
  if(A->cols != B->rows)
  {
    return 1;
  }
  
  int rows = A->rows;
  int cols = B->cols;
  int Acols = A->cols;
  P->rows = rows;
  P->cols = cols;
  
  if(matrixalloc(P) != 0) return 2;
  
  for(int i = 0; i<rows; i++)
  {
    for (int j = 0; j<cols; j++)
    {
      for(int k = 0; k<Acols; k++)
      {
	P->R[i][j] += (A->R[i][k] * B->R[k][j]);
	P->G[i][j] += (A->G[i][k] * B->G[k][j]);
	P->B[i][j] += (A->B[i][k] * B->B[k][j]);
      }
    }
  }
  return 0;
}



matrix *flippedIdentity(int n)
{
  matrix *fi = malloc(sizeof(matrix));
  fi->rows = n;
  fi->cols = n;
  if(matrixalloc(fi) != 0) return NULL;
  for(int i = 0; i<n; i++)
  {
    for(int j = 0; j<n; j++)
    {
      if(i+j == n-1)
      {
	fi->R[i][j] = 1;
	fi->G[i][j] = 1;
	fi->B[i][j] = 1;
      }
      else
      {
	fi->R[i][j] = 0;
	fi->G[i][j] = 0;
	fi->B[i][j] = 0;
      }
    }
  }
  return fi;
}
