#ifndef MATRIX
#define MATRIX

typedef struct matrix
{
  unsigned int rows;
  unsigned int cols;
  int **R;
  int **G;
  int **B;
} matrix;

int matrixalloc(matrix *);
void freematrix(matrix *);
#endif
