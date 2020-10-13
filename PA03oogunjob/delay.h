#ifndef __DELAY_H__
#define __DELAY_H__

typedef struct _Node {
   int sink;
   double resistance;
   double capacitance;
   double delay;
   struct _Node *left;
   struct _Node *right;
} Node;

Node *Load_Tree_From_File(char * filename, double * resistance, double * per_unit_length_resistance, double * per_unit_length_capacitance);

#endif

