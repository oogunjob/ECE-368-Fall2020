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

int concatenate(int a, int b, int c, int d, int e, int f, int g, int h);
int convert2decimal(int num);
int * decodeInput(FILE * file, long topoSize);
int isLeafNode(HBTNode * node);

void loadTree(FILE * file, HBTFile * HBT, long topoSize);
void push(STACK *stack, HBTNode *node);
void deleteTree(HBTNode *node);

void printTree(FILE * file, HBTNode* node);
void printEncoded(FILE * file, char * filename, HBTFile * HBT);
void printCount(FILE * input, char * filename);

#endif

