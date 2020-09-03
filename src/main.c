#include <stdio.h>
#include <stdlib.h>
#include "matrix.h"
#include "matrixmath.h"
#include "transformations.h"
#include "ppm.h"


int main()
{
  image inputimg = readPPM("/home/yuvraj/Pictures/pulse.ppm");
  int flipResult = applyFlipping(inputimg);
  if(flipResult != 0)
  {
    fprintf(stderr, "Error applying flipping transformation");
    return 1;
  }
  int blurResult = applyBlur(inputimg);
  if(blurResult != 0)
  {
    fprintf(stderr, "Error applying blur transformation");
    return 1;
  }
  
  writePPM(inputimg, "/home/yuvraj/Pictures/bruh.ppm");
  freeimage(inputimg);
  return 0;
}
