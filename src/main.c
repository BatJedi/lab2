#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrixmath.h"
#include "transformations.h"

int main()
{
  int rows = 5;
  int cols = 5;
  matrix inp = creatematrix(rows, cols);
  if(inp == NULL) return 1;
  for(int i = 0; i<5; i++)
    for(int j = 0; j<5;j++)
      inp->mat[i][j] = i+j;
  
  matrix transformed = flipTrans(inp);
  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<5;j++)
    {
      printf("%f ", inp->mat[i][j]);
    }
    printf("\n");
  }

  printf("\n");
  
  for(int i = 0; i<5; i++)
  {
    for(int j = 0; j<5;j++)
    {
      printf("%f ", transformed->mat[i][j]);
    }
    printf("\n");
  }
  freematrix(inp);
  freematrix(transformed);
}
