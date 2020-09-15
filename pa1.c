#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell_list.h"
#include "shell_array.h"

int main(int argc, char * * argv){ 
  // ensures there are 4 arguments given
  if (argc < 4) {
    fprintf(stderr, "ERROR: Number of arguments less than 4.\n");
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

    free(array); // frees the array

    return EXIT_SUCCESS; // exits program
  }

  // runs shell sort for linked list
  if((strcmp("-l", argv[1])) == 0){
    long n_comp = 0; // number of comparisons counted
	  int elements = 0; // number of elements written to the file

    Node * list = List_Load_From_File(argv[2]); // loads linked list from file

    list = List_Shellsort(list, &n_comp); // performs shell sort on the linked and calcuates number of comparisons made
    
    elements = List_Save_To_File(argv[3], list); // saves the elemments the file and returns the number of elements printed
	
    fprintf(stdout, "%ld\n", n_comp); // prints number of comparisons to standard output 

    // deletion of linked list
    Node * current = list; // current position in linked list
    Node * next; // next node from current node in linked list
  
    while(current != NULL){ 
      next = current -> next; 
      free(current); 
      current = next; 
    }    
    
    return EXIT_SUCCESS; // exits program 
  }

  // if the second argument does not match either a "-a" or "-l", returns EXIT_FAILURE
  else{
    fprintf(stderr, "ERROR: Second arguement is invalid.\n");
    return EXIT_FAILURE;
  }
}
