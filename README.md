matrix.h : Contains declaration for matrix struct
matrixmatch.h : Header file with declarations for matrixmatch.c
transformations.h : Header file with declarations for transformations.c

main.c : main file that will contain the code for running both transformations or just one of them based on command line arguments. Currently it only
contains code for testing the flipping transformation I made.
matrix.c : defines a few important functions such as allocating space to the 3 matrices in matrix struct and also for freeing those matrices
matrixmath.c : contains multiply function and a function that returns a flipped identity matrix of size taken as input
transformations.c : this file should contain the functions for applying the transformations. Currently contains the function for flipping transformation.

To Add: 
ppm.c : source code for the library that will contain the functions for reading from and writing to ppm files
ppmh : header file for ppm.c
