#include "matrixmath.h"
#include "matrix.h"
#include "transformations.h"
#include "ppm.h"
#include <stdlib.h>
#include <stdio.h>

matrix flipTrans(matrix X)
{
  matrix flipped = emptyMatrixStruct();
  matrix transformation = flippedIdentity(X->cols);
  if(multiply(flipped, X, transformation) != 0) return NULL;
  freematrix(transformation);
  return flipped;
}

int applyFlipping(image toFlip)
{
  if(!toFlip) return 1;
  matrix img = toFlip->img;
  matrix flippedimg = flipTrans(img);
  toFlip->img = flippedimg;
  if(img != NULL) freematrix(img);
  else return 1;
  return 0;
}

int applyBlur(image toBlur)
{
  if(!toBlur) return 1;
  int padval = 255;
  matrix img = toBlur->img;
  matrix kernel = ones(3,3);
  matrix conv = convolution(kernel, img, padval);
  freematrix(kernel);
  float scalar = 1.0/9.0; 
  if(scale(conv, scalar) != 0)
  {
    fprintf(stderr, "Error applying blur\n");
    return 1;
  }
  toBlur->img = conv;
  if(img != NULL) freematrix(img);
  else return 1;
  return 0;
}
