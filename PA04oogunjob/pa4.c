#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hbt.h"
#include "pa4.h"

int main(int argc, char * * argv){ 
  // ensures there are 6 arguments given
  if (argc < 2 || argc > 4){
    fprintf(stderr, "ERROR: Invalid Number of Arguments.\n");
    return EXIT_FAILURE;
  }
  
  // building a height-balanced BST
  if((strcmp("-b", argv[1])) == 0){
    FILE * file = fopen(argv[2], "rb"); // opens the binary file that contains the binary search tree
    
    if(file == NULL){
      fprintf(stdout, "-1\n");
      return EXIT_FAILURE;
    }
    
    Tnode * root = Build_AVL_Tree(file); // builds the height-balanced binary tree
    
    fclose(file); // closes input file
     
    file = fopen(argv[3], "wb"); // opens output file to be written to
    Print_Binary_Tree(root, file); // prints binary tree in pre-order traversal to output file
    
    fclose(file); // closes output file
		
    deleteTree(root); // deletes the binary tree 
    return EXIT_SUCCESS; // exits program
  }

  // evaluation of height-balanced BST
  else if((strcmp("-e", argv[1])) == 0){
    FILE * file = fopen(argv[2], "rb"); // opens the binary file that contains the binary search tree
    
    // if the file cannot be opened, print the following to standard output and return EXIT_FAILURE
    if(file == NULL){
      fprintf(stdout, "-1,0,0\n");
      return EXIT_FAILURE;
    }
    
    Evaluate_Tree(file); // evaluates the binary search tree built from given file
    
    fclose(file); // closes the file
    return EXIT_SUCCESS; // exits program
  }
  
  // invalid option was provided
  else{
    fprintf(stderr, "ERROR: Invalid Option Provided.\n");
    return EXIT_FAILURE;
  }  
}
