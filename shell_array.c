#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

long * Array_Load_From_File(char *filename, int *size)
{
  FILE * file = fopen(filename, "rb"); // opens binary file of numbers for array

  // if file is NULL, save size as zero, and return empty array
  if(file == NULL)
  {	
    *size = 0;
    return NULL;
  }

  // Determine how the file is going to be
  fseek(file, 0, SEEK_END);
  *size = ftell(file) / sizeof(long);
  fseek(file, 0, SEEK_SET);

  // Creates temporary array
  long * temp = malloc(sizeof(*temp), *size);

  // Stores integers from files into the array
  for(int i = 0; i < *size; i++)
  {
    fread(&temp[i], sizeof(long), 1, file);
  }

  fclose(file); // closes the file

  return temp; // returns the array
}