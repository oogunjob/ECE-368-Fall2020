#include <stdio.h>
#include <stdlib.h>
#include "hbt.h"

int main(int argc, char * * argv){ 
  // ensures there are 6 arguments given
  if (argc < 6) {
    fprintf(stderr, "ERROR: Number of arguments less than 6.\n");
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS; // exits program 
}
