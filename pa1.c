#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_array.h"
#include "shell_list.h"

int main(int argc, char * * argv) { 
  
  // ensures there are 4 arguments given ***
  if (argc < 3) {
    fprintf(stderr, "ERROR: Arguments less than 4.\n");
    return EXIT_FAILURE;
  }

  // runs shell sort for array
  if((strcmp("-a", argv[1])) == 0){
    int size = 0; // number of elements in the array
    long n_comp = 0; // number of comparisons counted
	  int elements; // number of elements written to the file

	  long * array = Array_Load_From_File(argv[2], &size); // loads the array from the file
    
	  // if the file could not be read return exit failure
	  if(array == NULL){
      fprintf(stderr, "ERROR: Array is NULL.\n");
	    return EXIT_FAILURE; 
	  }
	
    Array_Shellsort(array, size, &n_comp); // performs shell sort on the array and calcuates number of comparisons made
	
//     elements = Array_Save_To_File(argv[3], array, size); // saves the elemments the file and returns the number of elements printed
	
// 	// if no elements are saved to the file, return EXIT_FAILURE
// 	if(elements == NULL)
// 	{
// 	  free(array); // frees memory allocated for the array
// 	  return EXIT_FAILURE; 
// 	}

// 	free(array); // frees memory allocated for the array
  }

  return EXIT_SUCCESS; // return EXIT_SUCCESS is program is successful
}