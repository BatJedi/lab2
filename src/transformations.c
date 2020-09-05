#include "matrixmath.h"
#include "matrix.h"
#include "transformations.h"
#include "ppm.h"
#include <stdlib.h>
#include <stdio.h>

matrix flipTrans(matrix X)
{
  if(!X) return X;
  matrix flipped = emptyMatrixStruct();
  matrix transformation = flippedIdentity(X->cols);
  if(multiply(flipped, X, transformation) != 0) return NULL;
  freematrix(transformation);
  return flipped;
}

matrix blur(matrix X, int padval)
{
  if(!X) return X;
  int bluramt = 3.0;
  matrix kernel = ones(bluramt,bluramt);
  if(!kernel) return NULL;
  matrix conv = convolution(kernel, X, padval);
  if(!conv) return NULL;
  freematrix(kernel);
  float scalar = 1.0/(bluramt*bluramt); 
  if(scale(conv, scalar) != 0)
  {
    fprintf(stderr, "Error applying blur\n");
    return X;
  }
  return conv;
}

matrix deepFry(matrix X, int degree)
{
  int padval = 0;
  if(!X) return X;
  matrix kernel = fryKernel(degree);
  if(!kernel) return NULL;
  matrix conv = convolution(kernel, X, padval);
  if(!conv) return NULL;
  freematrix(kernel);
  return conv;
}

int applyFlipping(image toFlip)
{
  if(!toFlip) return 1;
  matrix img = toFlip->img;
  matrix flippedimg = flipTrans(img);
  if(!flippedimg) return 1;
  toFlip->img = flippedimg;
  if(img != NULL) freematrix(img);
  else return 1;
  return 0;
}

int applyCenterFlipping(image toFlip, int centerRows, int centerCols)
{
  if(!toFlip) return 1;
  matrix img = toFlip->img;
  if(img->rows < centerRows || img->cols < centerCols)
  {
    fprintf(stderr, "Invalid center matrix dimensions\n");
    return 1;
  }    
  matrix center = creatematrix(centerRows, centerCols);
  if(!center)
  {
    fprintf(stderr, "Error in space allocation for new matrix\n");
    return 1;
  }
  if(fillCenter(img, center) != 0)
  {
    fprintf(stderr, "Error in flipping center\n");
    return 1;
  }
  matrix flippedCenter = flipTrans(center);
  freematrix(center);
  if(!flippedCenter)
    return 1;
  if(swapCenter(img, flippedCenter) != 0)
  {
    fprintf(stderr, "Error in swapping center\n");
    return 1;
  }
  freematrix(flippedCenter);
}

int applyBlur(image toBlur)
{
  int padval = 0;
  if(!toBlur) return 1;
  matrix img = toBlur->img;
  matrix blurred = blur(img, padval);
  if(!blurred) return 1;
  toBlur->img = blurred;
  if(img != NULL) freematrix(img);
  else return 1;
  return 0;
}

int applyDeepFry(image toFry, int degree)
{
  if(!toFry) return 1;
  matrix img = toFry->img;
  matrix fried = deepFry(img, degree);
  if(!fried) return 1;
  toFry->img = fried;
  if(img != NULL) freematrix(img);
  else return 1;
  return 0;
}

matrix fryKernel(int n)
{
  matrix result = creatematrix(3,3);
  if(!result) return NULL;

  for(int i = 0; i<3; i++)
  {
    for(int j = 0; j<3; j++)
    {
      if(i+j == 1 || i+j == 3)
      {
	result->R[i][j] = 0;
	result->G[i][j] = 0;
	result->B[i][j] = 0;
      }
      else
      {
	result->R[i][j] = 0;
	result->G[i][j] = 0;
	result->B[i][j] = 0;
      }
    }
  }
  result->R[1][1] = n;
  result->G[1][1] = n;
  result->B[1][1] = n;
  return result;
}

