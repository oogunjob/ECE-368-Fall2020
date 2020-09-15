#include <stdio.h>
#include <stdlib.h>
#include "sequence.h"

static void bubblesort(long * array, long size);
static void swap(long * x, long * y);

long *Generate_2p3q_Seq(int length, int *seq_size){
  // if length contains 0 or 1 elements, returns a size of 0 and empty sequence
  if(length < 2){
    return NULL;
  }

  long * sequence = malloc(sizeof(*sequence) * ++(*seq_size)); // array that stores the sequence of powers
  
  // if malloc fails, returns NULL, and stores 0 in seq_size
  if(sequence == NULL){
    *seq_size = 0;
    return NULL;
  }

  long power_q = 1; // power that corresponds to q
  long power_p; // power that corresponds to p
  int index = 0; // index of elements in the array

  // computes powers for Pratt's sequence array
  while(power_q < length){
    power_p = power_q;

    while(power_p < length){
      sequence[index++] = power_p; // appends the current power to the array
      sequence = realloc(sequence, sizeof(*sequence) * ++(*seq_size));
      power_p = power_p * 2;
    }
    power_q = power_q * 3;
  }

  *seq_size = *seq_size - 1; // removes extra value from sequence size
  sequence = realloc(sequence, sizeof(*sequence) * (*seq_size)); // resizes the sequence array
  
  bubblesort(sequence, *seq_size); // sorts the sequence array in ascending order *** QuickSort ? ***

  return sequence; // returns the sequence array
}

static void bubblesort(long * array, long size){
  int i; // loop control variable
  int j; // loop control variable
 
  for (i = 0; i < size - 1; i++){       
    for (j = 0; j < size - i - 1; j++)  
      if (array[j] > array[j + 1])  
        swap(&array[j], &array[j + 1]);
  }
}

static void swap(long * x, long * y){
  int temp = *x;  
  // swaps places of x and y
  *x = *y;  
  *y = temp; 
}
