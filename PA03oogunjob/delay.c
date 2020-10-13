#include <stdio.h>
#include <stdlib.h>
#include "delay.h"

Node *Load_Tree_From_File(char *filename, double *resistance, double *per_unit_length_resistance, double *per_unit_length_capacitance){
  FILE * file = fopen(filename, "r"); // opens input file
  
  // counts how many nodes will be used for the binary tree
  int size = -1; // numbers of nodes in the tree
  char ch; // character variable

  while(!feof(file)){
    ch = fgetc(file);
    if(ch == '\n'){
      size++;
    }
  }

  fseek(file, 0, SEEK_SET); // returns to the top of the file

  // stores the first line's data into the three variables
  fscanf(file, "%le %le %le\n", resistance, per_unit_length_resistance, per_unit_length_capacitance);
  
  // Node * root = constructBST(file, 0, size - 1);
  
  
  
  fclose(file); // closes
  
  return NULL;
}