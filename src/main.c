#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "matrix.h"
#include "matrixmath.h"
#include "transformations.h"
#include "ppm.h"


char *concatenate(char*inppath)
{
  int len1 = strlen(inppath);
  char *result = (char*)malloc(sizeof(char)*(len1+4));
  int flag = 0;
  int idx = len1+3;
  for(int i = len1; i>=0; i--)
  {
    if(i == 0 && flag == 0)
    {
      fprintf(stderr, "Invalid file path. Pls ensure .ppm extension\n");
      exit(1);
    }
    if(inppath[i] == '.' && flag == 0)
    {
      flag = 1;
      result[idx--] = '.';
      result[idx--] = 't';
      result[idx--] = 'u';
      result[idx--] = 'O';
    }
    else
      result[idx--] = inppath[i];
  }
  result[len1+3] = '\0';
  return result;
}

int main(int argc, char* argv[])
{
  if(argc <= 1)
  {
    fprintf(stderr, "Invalid arguments\n");
  }

  int inputType = atoi(argv[2]);
  for(int i = 3; i<argc-(inputType-1); i+=inputType)
  {
    char *inputpath = argv[i];
    char *outputpath;
    if(inputType == 2)
    {
      outputpath = argv[i+1];
    }
    else if(inputType == 1)
    {
      outputpath = concatenate(inputpath);
    }
    else
    {
      fprintf(stderr, "Invalid args\n");
      return 1;
    }
    image inputimg = readPPM(inputpath);
    if(atoi(argv[1]) <= 1)
    {
      int flipResult = applyFlipping(inputimg);
      if(flipResult != 0)
      {
	fprintf(stderr, "Error applying flipping transformation");
	return 1;
      }
    }

    if(atoi(argv[1])%2 == 0)
    {
      int blurResult = applyBlur(inputimg);
      if(blurResult != 0)
      {
	fprintf(stderr, "Error applying blur transformation");
	return 1;
      }
    }
  
      writePPM(inputimg, outputpath);
      freeimage(inputimg);
    }

  return 0;
}
