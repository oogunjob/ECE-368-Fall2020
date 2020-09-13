#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// #include <time.h>
#include "shell_list.h"
#include "shell_array.h"

int main(int argc, char * * argv) { 
  // calculates the time taken by program
  // clock_t t; 
  // t = clock(); 

  // ensures there are 4 arguments given
  if (argc < 4) {
    fprintf(stderr, "ERROR: Arguments less than 4.\n");
    return EXIT_FAILURE;
  }

  // runs shell sort for array
  if((strcmp("-a", argv[1])) == 0){
    int size = 0; // number of elements in the array
    long n_comp = 0; // number of comparisons counted
	  int elements = 0; // number of elements written to the file

	  long * array = Array_Load_From_File(argv[2], &size); // loads the array from the file
    
    Array_Shellsort(array, size, &n_comp); // performs shell sort on the array and calcuates number of comparisons made
	  
    elements = Array_Save_To_File(argv[3], array, size); // saves the elemments the file and returns the number of elements printed
	
    fprintf(stdout, "%ld\n", n_comp); // prints number of comparisons to standard output

    free(array); // frees memory allocated for the array
  }

  // runs shell sort for linked list
  if((strcmp("-l", argv[1])) == 0){
    long n_comp = 0; // number of comparisons counted
	  int elements = 0; // number of elements written to the file

    Node * list = List_Load_From_File(argv[2]); // loads linked list from file

    list = List_Shellsort(list, &n_comp); // performs shell sort on the linked and calcuates number of comparisons made
    
    elements = List_Save_To_File(argv[3], list); // saves the elemments the file and returns the number of elements printed
	
    fprintf(stdout, "%ld\n", n_comp); // prints number of comparisons to standard output  
  }

  // t = clock() - t; 
  // double time_taken = ((double)t)/CLOCKS_PER_SEC; // time taken (in seconds)
  
  // fprintf(stdout, "Program took %f seconds to execute.\n\n", time_taken); 
  return EXIT_SUCCESS; // return EXIT_SUCCESS is program is successful
}