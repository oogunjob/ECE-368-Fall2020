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
  long data;
  struct _HBTTree *left;
  struct _HBTTree *right;
} HBTTree;

HBTFile * openFile(char * filename);
long loadEncodingSize(FILE * file);
long loadTopoSize(FILE * file);
long loadUnencodedSize(FILE * file);

#endif

