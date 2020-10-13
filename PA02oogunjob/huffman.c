#include <stdio.h>
#include <stdlib.h>
#include "huffman.h"

HBTFile * openFile(char * filename){
  FILE * file = fopen(filename, "rb"); // opens the input file
  HBTFile * head = malloc(sizeof(*head)); // allocates space for HBT file that will hold information

  head -> encodedSize = loadEncodingSize(file); // loads encoded bytes size
  head -> topoSize = loadTopoSize(file); // loads topology bytes size 
  head -> unencodedSize = loadUnencodedSize(file); // loads unencoded bytes sizez

  loadTree(file);

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

void loadTree(FILE * file){
  
  char character;
  unsigned char * array = malloc(sizeof(char) * 10);

  fread(array, sizeof(char), 10, file);

  for (int i = 0; i < 10; i++) {
    fprintf(stdout, "%u\n", array[i]);
  }
  
  unsigned char * char_arr = malloc(sizeof(char)*80);

  int j = 0;

  while (j < 80) {
    unsigned char byte[8];
    unsigned char bits = array[j/8];

    for (int c = 0; c < 8; c++){
      byte[c] = (bits & (1 << (7-c))) ? '1' : '0';
    }

    for(int k = 0; k < 8; k++, j++){
      char_arr[j] = byte[7-k];
    }
  }

  for (int c = 0; c < 80; c++){
    if (c%8 == 0) {
      printf("\n");
    }
    printf("%c", char_arr[c]);
  }

/*
               0
              /
            0
           / \
          g   o                            

  */

  return;
}

void openFiles(char * file1, char * file2, char * file3, char * file4, char * file5){
  
  // opens files
  FILE * file_1 = fopen(file1, "w");
  FILE * file_2 = fopen(file2, "w");
  FILE * file_3 = fopen(file3, "w");
  FILE * file_4 = fopen(file4, "w");
  FILE * file_5 = fopen(file5, "w");

  // closes files
  fclose(file_1);
  fclose(file_2);
  fclose(file_3);
  fclose(file_4);
  fclose(file_5);

  return;
}
