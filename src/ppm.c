#include "matrix.h"
#include "ppm.h"
#include "stdlib.h"
#include <stdio.h>
#include <stdlib.h>

void errmessage(char *error)
{
  fprintf(stderr, "%s\n", error);
  exit(1);
}

image readPPM(char *inputpath)
{
  image readimg = (image)malloc(sizeof(struct image));
  FILE *fp = fopen(inputpath, "r");
  if(!readimg) errmessage("Memory allocation error. Aborting");
  if(!fp) errmessage("Can't open image file for reading. Aborting.");

  //read magic number
  char ch;
  if(fscanf(fp, "P%c\n", &ch) != 1 || ch!='6') errmessage("Incorrect format of ppm file. Aborting.");
  
  //ignore comments in ppm file
  ch = getc(fp);
  while(ch == '#')
  {
    ch = getc(fp);
    while(ch != '\n')
      ch = getc(fp);
    ch = getc(fp);
  }
  if(!(ch >= '0' && ch<= '9'))
  {
    errmessage("ppm file format error");
  }

  //put back character as it is part of width
  ungetc(ch, fp);

  //read width and height
  int width, height;
  fscanf(fp, "%d%d%d\n", &width, &height, &(readimg->maxval));
  if(width <= 0 || height <= 0) errmessage("Empty image error. Aborting.");
  if(readimg->maxval > 255) errmessage("PPM color format error. Aborting.");
  readimg->width = width;
  readimg->height = height;
  readimg->img = creatematrix(height, width);
  
  //read the matrix now
  int size = (readimg->height)*(readimg->width);
  int readCount = 0;
  unsigned char ch1, ch2, ch3;
  while(readCount < size)
  {
    int rowIndex = readCount/width;
    int colIndex = readCount % width;
    fscanf(fp, "%c%c%c", &ch1, &ch2, &ch3);
    readimg->img->R[rowIndex][colIndex] = ch1;
    readimg->img->G[rowIndex][colIndex] = ch2;
    readimg->img->B[rowIndex][colIndex] = ch3;
    readCount++;
  }
  if(readCount != size) errmessage("Image read error");
  
  fclose(fp);
  return readimg;
}

int writePPM(image writeimg, char *outputpath)
{
  FILE *fp = fopen(outputpath, "w");
  if(!fp) errmessage("Output file couldn't be opened for writing. Aborting.");

  fprintf(fp, "P6\n%d %d\n%d\n", writeimg->width, writeimg->height, writeimg->maxval);

  int size = (writeimg->height)*(writeimg->width);
  int writeCount = 0;
  unsigned char ch1, ch2, ch3;
  
  while(writeCount < size)
  {
    int rowIndex = writeCount/writeimg->width;
    int colIndex = writeCount % writeimg->width;
    ch1 = writeimg->img->R[rowIndex][colIndex];
    ch2 = writeimg->img->G[rowIndex][colIndex];
    ch3 = writeimg->img->B[rowIndex][colIndex];
      fprintf(fp, "%c%c%c", ch1, ch2, ch3);
    writeCount++;
  }
  if(writeCount != size)
  {
    return 1;
  }
  fclose(fp);
  return 0;
}

void freeimage(image toFree)
{
  if(!toFree)
  {
    errmessage("Couldn't free image");
    return;
  }
  if(toFree->img != NULL)
    freematrix(toFree->img);
  free(toFree);
  return;
}
