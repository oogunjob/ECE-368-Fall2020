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
 
  // argv[1] = encoded file
  
  // argv[2] = output file for tree
  // argv[3] = output file for decoded 
  // argv[4] = output file for count
  // argv[5] = output file for huffman tree
  // argv[6] = output file for evaluation

  // opens input file and stores in HBT file
  HBTFile * HBT = openFile(argv[1]); // loads the information stored in input file into HBT file
  
  // if file is empty, produce empty outputs and return EXIT_SUCCESS
  if(HBT == NULL){
    // opens and closes argv[2]
    FILE * file = fopen(argv[2], "w");
    fclose(file);

    // opens and closes argv[3]
    file = fopen(argv[3], "w");
    fclose(file);

    // opens and closes argv[4]
    file = fopen(argv[4], "w");
    fclose(file);
  
    // opens and closes argv[5]
    file = fopen(argv[5], "w");
    fclose(file);

    // opens and closes argv[6]
    file = fopen(argv[6], "w");
    fclose(file);
    
    return EXIT_SUCCESS;
  }

  // creates output for argv[2]
  FILE * file = fopen(argv[2], "w"); // opens up file to be written to
  printTree(file, HBT -> tree); // prints tree in pre-order traversal to output file
  fclose(file); // closes the file

  // creates output for argv[3]
  file = fopen(argv[1], "rb");
  printEncoded(file, argv[3], HBT); 
  
  // creates output for argv[4]
  file = fopen(argv[3], "rb");
  long * frequencies = printCount(file, argv[4]); 
  fclose(file); // closes the input file
  
  // creates output for argv[5]
  file = fopen(argv[5], "w"); // opens output file to be written to
   
  ListNode * root = NULL; // creates root for what will hold the huffman coding tree
  root = constructHuffmanTree(frequencies, file); // creates the huffman coding tree given the frequencies in argv[3]
  free(frequencies); // frees count of frequencies in ASCII table
  fclose(file); // closes output file

  // creates output for argv[6]
  file = fopen(argv[6], "w");
  fclose(file);
  
  // frees allocated memory used in program
  deleteTree(root -> root);
  deleteTree(HBT -> tree);
  free(root);
  free(HBT); 

  return EXIT_SUCCESS;
}