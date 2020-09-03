#ifndef MATRIX
#define MATRIX

typedef struct matrix
{
  unsigned int rows;
  unsigned int cols;
  unsigned char **R;
  unsigned char **G;
  unsigned char **B;
}* matrix;

int matrixalloc(matrix);
matrix creatematrix(int rows, int cols);
matrix emptyMatrixStruct();
void freematrix(matrix);
#endif
