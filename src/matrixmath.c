#include "matrixmath.h"
#include "matrix.h"
#include "transformations.h"
#include <stdlib.h>

int multiply(matrix P, matrix A, matrix B) //multiplies A and B and stores the result in P. Note that to call this function, you need to allocate space for
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
    for (int j = 0; j<cols; j++)
      for(int k = 0; k<Acols; k++)
	P->mat[i][j] += (A->mat[i][k] * B->mat[k][j]);
  
  return 0;
}



matrix flippedIdentity(int n)
{
  matrix fi = creatematrix(n,n);
  if(fi == NULL) return NULL;
  for(int i = 0; i<n; i++)
    for(int j = 0; j<n; j++)
      if(i+j == n-1)
	fi->mat[i][j] = 1;
      else
	fi->mat[i][j] = 0;
      
  return fi;
}
