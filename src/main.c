#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrixmath.h"

int main()
{
  matrix * inp = malloc(sizeof(matrix));
  inp->rows = 5;
  inp->cols = 5;
  if(matrixalloc(inp)!= 0) return 1;
  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<5;j++)
    {
      inp->R[i][j] = i+j;
      inp->G[i][j] = i+j;
      inp->B[i][j] = i+j;
    }
  }
  matrix *transformed = flipTrans(inp);
  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<5;j++)
    {
      printf("%d ", inp->R[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  
  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<5;j++)
    {
      printf("%d ", transformed->R[i][j]);
    }
    printf("\n");
  }
  freematrix(inp);
  freematrix(transformed);
}
