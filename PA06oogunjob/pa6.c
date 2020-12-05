#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pa6.h"

int main(int argc, char * * argv){ 
  
  // finding stricly longest sequence mode
  if((strcmp("-s", argv[1])) == 0){
  
    int sequence = findSequence(argv[2], argv[3], argv[4]);
    
    if(sequence < 1){
      fprintf(stderr, "ERROR: Failure occured during opening of files.\n");
      return EXIT_FAILURE;
    }

    return EXIT_SUCCESS; // returns EXIT_SUCCESS
  }
    
  //  Evaluating strictly increasing sequence
  else if((strcmp("-e", argv[1])) == 0){
    
    // ./pa6 -e binary table file sequence file
    
    // produces the following output "%d,%d,%d,%d\n", where the first integer
    // first integer - indicates the validity of the binary table file
    // second integer - indicates the validity of the sequence file
    
    // third integer - indicates whether the sequence file corresponds to a strictly increasing sequence
    // fourth integer - indicates whether the sequence corresponds to a maximal strictly increasing sequence

    // FIRST INTEGER
    // If the binary table file cannot be opened, the first integer should be -1. 
    // If it can be opened, but of the wrong format, the first integer should be 0
    // If it can be opened and is of the correct format, the first integer should be 1

    // SECOND INTEGER
    // If the sequence file cannot be opened, the second integer should be -1. 
    // If it can be opened, but of the wrong format, the second integer should be 0. 
    // If it can be opened and is of the correct format, the second integer should be 1. 
    
    // THIRD INTEGER
    // If the sequence file corresponds to a strictly increasing sequence, the third integer is 1
    // otherwise, it is 0.

    // FOURTH INTEGER
    // If the sequence file corresponds to a maximal strictly increasing sequence, the fourth integer is 1
    // otherwise, it is 0.

    int evaluation = Evaluate(argv[2], argv[3]);

    // if the evaluation isn't equal to 1, return EXIT_FAILURE
    if(evaluation < 1){
      fprintf(stderr, "ERROR: Failure occured during opening of files.\n");
      return EXIT_FAILURE;
    }
    return EXIT_SUCCESS; // returns EXIT_SUCCESS
  }

  else{
    fprintf(stderr, "ERROR: Invalid argv[1] argument passed.\n");
    return EXIT_FAILURE;
  }
}
