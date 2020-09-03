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

matrix sharpen(matrix X)
{
  int padval = 0;
  if(!X) return X;
  matrix kernel = sharpenKernel();
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

int applySharpen(image toSharpen)
{
  if(!toSharpen) return 1;
  matrix img = toSharpen->img;
  matrix sharpened = sharpen(img);
  if(!sharpened) return 1;
  toSharpen->img = sharpened;
  if(img != NULL) freematrix(img);
  else return 1;
  return 0;
}

matrix sharpenKernel()
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
  result->R[1][1] = 1;
  result->G[1][1] = 1;
  result->B[1][1] = 1;
  return result;
}

