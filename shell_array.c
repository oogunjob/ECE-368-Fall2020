#include <stdio.h>
#include <stdlib.h>
#include "shell_array.h"
#include "sequence.h"

long * Array_Load_From_File(char *filename, int *size){

  FILE * file = fopen(filename, "rb"); // opens binary file of numbers to store in array

  // if file is NULL, save size as zero, and return empty array
  if(file == NULL){	
    fprintf(stderr, "ERROR: File is NULL.\n");
    *size = 0;
    return NULL;
  }

  // determines how long the file is
  fseek(file, 0, SEEK_END);
  *size = ftell(file) / sizeof(long) / 2;
  fseek(file, 0, SEEK_SET);

  // creates a temporary array
  long * temp = malloc(sizeof(*temp) * (*size));

  // Stores integers from files into the array
  for(int index = 0; index < *size; index++){
    fread(&temp[index], sizeof(long), 1, file);
  }

  fclose(file); // closes the file
  return temp; // returns the array
}

void Array_Shellsort(long *array, int size, long *n_comp){
  int sequenceSize = 0; // number of elements in the sequence
  long * sequence = Generate_2p3q_Seq(size, &sequenceSize); // computes Pratt's sequence based on the size of the array
  
  // need to add a clause if the sequence is empty or sequenceSize is still 0
  // time to actually sort :/ 


  



  return;
}