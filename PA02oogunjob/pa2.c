#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

int main(int argc, char ** argv){
  // ensures there are 7 arguments given
  if (argc < 7) {
    fprintf(stderr, "ERROR: Number of arguments less than 7.\n");
    return EXIT_FAILURE;
  }
  
  // argv[0] = executable file
  // argv[1] = encoded input file
  
  // argv[2] = output file for the tree
  // argv[3] = output file for original 
  // argv[4] = output file for count
  // argv[5] = output file for huffman tree
  // argv[6] = output file for decoded file

  HBTFile * HBT = openFile(argv[1]); // loads the information stored in input file into HBT file
  
  FILE * file = fopen(argv[2], "w"); // opens up file to be written to
  printTree(file, HBT -> tree); // prints tree

  deleteTree(HBT -> tree);
  free(HBT); // frees the HBT File

  return EXIT_SUCCESS;
}