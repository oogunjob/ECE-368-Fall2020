#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

int main(int argc, char * * argv){ 
  // ensures there are 6 arguments given
  if (argc != 3 || argc != 4) {
    fprintf(stderr, "ERROR: Invalid Number of Arguments.\n");
    return EXIT_FAILURE;
  }

  // building a height-balanced BST
  if((strcmp("-b", argv[1])) == 0){
  
    return EXIT_SUCCESS;
  }


  // evaluation of height-balanced BST
  if((strcmp("-e", argv[1])) == 0){
  

  
  }



  return EXIT_SUCCESS; // exits program 
}
