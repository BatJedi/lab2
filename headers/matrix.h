#ifndef MATRIX
#define MATRIX

typedef struct matrix
{
  unsigned int rows;
  unsigned int cols;
  float **mat;
}* matrix;

int matrixalloc(matrix);
matrix creatematrix(int rows, int cols);
matrix emptyMatrixStruct();
void freematrix(matrix);
#endif
