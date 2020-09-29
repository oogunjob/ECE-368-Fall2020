#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

HBTFile * openFile(char * filename){
  FILE * file = fopen(filename, "rb"); // opens the input file
  HBTFile * head = malloc(sizeof(*head)); // allocates space for HBT file that will hold information

  head -> encodedSize = loadEncodingSize(file);
  head -> topoSize = loadTopoSize(file);
  head -> unencodedSize = loadUnencodedSize(file);
  
  fprintf(stdout, "The number of bytes in the compressed file: %ld\n", head -> encodedSize);
  fprintf(stdout, "The number of bytes in the topology of the coding tree in compressed file: %ld\n", head -> topoSize);
  fprintf(stdout, "The number of bytes in the original uncompressed file: %ld\n", head -> unencodedSize);

  fclose(file); // closes file
  return head;  
}

long loadEncodingSize(FILE * file){
  long value; // the number of bytes in the compressed file
  fread(&value, sizeof(long), 1, file); // loads value from file

  return value; // returns the value
}

long loadTopoSize(FILE * file){
  long value; // the number of bytes storing the topology of the Huffman coding tree
  fread(&value, sizeof(long), 1, file); // loads value from file

  return value; // returns the value
}

long loadUnencodedSize(FILE * file){
  long value; // the number of bytes in the original uncompressed file
  fread(&value, sizeof(long), 1, file); // loads value from file

  return value; // returns the value
}



