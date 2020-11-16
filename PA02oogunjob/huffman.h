#ifndef __HUFFMAN_H__
#define __HUFFMAN_H__

typedef struct _HBTFile {
   long encodedSize;
   long topoSize;
   long unencodedSize;
   struct _HBTNode *tree;
} HBTFile;

typedef struct _HBTNode {
  int data;
  long frequency;
  struct _HBTNode *left;
  struct _HBTNode *right;
  struct _HBTNode *next;
} HBTNode;

typedef struct _ListNode {
  struct _HBTNode * root;
  struct _ListNode * next;
} ListNode;

typedef struct _STACK {
  struct _HBTNode *top;
} STACK;

HBTFile * openFile(char * filename);

HBTNode *top(STACK *stack);
HBTNode * buildTree(int * array, int size);
HBTNode * createNode(int data);
HBTNode * makeHBTNode(int data, int frequency);

ListNode * constructHuffmanTree(long * frequencies, FILE * file);
ListNode * makeListNode(HBTNode * temp);
ListNode * insert(ListNode * head, ListNode * list);

int concatenate(int a, int b, int c, int d, int e, int f, int g, int h);
int convert2decimal(int num);
int * decodeInput(FILE * file, long topoSize);
int isLeafNode(HBTNode * node);

void loadTree(FILE * file, HBTFile * HBT, long topoSize);
void push(STACK *stack, HBTNode *node);
void deleteTree(HBTNode *node);

void printTree(FILE * file, HBTNode* node);
void printEncoded(FILE * file, char * filename, HBTFile * HBT);
long * printCount(FILE * input, char * filename);

#endif

