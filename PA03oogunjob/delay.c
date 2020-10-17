#include <stdio.h>
#include <stdlib.h>
#include "delay.h"

Node *Load_Tree_From_File(char *filename, double *resistance, double *per_unit_length_resistance, double *per_unit_length_capacitance){
  FILE * file = fopen(filename, "r"); // opens input file

  // stores the first line's data into the three variables
  fscanf(file, "%le %le %le\n", resistance, per_unit_length_resistance, per_unit_length_capacitance);
  
  char line[100]; // individual line read from the file
  
  int label; // label of the wire
  double capacitance; // capacitance of the wire
  
  double leftLength; // length from left wire to parent node
  double rightLength; // length from right wire to parent node

  Stack * stack = malloc(sizeof(*stack)); // creates stack

  while(fgets(line, sizeof(line), file)){
    if(line[0] != '('){
      sscanf(line, "%d(%le)\n", &label, &capacitance); // reads the sink and capacitance of the node
      
      // creates leaf node with sink and capacitance
      Node * leafNode = malloc(sizeof(*leafNode));
      leafNode -> label = label;
      leafNode -> sink = capacitance;

      // assigns NULL pointers to left and right nodes of current node
      leafNode -> left = NULL;
      leafNode -> right = NULL;
    
      push(stack, leafNode); // pushes node to the stack
    }
    else{
      // creates non-leaf wire node
      Node * nonLeafNode = malloc(sizeof(*nonLeafNode));
      nonLeafNode -> label = -1;
      nonLeafNode -> sink = 0;

      // scans in lengths of left and right node
      sscanf(line, "(%le %le)\n", &leftLength, &rightLength); 

      // pulls right node for parent node from stack and assigns legnth
      nonLeafNode -> right = top(stack);
      nonLeafNode -> right -> length = rightLength;

      // pulls left node for parent node from stack and assigns legnth
      nonLeafNode -> left = top(stack);
      nonLeafNode -> left -> length = leftLength;

      // pushes tree to the stack
      push(stack, nonLeafNode); 
    }
  }

  fclose(file); // closes file
  
  // stores the top of the stack in root node and frees allocated memory of the stack
  Node * root = stack -> top;
  free(stack);

  return root; // returns the root of the binary tree
}

void push(Stack *stack, Node *node){
  // if the stack is empty, push the node to the top of the stack
  if(stack == NULL){
    stack -> top = node;
    stack -> top -> next = NULL;
    return;
  }

  Node * temp = stack -> top; // temporary node is the current top of the stack
  stack -> top = node; // new top of the stack is the new node
  stack -> top -> next = temp; // the node after top is the previous top
  return;
}

Node *top(Stack *stack){
  Node * current = stack -> top; // assigns top of stack as current node
  stack -> top = stack -> top -> next; // new top becomes the node after previous top
  
  return current; // returns the previous top node
}

void Print_Pre_Order_Tree(FILE *file, Node *node){ 
  if (node == NULL){ 
    return; 
  }
  
  // traverses the right of the subtree
  if(node -> label == -1){
    fprintf(file, "(%le %le)\n", node -> left -> length, node -> right -> length);
  }
  else{
    fprintf(file, "%d(%le)\n", node -> label, node -> sink);   
  }

  // traverses the right of the subtree
  Print_Pre_Order_Tree(file, node -> left);   
  
  // traverses the right of the subtree
  Print_Pre_Order_Tree(file, node -> right); 

  return;
}     

void Compute_Resistance_Capacitance(char *filename, Node *root, double sourceResistance, double resistance, double capacitance){
  FILE * file = fopen(filename, "wb");
  
  root -> length = 0; // assigns the length of the root node as 0
  
  computeResistance(root, sourceResistance, resistance); // computes the resistance of each node in the binary tree
  computeCapacitance(root, capacitance); // computes the capacitance of each node in the binary tree

  Print_Resistance_Capacitance(file, root); // prints the resistance and capacitance to the output file
  
  fclose(file); // closes the file

  return;
}

void computeResistance(Node *node, double sourceResistance, double resistance){ 
  if (node == NULL){ 
    return; 
  }

  // assigns the resistance to the root of the binary tree
  if(node -> length == 0){
    node -> resistance = sourceResistance;
  }
  // computes the resistance of the individual node
  else{
  node -> resistance = (resistance) * (node -> length); 
  }

  // traverses the right of the subtree
  computeResistance(node -> left, sourceResistance, resistance);   
  
  // traverses the right of the subtree
  computeResistance(node -> right, sourceResistance, resistance); 

  return;
}    

void computeCapacitance(Node *node, double capacitance){ 
  if (node == NULL){ 
    return; 
  }
  
  if(node -> label != -1){
    // computes the capacitance of the individual leaf node
    node -> capacitance = ((capacitance) * (node -> length) / 2) + (node -> sink);
  }
  
  else{
    // computes the capacitance of the individual non-leaf node
    double leftCapacitance = (node -> left -> length) * (capacitance) / 2; // capacitance of the left node
    double rightCapacitance = (node -> right -> length) * (capacitance) / 2; // capacitance of the right node

    node -> capacitance = leftCapacitance + rightCapacitance + (node -> length * capacitance / 2); // computes the capacitance of the node
  }

  // traverses the right of the subtree
  computeCapacitance(node -> left, capacitance);   
  
  // traverses the right of the subtree
  computeCapacitance(node -> right, capacitance); 

  return;
}  

void Print_Resistance_Capacitance(FILE * file, Node * node){
  if(node == NULL){ 
    return; 
  }

  // prints the node's information
  fwrite(&(node -> label), sizeof(int), 1, file);
  fwrite(&(node -> resistance), sizeof(double), 1, file);
  fwrite(&(node -> capacitance), sizeof(double), 1, file);

  // traverses the right of the subtree
  Print_Resistance_Capacitance(file, node -> left);   
  
  // traverses the right of the subtree
  Print_Resistance_Capacitance(file, node -> right); 

  return;
}

double Compute_Total_Capacitance(Node *node){
  if(node == NULL){
    return 0;
  }
  
  // computes the capacitance of each sub tree
  double sum = node -> capacitance + Compute_Total_Capacitance(node -> left) + Compute_Total_Capacitance(node -> right);
  
  node -> totalCapacitance = sum; // stores the total capacitance of the sub-tree in the specific node

  return sum; // returns the current to the calling function
}

void Print_Total_Capacitance(FILE * file, Node * node){
  if(node == NULL){ 
    return; 
  }

  // prints the node's information
  fwrite(&(node -> label), sizeof(int), 1, file);
  fwrite(&(node -> totalCapacitance), sizeof(double), 1, file);

  // traverses the right of the subtree
  Print_Total_Capacitance(file, node -> left);   
  
  // traverses the right of the subtree
  Print_Total_Capacitance(file, node -> right); 

  return;
}

void deleteTree(Node *node)  { 
  // if node is empty, do nothing
  if(node == NULL){
    return;
  }

  deleteTree(node -> left); // traverses left side of the node
  deleteTree(node -> right); // traverses right side of the node
  
  free(node); // free the allocated memory of the node
  
  return;
}
  // tree is given in POST ORDER format
  // leaf node (which is a sink), printed with the format "%d(%le)\n 
  // integer represents the label of the sink, double represents the node capacitance

  // non-leaf node, printed with the format "(%le %le)\n", 
  // where the first double is the wire length to the left child, second double is the wire length to the right child