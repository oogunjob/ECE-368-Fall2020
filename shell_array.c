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
    fclose(file);
    return NULL;
  }

  // determines how long the file is
  fseek(file, 0, SEEK_END);
  *size = ftell(file) / sizeof(long);
  fseek(file, 0, SEEK_SET);

  // creates a temporary array
  long * temp = malloc(sizeof(*temp) * (*size));

  // stores integers from files into the array
  for(int index = 0; index < *size; index++){
    fread(&temp[index], sizeof(long), 1, file);
  }

  fclose(file); // closes the file
  return temp; // returns the array
}

void Array_Shellsort(long *array, int size, long *n_comp){
  int sequenceSize = 0; // number of elements in the sequence
  long *sequence = Generate_2p3q_Seq(size, &sequenceSize); // Pratt's sequence based on the size of the array

  // if the array or sequence is empty, return to main function
  if(size == 0 || sequenceSize == 0){
    return;
  }

  int count = 1; // loop control variable that determines value of k
  int k; // sequence control variable
  int i; // loop control variable for comparison
  long temp; // temporary number
  
  // shell sort implementation
  for(count = (sequenceSize - 1); count >= 0; count--){
    k = sequence[count]; // selects the value of k from sequence array
  
    for(int j = k; j <= (size - 1); j++){
      temp = array[j];
      i = j;

      while(i >= k && array[i - k] > temp){
        *n_comp += 1; // increments the number of comparisons made
        array[i] = array[i - k];
        i = i - k;
      }
      array[i] = temp;
    }
  }

  free(sequence); // frees the sequence array
  return;
}

int Array_Save_To_File(char *filename, long *array, int size){
  FILE * file = fopen(filename, "wb"); // opens binary file that will be written to

  // if the array is empty, closes the file and returns a count of no elements written
  if(array == NULL || size == 0){
    fclose(file); // closes file
	  return 0;
  }

  // writes elements of array to file
  int elements = 0; // number of elements written to the file
  int index; // index of elements in array

  for(index = 0; index < size; index++){	
    fwrite(&array[index], sizeof(long), 1, file);
	  elements++; 
  }
	
  fclose(file); // closes the file

  return elements; 
}