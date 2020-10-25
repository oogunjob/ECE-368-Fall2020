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
    
      leafNode -> isRoot = 0; // identifies that the node is not the root of the tree

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

      nonLeafNode -> isRoot = 0; // identifies that the node is not the root of the tree

      // pushes tree to the stack
      push(stack, nonLeafNode); 
    }
  }

  fclose(file); // closes file
  
  // stores the top of the stack in root node and frees allocated memory of the stack
  Node * root = stack -> top;
  root -> isRoot = 1; // identifies that the node is the root of the tree

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
  
  // prints node
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

double Compute_Root_Delay(Node *node, double resistance){ 
  if(node == NULL){ 
    return 0; 
  }
  
  double timeConstant = node -> capacitance * (resistance * resistance); // computes time constant of the node
  return timeConstant + Compute_Root_Delay(node -> left, resistance) + Compute_Root_Delay(node -> right, resistance); // returns summation of time constant of every node in binary tree
}

void Compute_Delay(Node *node, double resistance, double previousDelay){
  if(node == NULL){
    return;
  }

  // if it is the root of the tree, perform the traversal of both sides of the tree
  if(node -> isRoot == 1){
    Compute_Delay(node -> left, resistance, node -> delay);
    Compute_Delay(node -> right, resistance, node -> delay);

    return;
  }

  if(node -> label == -1){
    double delay; // delay of the node
    double totalCapacitance = node -> totalCapacitance; // total capacitance of the sub-tree

    delay = previousDelay - (totalCapacitance * resistance * resistance) + ((totalCapacitance) * ((resistance + node -> resistance) * (resistance + node -> resistance)));
    node -> delay = delay; // assigns the delay to the node

    Compute_Delay(node -> left, resistance + node -> resistance, node -> delay);
    Compute_Delay(node -> right, resistance + node -> resistance, node -> delay);
  }


  else if(node -> label != -1){
    double delay; // delay of the node
    double capacitance = node -> capacitance; // capacitance of the node

    delay = previousDelay - capacitance * (resistance * resistance) + capacitance * ((resistance + node -> resistance) * (resistance + node -> resistance));
    
    delay = (1 / (resistance + node -> resistance)) * delay; // computes the delay
    node -> delay = delay; // assigns the delay to the node
  }

  return;
}

void Print_In_Order_Tree(FILE *file, Node *node){ 
  if (node == NULL){ 
    return; 
  }

  // traverses the right of the subtree
  Print_In_Order_Tree(file, node -> left);   

  // prints node's delay value
  if(node -> label != -1){
    fwrite(&(node -> label), sizeof(int), 1, file);
    fprintf(stdout, "%d", node -> label);
    
    fwrite(&(node -> delay), sizeof(double), 1, file);
    fprintf(stdout, "(%le)\n", node -> delay);
  }

  // traverses the right of the subtree
  Print_In_Order_Tree(file, node -> right); 

  return;
}

void deleteTree(Node *node){ 
  // if node is empty, do nothing
  if(node == NULL){
    return;
  }

  deleteTree(node -> left); // traverses left side of the node
  deleteTree(node -> right); // traverses right side of the node
  
  free(node); // free the allocated memory of the node
  
  return;
}