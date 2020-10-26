#include <stdio.h>
#include <stdlib.h>
#include "delay.h"

int main(int argc, char * * argv){ 
  // ensures there are 6 arguments given
  if (argc < 6) {
    fprintf(stderr, "ERROR: Invalid number of arguments.\n");
    return EXIT_FAILURE;
  }
  
  double resistance; // the output resistance (Ω)
  double per_unit_length_resistance; // per unit length resistance of a wire (Ω/unit-length))
  double per_unit_length_capacitance; // per unit length capacitance (c)
  
  // loads the root of the tree from the file
  FILE * file = fopen(argv[1], "r");
  // checks if the file can be successfully opened
  if(file == NULL){
    fprintf(stderr, "ERROR: The file could not be opened.\n");
    return EXIT_FAILURE;
  }

  Node * root = Load_Tree_From_File(file, &resistance, &per_unit_length_resistance, &per_unit_length_capacitance);
  
  file = fopen(argv[2], "w"); // opens first output file

  Print_Pre_Order_Tree(file, root); // prints the pre-order traversal of the tree
  fclose(file); // closes the first output file
  
  // prints the resistance and capacitance of each node to the given output file
  Compute_Resistance_Capacitance(argv[3], root, resistance, per_unit_length_resistance, per_unit_length_capacitance);
  

  // prints the total capacitance of each sub-tree in the binary tree
  if(root != NULL){
    root -> totalCapacitance = Compute_Total_Capacitance(root); // computes the total capacitance of each subtree in the binary tree
  }

  file = fopen(argv[4], "wb");
  Print_Total_Capacitance(file, root); // prints the total capacitance values to the output file
  fclose(file); // closes third output file

  // prints the delay of each node to the file
  if(root != NULL){
    root -> delay = (1 / root -> resistance) * Compute_Root_Delay(root, root -> resistance);
    Compute_Delay(root, root -> resistance, root -> delay);
  }

  file = fopen(argv[5], "wb");
  Print_In_Order_Tree(file, root);
  fclose(file);

  deleteTree(root); // deletes the binary search tree

  return EXIT_SUCCESS; // exits program 
}
