#ifndef __DELAY_H__
#define __DELAY_H__

typedef struct _Node {
   int label;
   double sink;
   double resistance;
   double capacitance;
   double length;
   double delay;
   
   struct _Node *left;
   struct _Node *right;
   struct _Node *next;
} Node;

typedef struct _Stack {
  struct _Node *top;
} Stack;

Node *Load_Tree_From_File(char *filename, double *resistance, double *per_unit_length_resistance, double *per_unit_length_capacitance);
Node *top(Stack *stack);

void push(Stack *stack, Node *node);
void Print_Pre_Order_Tree(FILE *file, Node *node);
void Compute_Resistance_Capacitance(char *filename, Node *root, double sourceResistance, double resistance, double capacitance);
void Print_Resistance_Capacitance(Node *node);
void computeResistance(Node *node, double sourceResistance, double resistance);
void computeCapacitance(Node *node, double capacitance);
void deleteTree(Node *root);

#endif