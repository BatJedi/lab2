#ifndef PPM
#define PPM
#include "matrix.h"

struct image
{
  unsigned int height, width;
  int maxval;
  matrix img;
};

typedef struct image* image;

image readPPM(char *);
int writePPM(image);

#endif
