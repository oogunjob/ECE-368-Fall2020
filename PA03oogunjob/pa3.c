#include <stdio.h>
#include <stdlib.h>
#include "delay.h"

int main(int argc, char * * argv){ 
  // ensures there are 6 arguments given
  if (argc < 6) {
    fprintf(stderr, "ERROR: Number of arguments less than 6.\n");
    return EXIT_FAILURE;
  }

  double resistance; // the output resistance (Ω)
  double per_unit_length_resistance; // per unit length resistance of a wire (Ω/unit-length))
  double per_unit_length_capacitance; // per unit length capacitance (c)
  
  // loads the root of the tree from the file
  Node *root = Load_Tree_From_File(argv[1], &resistance, &per_unit_length_resistance, &per_unit_length_capacitance);
  
  return EXIT_SUCCESS; // exits program 
}
