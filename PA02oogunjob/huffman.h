#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

typedef struct _HBTFile {
   long encodedSize;
   long topoSize;
   long unencodedSize;
   struct _HBTTree *tree;
   char * encodedText;
} HBTFile;

typedef struct _HBTTree {
  int data;
  int frequency;
  char * character;
  struct _HBTTree *left;
  struct _HBTTree *right;
} HBTTree;

HBTFile * openFile(char * filename);
long loadEncodingSize(FILE * file);
long loadTopoSize(FILE * file);
long loadUnencodedSize(FILE * file);
void loadTree(FILE * file);
void openFiles(char * file1, char * file2, char * file3, char * file4, char * file5);

#endif

