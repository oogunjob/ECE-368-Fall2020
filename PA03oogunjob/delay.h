#ifndef __DELAY_H__
#define __DELAY_H__

typedef struct _Node {
   int label;
   double sink;
   double resistance;
   double capacitance;
   
   double totalCapacitance;
   double totalResistance;

   double length;
   double delay;

   int isRoot;
   
   struct _Node *left;
   struct _Node *right;
   struct _Node *next;
} Node;

typedef struct _Stack {
  struct _Node *top;
} Stack;

Node *Load_Tree_From_File(FILE *file, double *resistance, double *per_unit_length_resistance, double *per_unit_length_capacitance);
Node *top(Stack *stack);

void push(Stack *stack, Node *node);
void Compute_Resistance_Capacitance(char *filename, Node *root, double sourceResistance, double resistance, double capacitance);
void computeResistance(Node *node, double sourceResistance, double resistance);
void computeCapacitance(Node *node, double capacitance);
void Compute_Delay(Node *node, double sourceResistance, double previousDelay);

double Compute_Root_Delay(Node *node, double resistance);
double Compute_Total_Capacitance(Node *node);

void Print_Pre_Order_Tree(FILE *file, Node *node);
void Print_In_Order_Tree(FILE *file, Node *node);
void Print_Resistance_Capacitance(FILE * file, Node *node);
void Print_Total_Capacitance(FILE * file, Node * node);

void deleteTree(Node *root);

#endif
