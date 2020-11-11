#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

typedef struct _HBTFile {
   long encodedSize;
   long topoSize;
   long unencodedSize;
   struct _HBTNode *tree;
   char * encodedText;
} HBTFile;

typedef struct _HBTNode {
  int data;
  int frequency;
  char * character;
  struct _HBTNode *left;
  struct _HBTNode *right;
  struct _HBTNode *next;
} HBTNode;

typedef struct _STACK {
  struct _HBTNode *top;
} STACK;


HBTFile * openFile(char * filename);

HBTNode *top(STACK *stack);
HBTNode * buildTree(int * array, int size);
HBTNode * createNode(int data);

int concat(int a, int b, int c, int d, int e, int f, int g, int h);
int convert_to_decimal(int n);
int * decodeInput(FILE * file, long topoSize);

void loadTree(FILE * file, HBTFile * HBT, long topoSize);
void push(STACK *stack, HBTNode *node);
void printTree(FILE * file, HBTNode* node);
void deleteTree(HBTNode *node);
void openFiles(char * file1, char * file2, char * file3, char * file4, char * file5);

#endif

