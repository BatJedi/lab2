#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrixmath.h"
#include "transformations.h"
#include "ppm.h"

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

int main()
{
  image inputimg = readPPM("/home/yuvraj/Pictures/sedcat.ppm");
  int flipResult = applyFlipping(inputimg);
  if(flipResult != 0)
  {
    fprintf(stderr, "Error applying flipping transformation");
    return 1;
  }
  writePPM(inputimg, "/home/yuvraj/Pictures/bruh.ppm");
  freeimage(inputimg);
  return 0;
}
