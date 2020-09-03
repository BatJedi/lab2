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

void errmessage(char *);
image readPPM(char *);
int writePPM(image, char *);
void freeimage(image);

#endif
